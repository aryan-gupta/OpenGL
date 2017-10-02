#version 330 core

in vec2 texCord;

out vec4 FragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    FragColor = mix(texture(tex1, texCord), texture(tex2, texCord), 0.2);
    // FragColor = texture(tex1, texCord);
} 