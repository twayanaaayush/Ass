#pragma once

#include <iostream>
#include "Particle.h"
#include <glm/glm.hpp>

const int SPRING_CONSTANT = 0.1;

class Spring
{
private:
	float m_RestLength;
	std::shared_ptr<Particle> m_EndOne;
	std::shared_ptr<Particle> m_EndTwo;
	float m_SpringConstant;
	glm::vec3 m_NormalVec;

public:
	Spring(std::shared_ptr<Particle> endOne, std::shared_ptr<Particle> endTwo);
	~Spring();

	void SetRestLength(float length);
	void SetSpringConstant(float k);

	inline float GetRestLength() const { return m_RestLength; }
	inline float GetSpringConstant() const { return m_SpringConstant; }
	inline glm::vec3 GetNormalVec() const { return m_NormalVec; }
};