#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colorIn;

out vec3 colorOut;

void main()
{
    gl_Position = vec4(position, 1.0f);
    colorOut = colorIn;
}
