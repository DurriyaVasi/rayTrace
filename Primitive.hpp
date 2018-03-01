#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "intersect.cpp"


struct Triangle
{
        size_t v1;
        size_t v2;
        size_t v3;

        Triangle( size_t pv1, size_t pv2, size_t pv3 )
                : v1( pv1 )
                , v2( pv2 )
                , v3( pv3 )
        {}
};


class Primitive {
public:
  virtual ~Primitive();
  virtual Intersect intersect(glm::vec3 rayDir, glm::vec3 rayPos);
  Intersect intersectPolygon(glm::vec3 rayDir, glm::vec3 rayPos, std::vector<glm::vec3> vertices, std::vector<Triangle> faces);
  Intersect intersectTriangle(glm::vec3 rayDir, glm::vec3 rayPos, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
};

class Sphere : public Primitive {
public:
  virtual ~Sphere();
};

class Cube : public Primitive {
public:
  virtual ~Cube();
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const glm::vec3& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierSphere();
  virtual Intersect intersect(glm::vec3 rayDir, glm::vec3 rayPos);

private:
  glm::vec3 m_pos;
  double m_radius;
};

class NonhierBox : public Primitive {
public:
  NonhierBox(const glm::vec3& pos, double size)
    : m_pos(pos), m_size(size)
  {
	float fSize = (float)size/2;
	float nSize = fSize * -1;
/*	m_vertices.push_back(pos + glm::vec3(nSize, size, nSize));
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
	float size1 = (float)size;
	m_vertices.push_back(pos + glm::vec3(0, 0, size1));
        m_vertices.push_back(pos + glm::vec3(size1, 0, size1));
        m_vertices.push_back(pos + glm::vec3(size1, size1, size1));
        m_vertices.push_back(pos + glm::vec3(0, size1, size1));
        m_vertices.push_back(pos + glm::vec3(0, 0, 0));
        m_vertices.push_back(pos + glm::vec3(size1, 0, 0));
        m_vertices.push_back(pos + glm::vec3(size1, size1, 0));
        m_vertices.push_back(pos + glm::vec3(0, size1, 0)); 
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
  
  virtual ~NonhierBox();
  virtual Intersect intersect(glm::vec3 rayDir, glm::vec3 rayPos);

  glm::vec3 m_pos;
  double m_size;
  std::vector<glm::vec3> m_vertices;
  std::vector<Triangle> m_faces;
};
