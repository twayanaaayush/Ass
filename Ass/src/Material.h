#pragma once

#include <glm/glm.hpp>

struct Material
{
    // object color
    glm::vec3 color;

    // strength value
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};