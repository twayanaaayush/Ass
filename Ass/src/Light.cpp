#include "Light.h"

Light::Light(const Light& other)
{
	position = other.position;
	ambient = other.ambient;
	diffuse = other.diffuse;
	specular = other.specular;
}

Light::Light(
	glm::vec3 position,
	glm::vec3 ambient,
	glm::vec3 diffuse,
	glm::vec3 specular
):position(position), ambient(ambient), diffuse(diffuse), specular(specular)
{}

void Light::operator=(const Light& other)
{
	position = other.position;
	ambient = other.ambient;
	diffuse = other.diffuse;
	specular = other.specular;
}

Light::~Light() {}

void Light::SetUniforms(Shader& shader) const
{
	shader.Use();
	shader.SetUniformVec3f("light.position", position);
	shader.SetUniformVec3f("light.ambient", ambient);
	shader.SetUniformVec3f("light.diffuse", diffuse);
	shader.SetUniformVec3f("light.specular", specular);
}
