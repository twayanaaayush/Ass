#pragma once

#include "Particle.h"
#include <glm/glm.hpp>

class Spring
{
private:
	float m_RestLength;
	Particle* m_EndOne, *m_EndTwo;
	float m_SpringConstant;
	glm::vec3 m_NormalVec;

public:
	Spring(Particle* endOne, Particle* endTwo);
	~Spring();

	void SetRestLength(float length);
	void SetSpringConstant(float k);

	inline float GetRestLength() const { return m_RestLength; }
	inline float GetSpringConstant() const { return m_SpringConstant; }
	inline glm::vec3 GetNormalVec() const { return m_NormalVec; }
};