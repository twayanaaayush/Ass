#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
private:
	glm::vec3 m_Scale;
	glm::vec3 m_Rotate;
	glm::vec3 m_Translate;
	glm::mat4 m_ModelMatrix;

public:
	Transform() = default;
	Transform(const Transform& other);
	Transform(glm::vec3 scale, glm::vec3 rotate, glm::vec3 translate);

	void InitDefault();

	void SetScale(glm::vec3 factor);
	void SetRotation(glm::vec3 angle);
	void SetTranslation(glm::vec3 factor);

	void Scale_X(float factor);			void Scale_Y(float factor);			void Scale_Z(float factor);
	void Rotate_X(float angle);			void Rotate_Y(float angle);			void Rotate_Z(float angle);
	void Translate_X(float factor);		void Translate_Y(float factor);		void Translate_Z(float factor);
	
	inline glm::mat4& GetModelMatrix() { return m_ModelMatrix; }
	inline glm::vec3& GetScale()	   { return m_Scale; }
	inline glm::vec3& GetRotation()	   { return m_Rotate; }
	inline glm::vec3& GetTranslation() { return m_Translate; }

private:
	void UpdateModelMatrix();
};