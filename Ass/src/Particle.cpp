#include "Particle.h"

Particle::Particle(const Particle& other)
{
	m_Mass = other.m_Mass;
	m_Velocity = other.m_Velocity;	
	m_Position = other.m_Position;
	m_ForceAccumulated = other.m_ForceAccumulated;
}

Particle::Particle(float mass, glm::vec3 velocity, glm::vec3 position)
	:m_Mass(mass), m_Velocity(velocity),
	 m_Position(position),
	 m_ForceAccumulated(glm::vec3(0.0f))
{}

Particle::Particle(glm::vec3 position)
	:m_Position(position),
	 m_Mass(PARTICLE_MASS),
	 m_Velocity(glm::vec3(0.0f)),
	 m_ForceAccumulated(glm::vec3(0.0f))
{}

void Particle::SetMass(float mass)
{
	m_Mass = mass;
}

void Particle::SetVelocity(glm::vec3 velocity)
{
	m_Velocity = velocity;
}

void Particle::SetPosition(glm::vec3 position)
{
	m_Position = position;
}

void Particle::AddForce(glm::vec3 force)
{
	m_ForceAccumulated += force;
}