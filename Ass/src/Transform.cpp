#include "Transform.h"

Transform::Transform(glm::vec3 pos)
{
	m_Pos = pos;
	UpdateModelMatrix();
}

Transform::Transform(const Transform& other)
{
	m_Scale = other.m_Scale;
	m_Translate = other.m_Translate;
	m_RotateX = other.m_RotateX;
	m_RotateY = other.m_RotateY;
	m_RotateZ = other.m_RotateZ;
	
	UpdateModelMatrix();
}

Transform::Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotate, glm::vec3 translate)
	:m_Pos(pos),
	 m_Scale(scale),
	 m_RotateX(rotate.x),
	 m_RotateY(rotate.y),
	 m_RotateZ(rotate.z),
	 m_Translate(translate)
{
	UpdateModelMatrix();
}

void Transform::UpdateModelMatrix()
{
	m_Pos = m_Translate;

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::scale(model, m_Scale);
	model = glm::translate(model, m_Pos);
	model = glm::rotate(model, glm::radians(m_RotateX), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_RotateY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_RotateZ), glm::vec3(0.0f, 0.0f, 1.0f));

	m_ModelMatrix = model;
}

void Transform::ToOrigin()
{
	m_Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	UpdateModelMatrix();
}

void Transform::operator=(const Transform& other)
{
	m_Scale = other.m_Scale;
	m_RotateX = other.m_RotateX;
	m_RotateY = other.m_RotateY;
	m_RotateZ = other.m_RotateZ;
	m_Translate = other.m_Translate;

	UpdateModelMatrix();
}

void Transform::SetScale(glm::vec3 factor)
{
	m_Scale = factor;
	UpdateModelMatrix();
}

void Transform::SetRotation(glm::vec3 angle)
{
	m_RotateX = angle.x;
	m_RotateY = angle.y;
	m_RotateZ = angle.z;

	UpdateModelMatrix();
}

void Transform::SetTranslation(glm::vec3 factor)
{
	m_Translate = factor;
	UpdateModelMatrix();
}

void Transform::Scale_X(float factor)
{
	m_Scale = glm::vec3(factor, m_Scale.y, m_Scale.z);
	UpdateModelMatrix();
}

void Transform::Scale_Y(float factor)
{
	m_Scale = glm::vec3(m_Scale.x, factor, m_Scale.z);
	UpdateModelMatrix();
}

void Transform::Scale_Z(float factor)
{
	m_Scale = glm::vec3(m_Scale.x, m_Scale.y ,factor);
	UpdateModelMatrix();
}

void Transform::Rotate_X(float angle)
{
	m_RotateX = angle;
	UpdateModelMatrix();
}

void Transform::Rotate_Y(float angle)
{
	m_RotateY = angle;
	UpdateModelMatrix();
}

void Transform::Rotate_Z(float angle)
{
	m_RotateZ = angle;
	UpdateModelMatrix();
}

void Transform::Translate_X(float factor)
{
	m_Translate = glm::vec3(factor, m_Translate.y, m_Translate.z);
	UpdateModelMatrix();
}

void Transform::Translate_Y(float factor)
{
	m_Translate = glm::vec3(m_Translate.x, factor, m_Translate.z);
	UpdateModelMatrix();
}

void Transform::Translate_Z(float factor)
{
	m_Translate = glm::vec3(m_Translate.x, m_Translate.y, factor);
	UpdateModelMatrix();
}
