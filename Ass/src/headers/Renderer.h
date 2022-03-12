#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Light.h"
#include "Shader.h"
#include "Camera.h"

template <typename T>
using RenderObjects = std::shared_ptr<std::vector<std::unique_ptr<T>>>;

template <typename T>
class Renderer
{
private:
	RenderObjects<T> m_RenderObjects;
	std::shared_ptr<Light> m_Light;
    std::shared_ptr<Shader> m_WireframeShader;
    std::shared_ptr<Shader> m_SolidShader;
	std::shared_ptr<Shader> m_ActiveShader;

public:
	Renderer(RenderObjects<T> renderObjects);
	Renderer(RenderObjects<T> renderObjects, std::shared_ptr<Light> light);
	~Renderer();

	void AddShader(std::shared_ptr<Shader> shader);
    void EnableWireframe();
    void DisableWireframe();
	void UpdateAll(float g_rotX_angle, float g_rotY_angle);
	void RenderAll(Camera& camera);
};



template <typename T>
Renderer<T>::Renderer(RenderObjects<T> renderObjects)
{
    m_RenderObjects = renderObjects;

    std::shared_ptr<Shader> wireframeShader =
    std::make_shared<Shader>("res/shaders/BasicVertex.shader", "res/shaders/BasicFragment.shader");
 
    m_WireframeShader = wireframeShader;
    m_ActiveShader = wireframeShader;
}

template <typename T>
Renderer<T>::Renderer(RenderObjects<T> renderObjects, std::shared_ptr<Light> light)
{
    m_RenderObjects = renderObjects;
    m_Light = light;

    std::shared_ptr<Shader> wireframeShader =
        std::make_shared<Shader>("res/shaders/BasicVertex.shader", "res/shaders/BasicFragment.shader");

    m_WireframeShader = wireframeShader;
    m_ActiveShader = wireframeShader;
}

template <typename T>
Renderer<T>::~Renderer()
{}

template <typename T>
void Renderer<T>::AddShader(std::shared_ptr<Shader> shader)
{
    m_SolidShader = shader;
    m_ActiveShader = shader;
}

template <typename T>
void Renderer<T>::EnableWireframe()
{
    m_ActiveShader = m_WireframeShader;

}

template <typename T>
void Renderer<T>::DisableWireframe()
{
    m_ActiveShader = m_SolidShader;
}

template <typename T>
void Renderer<T>::UpdateAll(float g_rotX_angle, float g_rotY_angle)
{
    for (auto it = (*m_RenderObjects).begin(); it != (*m_RenderObjects).end(); ++it)
    {
        //Update
        (**it).Update(g_rotX_angle, g_rotY_angle);
    }
}

template <typename T>
void Renderer<T>::RenderAll(Camera& camera)
{
    for (auto it = (*m_RenderObjects).begin(); it != (*m_RenderObjects).end(); ++it)
    {
        //Set Uniforms
        if (m_ActiveShader == m_WireframeShader)
        {
            (*m_WireframeShader).Use();
            (*m_WireframeShader).SetUniformVec4f("color", glm::vec4(1.0f, 0.5f, 0.31f, 1.0f));
            camera.SetUniforms(*m_ActiveShader, (**it).GetTransform().GetModelMatrix());
        }
        else
        {
            (*m_Light).SetUniforms(*m_ActiveShader);
            camera.SetUniformViewPos(*m_ActiveShader);
            (**it).GetMaterial().SetUniforms(*m_ActiveShader);

            camera.SetUniforms(*m_ActiveShader, (**it).GetTransform().GetModelMatrix());
        }

        //Render
        (**it).Draw();
    }
}
