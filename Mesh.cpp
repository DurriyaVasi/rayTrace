#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

// #include "cs488-framework/ObjFileDecoder.hpp"
#include "Mesh.hpp"

glm::vec3 transformPoint1(glm::vec3 v, glm::mat4 trans) {
        glm::vec4 v4 = glm::vec4(v[0], v[1], v[2], 1);
        v4 = trans * v4;
        return glm::vec3(v4[0], v4[1], v4[2]);
}

Mesh::Mesh( const std::string& fname )
	: m_vertices()
	, m_faces()
{
	std::string code;
	double vx, vy, vz;
	size_t s1, s2, s3;

	std::ifstream ifs( fname.c_str() );
	while( ifs >> code ) {
		if( code == "v" ) {
			ifs >> vx >> vy >> vz;
			m_vertices.push_back( glm::vec3( vx, vy, vz ) );
		} else if( code == "f" ) {
			ifs >> s1 >> s2 >> s3;
			m_faces.push_back( Triangle( s1 - 1, s2 - 1, s3 - 1 ) );
		}
	}
}

std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  out << "mesh {";
  /*
  
  for( size_t idx = 0; idx < mesh.m_verts.size(); ++idx ) {
  	const MeshVertex& v = mesh.m_verts[idx];
  	out << glm::to_string( v.m_position );
	if( mesh.m_have_norm ) {
  	  out << " / " << glm::to_string( v.m_normal );
	}
	if( mesh.m_have_uv ) {
  	  out << " / " << glm::to_string( v.m_uv );
	}
  }

*/
  out << "}";
  return out;
}

Intersect Mesh::intersect(glm::vec3 rayDir, glm::vec3 rayPos, glm::mat4 trans) {
	std::vector<glm::vec3> transformedVertices;
        for(std::vector<glm::vec3>::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it) {
                transformedVertices.push_back(transformPoint1(*it, trans));
        }
	return Primitive::intersectPolygon(rayDir, rayPos, transformedVertices, m_faces);
}

