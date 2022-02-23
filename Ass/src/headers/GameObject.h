#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

class GameObject
{
private:
	Mesh* m_Mesh = nullptr;
	Material m_Material;
	Transform m_Transform;
public:
	GameObject() = default;
	GameObject(Mesh* mesh, const Material& material, const Transform& transform);
	GameObject(Mesh* mesh);
	~GameObject();

	void SetMesh(Mesh* mesh);
	void SetMaterial(const Material& material);
	void SetTransform(const Transform& transform);

	inline Mesh* GetMesh() const { return m_Mesh; }
	inline Material& GetMaterial() { return m_Material; }
	inline Transform& GetTransform() { return m_Transform; }

	void Update();
	void Draw();
};