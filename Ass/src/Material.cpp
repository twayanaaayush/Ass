#include "Material.h"

Material::Material(const Material& other)
{
	m_Ambient = other.GetAmbient();
	m_Diffuse = other.GetDiffuse();
	m_Specular = other.GetSpecular();
	m_Shininess = other.GetShininess();
}

Material::Material(
	glm::vec3 ambient,
	glm::vec3 diffuse,
	glm::vec3 specular,
	float shininess
)
{
	m_Ambient = ambient;
	m_Diffuse = diffuse;
	m_Specular = specular;
	m_Shininess = shininess;
}

void Material::operator=(const Material& other)
{
	m_Ambient = other.GetAmbient();
	m_Diffuse = other.GetDiffuse();
	m_Specular = other.GetSpecular();
	m_Shininess = other.GetShininess();
}

Material::~Material() {}

void Material::SetUniforms(Shader& shader) const
{
	shader.Use();
	shader.SetUniformVec3f("material.ambient", m_Ambient);
	shader.SetUniformVec3f("material.diffuse", m_Diffuse);
	shader.SetUniformVec3f("material.specular", m_Specular);
	shader.SetUniform1f("material.shininess", m_Shininess);
}

void Material::SetAmbient(glm::vec3 ambient)
{
	m_Ambient = ambient;
}

void Material::SetDiffuse(glm::vec3 diffuse)
{
	m_Diffuse = diffuse;
}

void Material::SetSpecular(glm::vec3 specular)
{
	m_Specular = specular;
}

void Material::SetShininess(float shininess)
{
	m_Shininess = shininess;
}