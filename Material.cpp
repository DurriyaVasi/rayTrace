#include "Material.hpp"

Material::Material(glm::vec3 kd, glm::vec3 ks, float shininess)
{
	this->kd = kd;
	this->ks =  ks;
	this->shininess = shininess;
}

Material::~Material()
{}
