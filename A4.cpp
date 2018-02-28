#include <glm/ext.hpp>

#include "A4.hpp"
#include "helpers.cpp"

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
                                image(x, y, 0) = (double)y / h;
                                // Green: increasing from left to right
                                image(x, y, 1) = (double)x / w;
                                // Blue: in lower-left and upper-right corners
                                image(x, y, 2) = ((y < h/2 && x < w/2)
                                                  || (y >= h/2 && x >= w/2)) ? 1.0 : 0.0;
                        }
			else {
			/*
				 glm::vec3 colour = glm::vec3(0, 0, 0);
                                glm::vec3 kd = intersect.kd;
                                glm::vec3 ks = intersect.ks;
                                float shininess = intersect.shininess;
				
				//if (kd[0] != 0.5) {
				//	std::cout << glm::to_string(kd) << " " << glm::to_string(ks) << " " << shininess << " " << glm::to_string(ambient) << std::endl;
				//}				

                                colour = colour + multiply(kd, ambient);

                                for(const Light * light : lights) {

                                        bool lightHits = false;

                                        glm::vec3 lightPos = intersect.pos;
                                        glm::vec3 lightDir = light->position - intersect.pos;
                                        Intersect iLight = root->intersect(lightDir, lightPos);

					//glm::vec3 lightHitDir = intersect.pos - light->position;
					glm::vec3 lightHitDir = lightDir;

                                        if(!iLight.hit || (!(glm::length(iLight.pos - intersect.pos) < (glm::length(lightDir) - 0.01)))) {
                                                lightHits = true;
                                        }
					if (lightHits && (!vecIs0(kd))) {
					//	std::cout << glm::to_string(colour) << " " << glm::to_string(kd) << " " << glm::to_string(ambient) << std::endl;

						float lambertDirectLight = glm::dot(lightHitDir, intersect.n);
						colour = colour + (lambertDirectLight * multiply(kd, light->colour));
						
					//	std::cout << glm::to_string(colour) << " " << glm::to_string(kd) << " " << glm::to_string(light->colour) << " " << lambertDirectLight << std::endl;

					//	std::cout << glm::to_string(multiply(kd, light->colour)) << " " << glm::to_string(lambertDirectLight * multiply(kd, light->colour)) << " " << glm::to_string(lambertDirectLight * glm::vec3(1, 1, 1)) << std::endl;
						
					}
                                        if (lightHits && (!vecIs0(ks))) {
                                                glm::vec3 reflectPos = intersect.pos;
                                                glm::vec3 reflectDir =  lightHitDir - (2 * (glm::dot(glm::normalize(lightHitDir), intersect.n)) * intersect.n);
						float phong = std::pow(glm::dot(reflectDir, view), shininess);
						colour = colour + (phong * multiply(ks, light->colour));
					}
				}
				image(x, y, 0) = colour[0];
				image(x, y, 1) = colour[1];
				image(x, y, 2) = colour[2];	*/	
				image (x, y, 0) = 1;
        	                image(x, y, 1) = 1;
	                        image (x, y, 2) = 1;

                          }
			
		}
	}

}
