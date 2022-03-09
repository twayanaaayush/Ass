#pragma once

#include <glm/glm.hpp>
#include "Shader.h"

struct Light
{
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Light(const Light& other);
    Light(
        glm::vec3 position = glm::vec3(2.0f, 2.0f, 2.0f),
        glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f)
    );
    ~Light();

    void operator = (const Light& other);

    void SetUniforms(Shader& shader) const;
};