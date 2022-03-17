#include "Spring.h"
#include <cmath>

Spring::Spring(std::shared_ptr<Particle> endOne, std::shared_ptr<Particle> endTwo)
	:m_SpringConstant(SPRING_CONSTANT)
{
	m_EndOne = endOne;
	m_EndTwo = endTwo;

	m_RestLength = glm::sqrt(
		pow(((*endOne).GetPosition().x - (*endTwo).GetPosition().x), 2) +
		pow(((*endOne).GetPosition().y - (*endTwo).GetPosition().y), 2) +
		pow(((*endOne).GetPosition().z - (*endTwo).GetPosition().z), 2)
	);
}

Spring::~Spring() {}

void Spring::SetRestLength(float length)
{
	m_RestLength = length;
}

void Spring::SetSpringConstant(float k)
{
	m_SpringConstant = k;
}

void Spring::SetNormalVector(glm::vec3 normal)
{
	m_NormalVec = normal;
}
