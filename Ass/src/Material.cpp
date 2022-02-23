#include "Material.h"

Material::Material(const Material& other)
{
	ambient = other.ambient;
	diffuse = other.diffuse;
	specular = other.specular;
	shininess = other.shininess;
}

Material::Material(
	glm::vec3 ambient,
	glm::vec3 diffuse,
	glm::vec3 specular,
	float shininess
):ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) 
{}

void Material::operator=(const Material& other)
{
	ambient = other.ambient;
	diffuse = other.diffuse;
	specular = other.specular;
	shininess = other.shininess;
}

Material::~Material() {}

void Material::SetUniforms(Shader& shader) const
{
	shader.Use();
	shader.SetUniformVec3f("material.ambient", ambient);
	shader.SetUniformVec3f("material.diffuse", diffuse);
	shader.SetUniformVec3f("material.specular", specular);
	shader.SetUniform1f("material.shininess", shininess);
}
