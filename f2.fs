#version 330 core
out vec4 FragColor;

in vec2 texCord;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    FragColor = vec4(1.0f, 0.3f, 0.7f, 1.0);
}