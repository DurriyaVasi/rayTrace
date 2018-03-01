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
  virtual Intersect intersect(glm::vec3 rayDir, glm::vec3 rayPos, glm::mat4 trans);
  Intersect intersectPolygon(glm::vec3 rayDir, glm::vec3 rayPos, std::vector<glm::vec3> vertices, std::vector<Triangle> faces);
  Intersect intersectTriangle(glm::vec3 rayDir, glm::vec3 rayPos, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
  void createInitCube(glm::vec3 m_pos, double m_size, std::vector<glm::vec3> &m_vertices, std::vector<Triangle> &m_faces);
};

class Sphere : public Primitive {
public:
  virtual ~Sphere();
  virtual Intersect intersect(glm::vec3 rayDir, glm::vec3 rayPos, glm::mat4 trans);
};

class Cube : public Primitive {
public:
  Cube() {
	m_pos  = glm::vec3(0, 0, 0);
	m_size = 1;
	Primitive::createInitCube(m_pos, m_size, m_vertices, m_faces);	
  } 
  glm::vec3 m_pos;
  double m_size;
  std::vector<glm::vec3> m_vertices;
  std::vector<Triangle> m_faces;
  virtual ~Cube();
  virtual Intersect intersect(glm::vec3 rayDir, glm::vec3 rayPos, glm::mat4 trans);
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const glm::vec3& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierSphere();
  virtual Intersect intersect(glm::vec3 rayDir, glm::vec3 rayPos, glm::mat4 trans);

private:
  glm::vec3 m_pos;
  double m_radius;
};

class NonhierBox : public Primitive {
public:
  NonhierBox(const glm::vec3& pos, double size)
    : m_pos(pos), m_size(size)
  {
	Primitive::createInitCube(m_pos, m_size, m_vertices, m_faces);
  }
  
  virtual ~NonhierBox();
  virtual Intersect intersect(glm::vec3 rayDir, glm::vec3 rayPos, glm::mat4 trans);

  glm::vec3 m_pos;
  double m_size;
  std::vector<glm::vec3> m_vertices;
  std::vector<Triangle> m_faces;
};
