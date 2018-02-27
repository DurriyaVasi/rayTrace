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
			//	std::cout << "Here" << std::endl;
				image(x, y, 0) = 1;
				image(x, y, 1) = 1;
				image(x, y, 2) = 1;


				/*
				


				*/

			}
		}
	}

}
