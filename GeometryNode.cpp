#include "GeometryNode.hpp"

//---------------------------------------------------------------------------------------
GeometryNode::GeometryNode(
	const std::string & name, Primitive *prim, Material *mat )
	: SceneNode( name )
	, m_material( mat )
	, m_primitive( prim )
{
	m_nodeType = NodeType::GeometryNode;
}

void GeometryNode::setMaterial( Material *mat )
{
	// Obviously, there's a potential memory leak here.  A good solution
	// would be to use some kind of reference counting, as in the 
	// C++ shared_ptr.  But I'm going to punt on that problem here.
	// Why?  Two reasons:
	// (a) In practice we expect the scene to be constructed exactly
	//     once.  There's no reason to believe that materials will be
	//     repeatedly overwritten in a GeometryNode.
	// (b) A ray tracer is a program in which you compute once, and 
	//     throw away all your data.  A memory leak won't build up and
	//     crash the program.

	m_material = mat;
}

Intersect GeometryNode::intersect(glm::vec3 rayDir, glm::vec3 rayPos) {
        Intersect i = m_primitive->intersect(rayDir, rayPos);
	i.kd = m_material->kd;
	i.ks = m_material->ks;
	i.shininess = m_material->shininess;
	Intersect i2 = SceneNode::intersect(rayDir, rayPos);
	i2.kd = m_material->kd;
        i2.ks = m_material->ks;
        i2.shininess = m_material->shininess;
	if (!i.hit && !i2.hit) {
		return Intersect();
	}
	else if (i.hit && !i2.hit) {
		return i;
	}
	else if (i2.hit && !i.hit) {
		return i2;
	}
	else if (i.hit && i2.hit) {
		if (i.t < i2.t) {
			return i;
		}
		else {
			return i2;
		}
	}
}
