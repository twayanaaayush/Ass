#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
private:
	glm::vec3 m_Scale;
	glm::vec3 m_Rotate;
	glm::vec3 m_Translate;
	glm::mat4 ModelMatrix;

public:
	Transform() = default;
	Transform(const Transform& other);
	Transform(glm::vec3 scale, glm::vec3 rotate, glm::vec3 translate);

	void InitDefault();

	void Scale_X(float factor);			void Scale_Y(float factor);			void Scale_Z(float factor);
	void Rotate_X(float factor);		void Rotate_Y(float factor);		void Rotate_Z(float factor);
	void Translate_X(float factor);		void Translate_Y(float factor);		void Translate_Z(float factor);

	inline const glm::mat4& GetModelMatrix() const { return ModelMatrix; }
private:
	void UpdateModelMatrix();
};