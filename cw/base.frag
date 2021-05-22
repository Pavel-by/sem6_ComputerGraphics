#version 150 core

in vec3 frag_normal;
in vec4 frag_color;
in vec3 frag_position;

uniform vec3 lightColor;
uniform vec3 lightPosition;

void main(void)
{
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(frag_normal);
    vec3 lightDir = normalize(frag_position - lightPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    gl_FragColor = vec4((ambient + diffuse), 1.0) * frag_color;
}
