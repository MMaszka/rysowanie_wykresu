#version 330 core
in vec3 Color;

out vec4 FragColor;

uniform vec3 color;

void main()
{    
    FragColor=vec4(0.5f, 0.9f, 0.4f,1.0f);
}