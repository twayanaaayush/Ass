#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

class GameObject
{
private:
	Mesh* m_Mesh = nullptr;
	Material* m_Material = nullptr;
	Transform m_Transform;
public:
	GameObject() = default;
	GameObject(Mesh* mesh, Material* material, Transform transform);
	~GameObject();

	void SetMesh(Mesh* mesh);
	void SetMaterial(Material* material);
	void SetTransform(Transform transform);

	inline Mesh* GetMesh() const { return m_Mesh; }
	inline Material* GetMaterial() const { return m_Material; }
	inline Transform GetTransform() { return m_Transform; }

	void Update();
	void Draw();
};