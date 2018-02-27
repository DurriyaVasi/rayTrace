class Intersect {
	public: 
		glm::vec3 pos;
		glm::vec3 n;
		bool hit;
		double t;
		Intersect() {
			pos = vec3(0, 0, 0);
			n = vec3(0, 0, 0);
			hit = false;
			t = 0;
		}
		Intersect(vec3 pos, vec3 n, bool hit, double t) {
			this->pos = pos;
			this->n = n;
			this->hit = hit;
			this->t = t;
		}
};
