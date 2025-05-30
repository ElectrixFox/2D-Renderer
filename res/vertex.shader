#version 430 core
layout (location = 0) in vec3 pos;

uniform mat4 projection;
uniform mat4 model;

void main()
{
gl_Position = transpose(model * projection) * vec4(pos, 1.0);
}