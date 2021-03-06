#include "Primitive.hpp"
#include "polyroots.hpp"
#include <iostream>

using namespace std;

Primitive::~Primitive()
{
}

void Primitive::createInitCube(glm::vec3 m_pos, double m_size, std::vector<glm::vec3> &m_vertices, std::vector<Triangle> &m_faces) {
        float fSize = (float)m_size/2;
        float nSize = fSize * -1;
/*      m_vertices.push_back(pos + glm::vec3(nSize, size, nSize));
        m_vertices.push_back(pos + glm::vec3(size, size, nSize));
        m_vertices.push_back(pos + glm::vec3(size, size, size));
        m_vertices.push_back(pos + glm::vec3(nSize, size, size));
        m_vertices.push_back(pos + glm::vec3(nSize, nSize, nSize));
        m_vertices.push_back(pos + glm::vec3(size, nSize, nSize));
        m_vertices.push_back(pos + glm::vec3(size, nSize, size));
        m_vertices.push_back(pos + glm::vec3(nSize, nSize, size));
        m_faces.push_back(Triangle(0, 1, 3));
        m_faces.push_back(Triangle(1, 2, 3));
        m_faces.push_back(Triangle(4, 7, 5));
        m_faces.push_back(Triangle(5, 6, 7));
        m_faces.push_back(Triangle(0, 3, 7));
        m_faces.push_back(Triangle(0, 4, 7));
        m_faces.push_back(Triangle(1, 5, 6));
        m_faces.push_back(Triangle(1, 2, 6));
        m_faces.push_back(Triangle(3, 2, 6));
        m_faces.push_back(Triangle(3, 7, 6));
        m_faces.push_back(Triangle(0, 1, 5));
        m_faces.push_back(Triangle(0, 4, 5));*/
        float size1 = (float)m_size;
        m_vertices.push_back(m_pos + glm::vec3(0, 0, size1));
        m_vertices.push_back(m_pos + glm::vec3(size1, 0, size1));
        m_vertices.push_back(m_pos + glm::vec3(size1, size1, size1));
        m_vertices.push_back(m_pos + glm::vec3(0, size1, size1));
        m_vertices.push_back(m_pos + glm::vec3(0, 0, 0));
        m_vertices.push_back(m_pos + glm::vec3(size1, 0, 0));
        m_vertices.push_back(m_pos + glm::vec3(size1, size1, 0));
        m_vertices.push_back(m_pos + glm::vec3(0, size1, 0));
        m_faces.push_back(Triangle(2, 3, 0));
        m_faces.push_back(Triangle(0, 1, 3));
        m_faces.push_back(Triangle(2, 1, 5));
        m_faces.push_back(Triangle(5, 6, 2));
        m_faces.push_back(Triangle(3, 7, 4));
        m_faces.push_back(Triangle(4, 0, 3));
        m_faces.push_back(Triangle(7, 6, 5));
        m_faces.push_back(Triangle(5, 4, 7));
        m_faces.push_back(Triangle(1, 0, 4));
        m_faces.push_back(Triangle(4, 5, 1));
        m_faces.push_back(Triangle(2, 6, 7));
        m_faces.push_back(Triangle(7, 3, 2));
}


glm::vec3 transformPoint(glm::vec3 v, glm::mat4 trans) {
	glm::vec4 v4 = glm::vec4(v[0], v[1], v[2], 1);
	v4 = trans * v4;
	return glm::vec3(v4[0], v4[1], v4[2]);
}

glm::vec3 transformVector(glm::vec3 v, glm::mat4 trans) {
	glm::vec4 v4 = glm::vec4(v[0], v[1], v[2], 0);
        v4 = trans * v4;
        return glm::vec3(v4[0], v4[1], v4[2]);
}

Intersect Primitive::intersect(glm::vec3 rayDir, glm::vec3 rayPos, glm::mat4 trans) {
	return Intersect();
}

glm::vec3 getRayPoint(glm::vec3 rayDir, glm::vec3 rayPos, float t) {
        return (rayPos + (t * rayDir));
}

glm::vec3 getRaySphereNormal(glm::vec3 rayDir, glm::vec3 rayPos, float t, glm::vec3 centre) {
        glm::vec3 rayPoint = getRayPoint(rayDir, rayPos, t);
        return glm::normalize(rayPoint - centre);
}

Intersect Primitive::intersectTriangle(glm::vec3 rayDir, glm::vec3 rayPos, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	float x1 = p2[0] - p1[0];
	float x2 = p3[0] - p1[0];
	float x3 = rayDir[0];
	float y1 = p2[1] - p1[1];
        float y2 = p3[1] - p1[1];
        float y3 = rayDir[1];
	float z1 = p2[2] - p1[2];
        float z2 = p3[2] - p1[2];
        float z3 = rayDir[2];
	float r1 = rayPos[0] - p1[0];
	float r2 = rayPos[1] - p1[1];
	float r3 = rayPos[2] - p1[2];
	glm::mat3 dMat;
	dMat[0][0] = x1;
	dMat[1][0] = x2;
	dMat[2][0] = x3;
	dMat[0][1] = y1;
	dMat[1][1] = y2;
	dMat[2][1] = y3;
	dMat[0][2] = z1;
	dMat[1][2] = z2;
	dMat[2][2] = z3;
	glm::mat3 d1Mat;
	d1Mat[0][0] = r1;
        d1Mat[1][0] = x2;
        d1Mat[2][0] = x3;
        d1Mat[0][1] = r2;
        d1Mat[1][1] = y2;
        d1Mat[2][1] = y3;
        d1Mat[0][2] = r3;
        d1Mat[1][2] = z2;
        d1Mat[2][2] = z3;
	glm::mat3 d2Mat;
	d2Mat[0][0] = x1;
        d2Mat[1][0] = r1;
        d2Mat[2][0] = x3;
        d2Mat[0][1] = y1;
        d2Mat[1][1] = r2;
        d2Mat[2][1] = y3;
        d2Mat[0][2] = z1;
        d2Mat[1][2] = r3;
        d2Mat[2][2] = z3;
	glm::mat3 d3Mat;
	d3Mat[0][0] = x1;
        d3Mat[1][0] = x2;
        d3Mat[2][0] = r1;
        d3Mat[0][1] = y1;
        d3Mat[1][1] = y2;
        d3Mat[2][1] = r2;
        d3Mat[0][2] = z1;
        d3Mat[1][2] = z2;
        d3Mat[2][2] = r3;
	float d = glm::determinant(dMat);
	float d1 = glm::determinant(d1Mat);
	float d2 = glm::determinant(d2Mat);
	float d3 = glm::determinant(d3Mat);
	float B = d1/d;
	float A = d2/d;
	float t = d3/d;
	if (((B + 0.001) > 0) && ((A + 0.001) > 0) && ((B + A - 0.001) < 1)) {
 		glm::vec3 pos = getRayPoint(rayDir, rayPos, t);
		glm::vec3 normal = glm::normalize(glm::cross( (p3-p2), (p1-p2) ));
		return Intersect(pos, normal, true, t, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0);
	}
	else {
		return Intersect();
	}
}

Intersect Primitive::intersectPolygon(glm::vec3 rayDir, glm::vec3 rayPos, std::vector<glm::vec3> vertices, std::vector<Triangle> faces) {
	glm::vec3 pos = glm::vec3(0, 0, 0);
	glm::vec3 n = glm::vec3(0, 0, 0);
	bool hit = false;
	double t = 0;
	for (std::vector<Triangle>::iterator it = faces.begin(); it != faces.end(); ++it) {
		glm::vec3 p1 = vertices[(*it).v1];
		glm::vec3 p2 = vertices[(*it).v2];
		glm::vec3 p3 = vertices[(*it).v3];
		Intersect i = intersectTriangle(rayDir, rayPos, p1, p2, p3);
		if (!hit && i.hit) {
			hit = true;
			pos = i.pos;
			n = i.n;
			t = i.t;
		} 
		else if(hit && i.hit && (i.t < t)) {
			pos = i.pos;
                        n = i.n;
                        t = i.t;
		}
	}
	return Intersect(pos, n, hit, t, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0);
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

Intersect getSphereIntersect(glm::vec3 m_pos, double m_radius, glm::vec3 rayDir, glm::vec3 rayPos) {
	double roots[2];
	glm::vec3 aMc = rayPos - m_pos;
	float A = glm::dot(rayDir, rayDir);
        float B = 2 * glm::dot(rayDir, aMc);
        float C = glm::dot(aMc, aMc)- ((float)m_radius * (float)m_radius);
	size_t numRoots = quadraticRoots((double)A, (double)B, (double)C, roots);
        if (numRoots == 0) {
//              cout << "no roots" << endl;
                return Intersect();
        }
        else if (numRoots == 1) {
//              cout << "1 roots" << endl;
                double t = roots[0];
                return Intersect( getRayPoint(rayDir, rayPos, (float)t), getRaySphereNormal(rayDir, rayPos, (float)t, m_pos), true, t, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0 );
        }
        else if (numRoots == 2) {
//              cout << "2 roots" << endl;
                double t;
                if (roots[0] < roots[1]) {
                        t = roots[0];
                }
                else {
                        t = roots[1];
                }
                return Intersect( getRayPoint(rayDir, rayPos, (float)t), getRaySphereNormal(rayDir, rayPos, (float)t, m_pos), true, t, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0 );
        }
        else {
                cerr <<"nonhier sphere does not have 0 1 2 roots" << endl;
        }
}

Intersect NonhierSphere::intersect(glm::vec3 rayDir, glm::vec3 rayPos, glm::mat4 trans) {
//	cout << glm::to_string(rayDir) << " " << glm::to_string(rayPos) << " " << glm::to_string(m_pos) << " " << m_radius << endl;
	return getSphereIntersect(m_pos, m_radius, rayDir, rayPos);
}

Intersect Sphere::intersect(glm::vec3 rayDir, glm::vec3 rayPos, glm::mat4 trans) {
	rayDir = transformVector(rayDir, glm::inverse(trans));
	rayPos = transformPoint(rayPos, glm::inverse(trans));
	Intersect intersect = getSphereIntersect(glm::vec3(0, 0, 0), 0.5, rayDir, rayPos);
	if (intersect.hit) {	
		return Intersect(transformPoint(intersect.pos, trans), transformPoint(intersect.n, glm::transpose(glm::inverse(trans))), intersect.t, true, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0); 
	}
	else {
		return Intersect();
	}
}

	

/*Intersect Cylinder::intersect(glm::vec3 rayDir, glm::vec3 rayPos, glm::mat4 trans) {
	glm:vec3 vA = glm::vec3(0, 0, 1);
	float vDva = (glm::dot(rayDir, vA));
	glm::vec3 deltaP = rayPos - m_pos; // define m_pos
	float pDv = glm::dot(deltaP, vA);
	float A = (rayDir - (vDva * vA));
	A = A * A;
	float B = 2 * glm::dot((rayDir - (vDva * vA)), deltaP - (pDv * vA));
	float C = (deltaP - (pDv * vA));
	C = C * C;
	C = C - ((m_radius) * m_radius);
		
}*/

NonhierBox::~NonhierBox()
{
}

Intersect NonhierBox::intersect(glm::vec3 rayDir, glm::vec3 rayPos, glm::mat4 trans) {
	return Primitive::intersectPolygon(rayDir, rayPos, m_vertices, m_faces);
}

Intersect Cube::intersect(glm::vec3 rayDir, glm::vec3 rayPos, glm::mat4 trans) {
	cout << "intersect cube" << endl;
	std::vector<glm::vec3> transformedVertices;
	for(std::vector<glm::vec3>::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it) {
		transformedVertices.push_back(transformPoint(*it, trans));
	}
	return Primitive::intersectPolygon(rayDir, rayPos, transformedVertices, m_faces);
}
		
