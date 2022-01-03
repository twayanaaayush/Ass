#version 330 core

in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 lightPos;
//uniform vec3 objectColor;
uniform vec3 lightColor;

struct Material
{
    // object color
    vec3 color;

    // strength value
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main()
{
    // ambient light
    //float ambientStrength = 0.1;
    vec3 ambientLight = material.ambient * lightColor;

    // diffuse light
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseLight = lightColor * (diff * material.diffuse);

    // specular light
    //float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularLight = lightColor * (spec * material.specular);

    vec3 resultingLight = (ambientLight + diffuseLight + specularLight) * material.color;
    FragColor = vec4(resultingLight, 1.0);
}