#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Intersect {
	public: 
		glm::vec3 pos;
		glm::vec3 n;
		bool hit;
		double t;
		glm::vec3 kd;
		glm::vec3 ks;
		float shininess;
		Intersect() {
			pos = glm::vec3(0, 0, 0);
			n = glm::vec3(0, 0, 0);
			hit = false;
			t = 0;
			kd = glm::vec3(0, 0, 0);
			ks = glm::vec3(0, 0, 0);
			shininess = 0.0f;
		}
		Intersect(glm::vec3 pos, glm::vec3 n, bool hit, double t, glm::vec3 kd, glm::vec3 ks, float shininess) {
			this->pos = pos;
			this->n = n;
			this->hit = hit;
			this->t = t;
			this->kd = kd;
			this->ks = ks;
			this->shininess = shininess;
		}
};
