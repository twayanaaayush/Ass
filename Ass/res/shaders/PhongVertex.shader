#version 330 core

layout(location = 0) in vec3 aPos;

varying vec3 ec_pos;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    ec_pos = vec3(view * model * vec4(aPos, 1.0));
}