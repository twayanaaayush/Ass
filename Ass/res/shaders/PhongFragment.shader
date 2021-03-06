#version 330 core

in vec3 FragPos;
out vec4 FragColor;
varying vec3 ec_pos;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
    vec3 ec_normal = cross(dFdx(ec_pos), dFdy(ec_pos));

    // ambient light
    //float ambientStrength = 0.1;
    vec3 ambientLight = light.ambient * material.ambient;

    // diffuse light
    vec3 normal = normalize(ec_normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseLight = light.diffuse * (diff * material.diffuse);

    // specular light
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularLight = light.specular * (spec * material.specular);

    vec3 resultingLight = ambientLight + diffuseLight + specularLight;
    //vec3 resultingLight = ambientLight + diffuseLight;

    FragColor = vec4(resultingLight, 1.0);
}