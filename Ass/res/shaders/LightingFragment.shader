#version 330 core

in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    // ambient light
    float ambientStrength = 0.1;
    vec3 ambientLight = ambientStrength * lightColor;

    // diffuse light
    vec3 normal = normalize(Normal); //redundant but ok
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseLight = diff * lightColor;

    // specular light
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specularLight = specularStrength * spec * lightColor;

    vec3 resultingLight = (ambientLight + diffuseLight + specularLight) * objectColor;
    FragColor = vec4(resultingLight, 1.0);
}