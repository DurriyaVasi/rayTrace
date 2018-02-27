glm::vec3 getRayDir(eye, screenPoint, w, h, wWindow, hWindow, camRight, camUp, camDir) {
	glm::vec3 rayDir = screenPoint + (vec3(-1 * w/2, -1 * h/2, 0));
        rayDir = glm::scale(rayDir, vec3(-1 * wWindow/w, -1 * hWindow/h, 1));
        rayDir = eye + (rayDir[0] * camRight) + (rayDir[1] * camUp) + (rayDir[2] * camDir);
        rayDir = rayDir - eye;
	return rayDir;
}	
	
