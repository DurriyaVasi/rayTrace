#include "Primitive.hpp"
#include "polyroots.hpp"

Primitive::~Primitive()
{
}

Intersect Primitive::intersect(glm::vec3 rayDir, glm::vec3 rayPos) {
	return Intersect();
}

Sphere::~Sphere()
{
}

Cube::~Cube()
{
}

NonhierSphere::~NonhierSphere()
{
}

Intersect NonhierSphere::intersect(glm::vec3 rayDir, glm::vec3 rayPos) {
	glm::vec3 aMc = rayPos - m_pos;
	double A = glm::dot(rayDir, rayDir);
	double B = 2 * glm::dot(rayDir, aMc);
	double C = glm::dot(aMc, aMc) - (m_pos * m_pos);
	double roots[2];
	size_t numRoots = quadraticRoots(A, B, C, roots)
	if (numRoots == 0) {
		return Intersect();
	}
	else if (numRoots == 1) {
		double t = roots[0];
		return( (rayDir + (t * rayPos)), glm::vec3(0, 0, 0), true, t);
	}
	else if (numRoots == 2) {
		double t;
		if (roots[0] > roots[1]) {
			t = roots[0];
		}
		else {
			t = roots[1];
		}
		return( (rayDir + (t * rayPos)), glm::vec3(0, 0, 0), true, t);
	}
	else {
		cerr <<"nonhier sphere does not have 0 1 2 roots" << endl;
	}
}

NonhierBox::~NonhierBox()
{
}
