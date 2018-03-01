#include <glm/ext.hpp>

#include "A4.hpp"
//#include "helpers.cpp"

#include <list>

glm::vec3 getRayDir(glm::vec3 eye, glm::vec3 screenPoint, float w, float h, float wWindow, float hWindow, glm::vec3 camRight, glm::vec3 camUp, glm::vec3 camDir) {
        glm::vec3 rayDir = screenPoint + (glm::vec3(-1 * w/2, -1 * h/2, 0));
        rayDir[0] = rayDir[0]*(wWindow/w);
        rayDir[1] = rayDir[1]*(hWindow/h);

        rayDir = eye + (rayDir[0] * camRight) + (rayDir[1] * camUp) + (rayDir[2] * camDir);
        rayDir = rayDir - eye;
        return rayDir;
}

bool vecIs0(glm::vec3 v) {
        return ((v[0] == 0) && (v[1] == 0) && (v[2] == 0));
}

bool samePos(glm::vec3 pos1, glm::vec3 pos2) {
        glm::vec3 diff = pos2 - pos1;
        if (diff[0] < 0) {
                diff[0] = diff[0] * -1;
        }
        if (diff[1] < 0) {
                diff[1] = diff[1] * -1;
        }
        if (diff[0] < 0.001 && diff[1] < 0.001) {
                return true;
        }
        else {
                return false;
        }
}

glm::vec3 multiply(glm::vec3 vecA, glm::vec3 vecB) {
        glm::vec3 vecC = glm::vec3(0, 0, 0);
        vecC[0] = vecA[0] * vecB[0];
        vecC[1] = vecA[1] * vecB[1];
        vecC[2] = vecA[2] * vecB[2];
        return vecC;
}

float capFloat(float f) {
	if (f > 1) {
		f = 1;
	}
	else if (f < 0) {
		f = 0;
	}
	return f;
}

glm::vec3 capColour(glm::vec3 c) {
	c[0] = capFloat(c[0]);
	c[1] = capFloat(c[1]);
	c[2] = capFloat(c[2]);
	return c;
}

glm::vec3 switchXY(glm::vec3 v) {
	v[0] = v[0] * -1;
	v[1] = v[1] * -1;
}

glm::vec3 switchZ(glm::vec3 v) {
	v[2] = v[2] * -1;
}

void A4_Render(
		// What to render
		SceneNode * root,

		// Image to write to, set to a given width and height
		Image & image,

		// Viewing parameters
		const glm::vec3 & eye,
		const glm::vec3 & view,
		const glm::vec3 & up,
		double fovy,

		// Lighting parameters
		const glm::vec3 & ambient,
		const std::list<Light *> & lights
) {

  std::cout << "Calling A4_Render(\n" <<
		  "\t" << *root <<
          "\t" << "Image(width:" << image.width() << ", height:" << image.height() << ")\n"
          "\t" << "eye:  " << glm::to_string(eye) << std::endl <<
		  "\t" << "view: " << glm::to_string(view) << std::endl <<
		  "\t" << "up:   " << glm::to_string(up) << std::endl <<
		  "\t" << "fovy: " << fovy << std::endl <<
          "\t" << "ambient: " << glm::to_string(ambient) << std::endl <<
		  "\t" << "lights{" << std::endl;

	for(const Light * light : lights) {
		std::cout << "\t\t" <<  *light << std::endl;
	}
	std::cout << "\t}" << std::endl;
	std:: cout <<")" << std::endl;

	size_t h = image.height();
	size_t w = image.width();

	glm::vec3 camDir = glm::normalize(view); //w
        glm::vec3 camRight = glm::normalize(glm::cross(up, camDir)); //u
        glm::vec3 camUp = glm::cross(camDir, camRight); //v
	glm::vec3 lookAt = view + eye;
	float initZ = lookAt[2];
	fovy = glm::radians(fovy);
	//fovx = fovx * (w / h);
	float distance = glm::length(view);
	float hWindow = 2 * distance * glm::tan(fovy/2);
	float wWindow = ((float)w/(float)h) * hWindow;

	for (uint y = 0; y < h; ++y) {
		for (uint x = 0; x < w; ++x) {
			glm::vec3 screenPoint = glm::vec3((float)x, (float)y, distance);
			glm::vec3 rayPos = eye;
			glm::vec3 rayDir = getRayDir(eye, screenPoint, (float)w, (float)h, wWindow, hWindow, camRight, camUp, camDir);
			
			if ((x == 0 && y == 0) || (x == 255 && y == 255)) { 
				//std::cout << glm::to_string(eye) << " " << glm::to_string(screenPoint) << " " << w << " " << h << " " << wWindow << " " << hWindow << " " << glm::to_string(camRight) << " " << glm::to_string(camUp) << " " << glm::to_string(camDir) << std::endl;
				//std::cout << glm::to_string(rayPos) << " " << glm::to_string(rayDir) << std::endl;
			}
			
			Intersect intersect = root->intersect(rayDir, rayPos);			

			if (!intersect.hit) {
                                // Red: increasing from top to bottom
                                image((w - x - 1), (h - y - 1), 0) = (double)y / h;
                                // Green: increasing from left to right
                                image((w - x - 1), (h - y - 1), 1) = (double)x / w;
                                // Blue: in lower-left and upper-right corners
                                image((w - x - 1), (h - y - 1), 2) = ((y < h/2 && x < w/2)
                                                  || (y >= h/2 && x >= w/2)) ? 1.0 : 0.0;
                        }
			else {
			
				 glm::vec3 colour = glm::vec3(0, 0, 0);
                                glm::vec3 kd = intersect.kd;
                                glm::vec3 ks = intersect.ks;
                                float shininess = intersect.shininess;
				
				//if (kd[0] != 0.5) {
				//	std::cout << glm::to_string(kd) << " " << glm::to_string(ks) << " " << shininess << " " << glm::to_string(ambient) << std::endl;
				//}				

                                colour = colour + capColour(multiply(kd, ambient));

                                for(const Light * light : lights) {
					
                                        bool lightHits = false;
					//lightHits = true;

                                        glm::vec3 lightPos = intersect.pos;
                                        glm::vec3 lightDir = light->position - intersect.pos;
					//glm::vec3 lightDir = intersect.pos - light->position;
                                        Intersect iLight = root->intersect(lightDir, lightPos);

				//	glm::vec3 lightHitDir = intersect.pos - light->position;
					glm::vec3 lightHitDir = lightDir;
					lightHitDir = glm::normalize(lightHitDir);

					if(iLight.hit) {
						std::cout << glm::to_string(light->position) << " " << glm::to_string(intersect.pos) << " " << glm::to_string(iLight.pos) << std::endl;
					}

                                        if(!iLight.hit || (!(glm::length(iLight.pos - intersect.pos) < (glm::length(lightDir) - 0.01)))) {
                                                lightHits = true;
                                        }
					if (lightHits && (!vecIs0(kd))) {
					//	std::cout << glm::to_string(colour) << " " << glm::to_string(kd) << " " << glm::to_string(ambient) << std::endl;

						float lambertDirectLight = glm::dot(lightHitDir, intersect.n);
						colour = colour + capColour((lambertDirectLight * multiply(kd, light->colour)));
						
					//	std::cout << glm::to_string(colour) << " " << glm::to_string(kd) << " " << glm::to_string(light->colour) << " " << lambertDirectLight << std::endl;

					//	std::cout << glm::to_string(multiply(kd, light->colour)) << " " << glm::to_string(lambertDirectLight * multiply(kd, light->colour)) << " " << glm::to_string(lambertDirectLight * glm::vec3(1, 1, 1)) << std::endl;
						
					}
                                        if (lightHits && (!vecIs0(ks))) {
                                                glm::vec3 reflectPos = intersect.pos;
                                                glm::vec3 reflectDir =  lightHitDir - (2 * (glm::dot(glm::normalize(lightHitDir), intersect.n)) * intersect.n);
						float phong = std::pow(glm::dot(reflectDir, view), shininess);
						colour = colour + capColour((phong * multiply(ks, light->colour)));
					}
				}
				colour = capColour(colour);
				image((w - x - 1), (h - y- 1), 0) = colour[0];
				image((w - x - 1), (h - y - 1), 1) = colour[1];
				image((w - x - 1), (h - y - 1), 2) = colour[2];		
			/*	image((w - x - 1), (h - y - 1), 0) = 1;
                                image((w - x - 1), (h - y - 1), 1) = 1;
                                image((w - x - 1), (h - y - 1), 2) = 1;*/


                          }
			
		}
	}

}
