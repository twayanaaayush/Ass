#include "Renderer.h"

Renderer::Renderer(RenderObjects renderObjects)
{
	m_RenderObjects = renderObjects;
}

Renderer::Renderer(RenderObjects renderObjects, std::shared_ptr<Light> light)
{
	m_RenderObjects = renderObjects;
	m_Light = light;
}

Renderer::~Renderer()
{}

void Renderer::AddShader(std::shared_ptr<Shader> shader)
{
	m_Shader = shader;
}

void Renderer::UpdateAll(float g_rotX_angle, float g_rotY_angle)
{
    for (auto it = (*m_RenderObjects).begin(); it != (*m_RenderObjects).end(); ++it)
    {
        //Update
        (**it).Update(g_rotX_angle, g_rotY_angle);
    }
}


void Renderer::RenderAll(Camera& camera)
{
    for (auto it = (*m_RenderObjects).begin(); it != (*m_RenderObjects).end(); ++it)
    {
        //Set Uniforms
        (*m_Light).SetUniforms(*m_Shader);
        camera.SetUniformViewPos(*m_Shader);
        (**it).GetMaterial().SetUniforms(*m_Shader);

        camera.SetUniforms(*m_Shader, (**it).GetTransform().GetModelMatrix());

        //Render
        (**it).Draw();


    }
}
