#include <glm/glm.hpp>
#include <glm/ext.hpp>

glm::vec3 getRayDir(glm::vec3 eye, glm::vec3 screenPoint, size_t w, size_t h, double wWindow, double hWindow, glm::vec3 camRight, glm::vec3 camUp, glm::vec3 camDir) {
	glm::vec3 rayDir = screenPoint + (glm::vec3(-1 * w/2, -1 * h/2, 0));
	rayDir[0] = rayDir[0]*(-1 * wWindow/w);
	rayDir[1] = rayDir[1]*(hWindow/h);
	
        rayDir = eye + (rayDir[0] * camRight) + (rayDir[1] * camUp) + (rayDir[2] * camDir);
        rayDir = rayDir - eye;
	return rayDir;
}	
	
