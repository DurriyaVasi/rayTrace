#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Intersect {
	public: 
		glm::vec3 pos;
		glm::vec3 n;
		bool hit;
		double t;
		Intersect() {
			pos = glm::vec3(0, 0, 0);
			n = glm::vec3(0, 0, 0);
			hit = false;
			t = 0;
		}
		Intersect(glm::vec3 pos, glm::vec3 n, bool hit, double t) {
			this->pos = pos;
			this->n = n;
			this->hit = hit;
			this->t = t;
		}
};
