#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Spring.h"
#include "Particle.h"

const float R = 8.3145;

class Softbody : public GameObject
{
private:
	float m_Volume;
	float m_PressureValue;
	unsigned int m_NoOfMoles;
	std::vector<std::shared_ptr<Particle>> m_Particles;
	std::vector<std::shared_ptr<Spring>> m_Springs;

public:
	Softbody(unsigned int selector, float size = 1.0f, unsigned int moles = 100);
	void Update(bool BEGIN_SIMULATION, float g_rotX_angle, float g_rotY_angle);

	void SetPressureValue(float pressureVal);	// set pressure value, no need for calculation
	void SetNoOfMoles(unsigned int n);

private:
	void AddGravityForce();
	void AddSpringForce();
	void AddParticles();
	void AddSprings();
	std::shared_ptr<Spring> MakeSpring(std::shared_ptr<Particle> endOne, std::shared_ptr<Particle> endTwo);
	float CalculateVolume();
	void CalculatePressureForce();
	glm::vec3 CalculateCrossProduct(const Triangle& face);
	float CalculatePressureValue();

};