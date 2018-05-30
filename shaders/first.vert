#version 430 core

uniform mat4 transform;
uniform mat4 proj;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colorIn;

out vec3 colorOut;
out vec3 positionOut;

void main()
{
    gl_Position = transform * vec4(position, 1.0f);
    colorOut = colorIn;
    positionOut = position;
}
