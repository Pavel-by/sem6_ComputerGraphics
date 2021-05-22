#version 150 core

in vec3 vertex;
in vec4 color;
in vec3 normal;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec3 frag_normal;
out vec4 frag_color;
out vec3 frag_position;

void main(void)
{
    gl_Position = proj * view * model * vec4(vertex, 1.0);
    frag_normal = mat3(transpose(inverse(model))) * normal;
    frag_color = color;
    frag_position = vec3(gl_Position);
}
