#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <list>

glm::vec3 getRayDir(glm::vec3 eye, glm::vec3 screenPoint, float w, float h, float wWindow, float hWindow, glm::vec3 camRight, glm::vec3 camUp, glm::vec3 camDir) {
	glm::vec3 rayDir = screenPoint + (glm::vec3(-1 * w/2, -1 * h/2, 0));
	rayDir[0] = rayDir[0]*(-1 * wWindow/w);
	rayDir[1] = rayDir[1]*(-1 * hWindow/h);
	
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
