#pragma once

constexpr int GRAVITY = 9.8;

class Particle
{
private:
	float m_Mass, m_Velocity, m_Position, m_ForceAccumulated;
	bool m_Gravity = false;
public:
	Particle() = default;
	Particle(const Particle& other);
	Particle(float mass, float velocity, float position);

	void InitDefault();

	inline float GetMass() const { return m_Mass; }
	inline float GetVelocity() const { return m_Velocity; }
	inline float GetPosition() const { return m_Position; }

	void SetMass(float mass);
	void SetVelocity(float velocity);
	void SetPosition(float position);
	void CalculateForce(float force);
	void EnableGravity(bool val);

	void Update(float deltaTime);
};