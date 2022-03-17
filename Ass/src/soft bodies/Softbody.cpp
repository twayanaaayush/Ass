#include "Softbody.h"

Softbody::Softbody(unsigned int selector, float size, unsigned int moles)
{
	// load mesh
	// 0 = sphere, 1 = cube
	if (selector == 0) m_Mesh = std::make_shared<Mesh>();
	else if (selector == 1) m_Mesh = std::make_shared<Mesh>(cube::vertices, cube::triangles);

	// load material
	m_Material = std::make_shared<Material>();

	m_Size = size;
	m_NoOfMoles = moles;

	CalculateBoundingBox();

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
	size_t size = (*m_Mesh).GetIndices().size();
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
	//std::cout << (*spring).GetRestLength() << std::endl;
	return spring;
}

void Softbody::Update(bool BEGIN_SIMULATION, float g_rotX_angle, float g_rotY_angle)
{
	GameObject::Update(BEGIN_SIMULATION, g_rotX_angle, g_rotY_angle);
	
	if (BEGIN_SIMULATION)
	{
		//std::vector<Vertex> vertices;

		// main logic
		AddGravityForce();
		AddSpringForce();
		CalculateVolume();
		CalculatePressureValue();
		CalculatePressureForce();

		//for (auto it = m_Particles.begin(); it != m_Particles.end(); ++it)
		//{
		//	(**it).SetVelocity(glm::vec3(0.0f, -0.0098f, 0.0f));
		//	(**it).Update();
		//	vertices.push_back({ (**it).GetPosition() });
		//}

		//(*m_Mesh).SetVertices(vertices);
	}
}

void Softbody::SetPressureValue(float pressureVal)
{
	m_PressureValue = pressureVal;
}

void Softbody::SetNoOfMoles(unsigned int n)
{
	m_NoOfMoles = n;
}

void Softbody::AddGravityForce()
{
	for (auto it = m_Particles.begin(); it != m_Particles.end(); ++it)
	{
		float fx = 0;
		float fy = (**it).GetMass() * -9.8f; // include only when pressure variation, i.e. (Pressure - FINAL_PRESSURE >= 0);
		float fz = 0;
		(**it).AddForce(glm::vec3(fx, fy, fz));
	}
}

void Softbody::AddSpringForce()
{
	for (auto it = m_Springs.begin(); it != m_Springs.end(); ++it)
	{
		std::shared_ptr<Particle> particle1 = (**it).GetEndOne();
		std::shared_ptr<Particle> particle2 = (**it).GetEndTwo();

		glm::vec3 p1p = (*particle1).GetPosition();
		glm::vec3 p2p = (*particle2).GetPosition();

		// positions for 2 particles of the spring
		float x1 = p1p.x;
		float y1 = p1p.y;
		float z1 = p1p.z;

		float x2 = p2p.x;
		float y2 = p2p.y;
		float z2 = p2p.z;

		// distance between the particles
		float r12d = glm::sqrt(
			pow((x1 - x2), 2) +
			pow((y1 - y2), 2) +
			pow((z1 - z2), 2)
		);

		if (r12d != 0)
		{
			glm::vec3 p1v = (*particle1).GetVelocity();
			glm::vec3 p2v = (*particle2).GetVelocity();

			// relative velocity of 2 partices of the spring
			float vx12 = p1v.x - p2v.x;
			float vy12 = p1v.y - p2v.y;
			float vz12 = p1v.z - p2v.z;

			// calculate force value
			float f = (r12d - (**it).GetRestLength()) * (**it).GetSpringConstant() +
				((vx12 * (x1 - x2) + vy12 * (y1 - y2) + vz12 * (z1 - z2)) * (**it).GetDampingConstant()) / r12d;

			// calculate force vector
			float Fx = ((x1 - x2) / r12d) * f;
			float Fy = ((y1 - y2) / r12d) * f;
			float Fz = ((z1 - z2) / r12d) * f;

			(*particle1).AddForce(glm::vec3(-Fx, -Fy, -Fz));
			(*particle2).AddForce(glm::vec3(Fx, Fy, Fz));

			/*std::cout << Fx << "," << Fy << "," << Fz << std::endl;

			std::cout << "Particle 1: " << (*particle1).GetForceAccumulated().x
				<< "," << (*particle1).GetForceAccumulated().y
				<< "," << (*particle1).GetForceAccumulated().z
				<< std::endl;

			std::cout << "Particle 2: " << (*particle2).GetForceAccumulated().x
				<< "," << (*particle2).GetForceAccumulated().y
				<< "," << (*particle2).GetForceAccumulated().z
				<< std::endl;*/
		}

		// calculate normal vectors for the spring
		float nx = (x1 - x2) / r12d;
		float ny = (y1 - y2) / r12d;
		float nz = (z1 - z2) / r12d;
		(**it).SetNormalVector(glm::vec3(nx, ny, nz));

		//std::cout << (**it).GetNormalVec().x << "," << (**it).GetNormalVec().y << "," << (**it).GetNormalVec().z << std::endl;
	}
}

float Softbody::CalculateVolume()
{
	float dx = m_BoundingBox[1].x - m_BoundingBox[0].x;
	float dy = m_BoundingBox[1].y - m_BoundingBox[0].y;
	float dz = m_BoundingBox[1].z - m_BoundingBox[0].z;

	float volume = dx * dy * dz;
	//std::cout << volume;
	m_Volume = volume;
	return volume;
}

void Softbody::CalculatePressureForce()
{
	// loop over all the faces
	for (auto face = (*m_Mesh).GetIndices().begin(); face != (*m_Mesh).GetIndices().end(); ++face)
	{
		glm::vec3 crossProduct = CalculateCrossProduct(*face);
		glm::vec3 normalToSurface = glm::normalize(crossProduct);
		
		float magnitude = glm::sqrt(
			pow(crossProduct.x, 2) +
			pow(crossProduct.y, 2) +
			pow(crossProduct.z, 2)
		);

		float area = 0.5 * magnitude;

		for (unsigned int i = 0; i < (*face).GetVertexCount(); ++i)
		{
			std::shared_ptr<Particle> particle = m_Particles[(*face).vertex[i]];
			glm::vec3 pressureForce = m_PressureValue * area * normalToSurface;

			(*particle).AddForce(pressureForce);
		}
	}
}

glm::vec3 Softbody::CalculateCrossProduct(const Triangle& face)
{
	std::vector<Vertex> vertices = (*m_Mesh).GetVertices();

	glm::vec3 v1 = vertices[face.vertex[0]].Position;
	glm::vec3 v2 = vertices[face.vertex[1]].Position;
	glm::vec3 v3 = vertices[face.vertex[2]].Position;

	glm::vec3 crossProduct = glm::cross((v2 - v1), (v3 - v1));

	return crossProduct;
}

float Softbody::CalculatePressureValue()
{
	float pressureValue = (1 / m_Volume) * m_NoOfMoles * R; // temp const, i.e 1

	m_PressureValue = pressureValue;

	return pressureValue;
}
