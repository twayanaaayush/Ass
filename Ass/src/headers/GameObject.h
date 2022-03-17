#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

class GameObject
{
protected:
	std::shared_ptr<Mesh> m_Mesh;
	std::shared_ptr<Material> m_Material;
	Transform m_Transform;
	glm::vec3 m_BoundingBox[2];	//idx-0 = minVals, idx-1 = maxVals
	float m_Size;

public:
	GameObject() = default;
	GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const Transform& transform);
	GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
	GameObject(std::shared_ptr<Mesh> mesh);
	~GameObject();

	void SetMesh(std::shared_ptr<Mesh> mesh);
	void SetMaterial(std::shared_ptr<Material> material);
	void SetTransform(const Transform& transform);
	void SetSize(float size);

	void CalculateBoundingBox();

	inline Mesh& GetMesh() { return *m_Mesh; }
	inline Material& GetMaterial() { return *m_Material; }
	inline Transform& GetTransform() { return m_Transform; }
	inline float& GetSize() { return m_Size; }

	void Update(bool BEGIN_SIMULATION, float g_rotX_angle, float g_rotY_angle);
	void Draw();
};