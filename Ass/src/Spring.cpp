#include "Spring.h"

Spring::Spring(Particle* endOne, Particle* endTwo):m_RestLength(0),m_SpringConstant(0)
{
	m_EndOne = endOne;
	m_EndTwo = endTwo;
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
