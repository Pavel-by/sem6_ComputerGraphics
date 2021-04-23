#version 150 core

in vec3 vertex;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main(void)
{
    gl_Position = proj * view * model * vec4(vertex, 1.0);
}
