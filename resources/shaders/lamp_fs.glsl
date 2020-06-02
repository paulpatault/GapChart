#version 330 core

uniform vec3 u_color;

out vec4 FragColor;


void main()
{
    FragColor = vec4(u_color, 1.0); // set alle 4 vector values to 1.0
}