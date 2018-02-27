#include "Primitive.hpp"
#include "polyroots.hpp"
#include <iostream>

using namespace std;

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
//	cout << glm::to_string(rayDir) << " " << glm::to_string(rayPos) << " " << glm::to_string(m_pos) << " " << m_radius << endl;

	glm::vec3 aMc = rayPos - m_pos;
	float A = glm::dot(rayDir, rayDir);
	float B = 2 * glm::dot(rayDir, aMc);
	float C = glm::dot(aMc, aMc)- (m_radius * m_radius);
	double roots[2];
	size_t numRoots = quadraticRoots((double)A, (double)B, (double)C, roots);
	if (numRoots == 0) {
//		cout << "no roots" << endl;
		return Intersect();
	}
	else if (numRoots == 1) {
//		cout << "1 roots" << endl;
		double t = roots[0];
		return Intersect( (rayDir + (t * rayPos)), glm::vec3(0, 0, 0), true, t);
	}
	else if (numRoots == 2) {
//		cout << "2 roots" << endl;
		double t;
		if (roots[0] > roots[1]) {
			t = roots[0];
		}
		else {
			t = roots[1];
		}
		return Intersect( (rayDir + ((float)t * rayPos)), glm::vec3(0, 0, 0), true, t);
	}
	else {
		cerr <<"nonhier sphere does not have 0 1 2 roots" << endl;
	}
}

NonhierBox::~NonhierBox()
{
}
