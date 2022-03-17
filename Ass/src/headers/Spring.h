#pragma once

#include <iostream>
#include "Particle.h"
#include <glm/glm.hpp>

const float SPRING_CONSTANT = 1755.0f;
const float DAMPING_CONSTANT = 35.0;

class Spring
{
private:
	float m_RestLength;
	float m_SpringConstant;
	float m_DampingConstant;
	std::shared_ptr<Particle> m_EndOne;
	std::shared_ptr<Particle> m_EndTwo;
	glm::vec3 m_NormalVec;

public:
	Spring(std::shared_ptr<Particle> endOne, std::shared_ptr<Particle> endTwo);
	~Spring();

	void SetRestLength(float length);
	void SetNormalVector(glm::vec3 normal);
	void SetSpringConstant(float k);

	inline float& GetRestLength() { return m_RestLength; }
	inline float& GetSpringConstant() { return m_SpringConstant; }
	inline float& GetDampingConstant() { return m_DampingConstant; }
	inline glm::vec3& GetNormalVec() { return m_NormalVec; }
	inline std::shared_ptr<Particle> GetEndOne() const { return m_EndOne; }
	inline std::shared_ptr<Particle> GetEndTwo() const { return m_EndTwo; }
};