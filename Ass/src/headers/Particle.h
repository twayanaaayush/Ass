#pragma once

#include <glm/glm.hpp>

const float PARTICLE_MASS = 1.0f;

class Particle
{
private:
	float m_Mass;
	glm::vec3 m_Velocity;
	glm::vec3 m_Position;
	glm::vec3 m_ForceAccumulated;

public:
	Particle() = default;
	Particle(const Particle& other);
	Particle(float mass, glm::vec3 velocity, glm::vec3 position);
	Particle(glm::vec3 position);

	inline float GetMass() const { return m_Mass; }
	inline glm::vec3& GetVelocity() { return m_Velocity; }
	inline glm::vec3& GetPosition() { return m_Position; }
	inline glm::vec3& GetForceAccumulated() { return m_ForceAccumulated; }

	void SetMass(float mass);
	void SetVelocity(glm::vec3 velocity);
	void SetPosition(glm::vec3 position);
	void AddForce(glm::vec3 force);

	void Update();
};