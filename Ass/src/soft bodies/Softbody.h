#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Spring.h"
#include "Particle.h"

class Softbody : public GameObject
{
private:
	std::vector<std::shared_ptr<Particle>> m_Particles;
	std::vector<std::shared_ptr<Spring>> m_Springs;

public:
	Softbody(unsigned int selector);

	void Update();

private:
	void AddParticles();
	void AddSprings();
	std::shared_ptr<Spring> MakeSpring(std::shared_ptr<Particle> endOne, std::shared_ptr<Particle> endTwo);
};