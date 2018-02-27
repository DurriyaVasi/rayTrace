#pragma once

#include "SceneNode.hpp"
#include "Primitive.hpp"
#include "Material.hpp"
#include "intersect.cpp"

class GeometryNode : public SceneNode {
public:
	GeometryNode( const std::string & name, Primitive *prim, 
		Material *mat = nullptr );

	void setMaterial( Material *material );

	Material *m_material;
	Primitive *m_primitive;
	virtual Intersect intersect(glm::vec3 rayDir, glm::vec3 rayPos);
};
