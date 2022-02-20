#pragma once

#include "Shader.h"
#include <glm/glm.hpp>

class Material
{
private:
    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    glm::vec3 m_Specular;
    float m_Shininess;

public:
    Material(const Material& other);
    Material(
        glm::vec3 ambient = glm::vec3(1.0f, 0.5f, 0.31f),
        glm::vec3 diffuse = glm::vec3(1.0f, 0.5f, 0.31f),
        glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f),
        float shininess = 32.0f
    );
    ~Material();

    Material& operator = (const Material& other);

    void SetAmbient(glm::vec3 ambient);
    void SetDiffuse(glm::vec3 diffuse);
    void SetSpecular(glm::vec3 specular);
    void SetShininess(glm::vec3 shininess);

    void SetUniforms(Shader& shader) const;

    inline glm::vec3 GetAmbient() const { return m_Ambient; }
    inline glm::vec3 GetDiffuse() const { return m_Diffuse; }
    inline glm::vec3 GetSpecular() const { return m_Specular; }
    inline float GetShininess() const { return m_Shininess; }
};
