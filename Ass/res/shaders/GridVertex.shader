#version 330 core

layout(location = 0) in vec3 aPos;   // the position variable has attribute position 0

uniform float nearPlane, farPlane;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) out float near;
layout(location = 1) out float far;
layout(location = 2) out vec3 nearPoint;
layout(location = 3) out vec3 farPoint;
layout(location = 4) out mat4 fragView;
layout(location = 8) out mat4 fragProj;

vec3 unprojectPoint(float x, float y, float z, mat4 view, mat4 projection)
{
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint = viewInv * projInv * vec4(x, y, z, 1.0);

    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main()
{
    nearPoint = unprojectPoint(aPos.x, aPos.y, 0.0, view, projection).xyz;
    farPoint = unprojectPoint(aPos.x, aPos.y, 1.0, view, projection).xyz;

    fragView = view;
    fragProj = projection;

    near = nearPlane;
    far = farPlane;

    gl_Position = vec4(aPos, 1.0);
}