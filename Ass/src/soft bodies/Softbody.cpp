#include "Softbody.h"

Softbody::Softbody(unsigned int selector)
{
	// load mesh
	// 0 = cube, 1 = sphere
	if (selector == 0) m_Mesh = std::make_shared<Mesh>();
	else if (selector == 1) m_Mesh = std::make_shared<Mesh>(cube::vertices, cube::triangles);

	// load material
	m_Material = std::make_shared<Material>();

	AddParticles();
	AddSprings();
}

void Softbody::AddParticles()
{
	for (auto it = (*m_Mesh).GetVertices().begin(); it != (*m_Mesh).GetVertices().end(); ++it)
	{
		auto temp = std::make_shared<Particle>((*it).Position);
		m_Particles.push_back(std::move(temp));
	}
}

void Softbody::AddSprings()
{
	const std::vector<Triangle>& triangles = (*m_Mesh).GetIndices();
	unsigned int size = (*m_Mesh).GetIndices().size();
	for (unsigned int i = 0; i < size; ++i)
	{
		std::shared_ptr<Particle> p1 = m_Particles[triangles[i].vertex[0]];
		std::shared_ptr<Particle> p2 = m_Particles[triangles[i].vertex[1]];
		std::shared_ptr<Particle> p3 = m_Particles[triangles[i].vertex[2]];

		m_Springs.push_back(MakeSpring(p1, p2));
		m_Springs.push_back(MakeSpring(p2, p3));
		m_Springs.push_back(MakeSpring(p3, p1));

		//std::cout << x << "," << y << "," << z << std::endl;
	}
}

std::shared_ptr<Spring> Softbody::MakeSpring(std::shared_ptr<Particle> endOne, std::shared_ptr<Particle> endTwo)
{
	std::shared_ptr<Spring> spring = std::make_shared<Spring>(endOne, endTwo);
	return spring;
}

void Softbody::Update()
{

}