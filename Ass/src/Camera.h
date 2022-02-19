#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Cam
{
	enum class Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.5f;
	const float ZOOM = 45.0f;
}

class Camera
{
private:
	glm::vec3 m_InitialPos;
	glm::vec3 m_InitialUp;

	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	float m_Yaw;
	float m_Pitch;

	float m_MovementSpeed;
	float m_MouseSensitivity;
	float m_Zoom;

public:
	//Camera() = default;
	Camera( glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		    float yaw = Cam::YAW,
			float pitch = Cam::PITCH );

	glm::mat4 GetViewMatrix();

	void ProcessKeyboard(Cam::Camera_Movement direction, double deltaTime);
	void ProcessMouseMovement(double xoffset, double yoffset, double deltaTime, bool constrainPitch = true);
	void ProcessMouseScroll(double yoffset);
	void ResetPosition();

	inline float GetMovementSpeed() const { return m_MovementSpeed; }
	inline float GetMouseSensitivity() const { return m_MouseSensitivity; }
	inline float GetZoom() const { return m_Zoom; }
	inline glm::vec3 GetPosition() const { return m_Position; }

private:
	void UpdateCameraVectors();
};
