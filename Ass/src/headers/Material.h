#pragma once

#include "Shader.h"
#include <glm/glm.hpp>

struct Material
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    Material(const Material& other);
    Material(
        glm::vec3 ambient = glm::vec3(1.0f, 0.5f, 0.31f),
        glm::vec3 diffuse = glm::vec3(1.0f, 0.5f, 0.31f),
        glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f),
        float shininess = 32.0f
    );
    ~Material();

    void operator = (const Material& other);

    void SetUniforms(Shader& shader) const;
};
