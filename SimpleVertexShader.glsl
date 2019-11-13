#version 330 core

layout(location = 0) in vec4 position;

out vec4 mycolor;

uniform mat4 u_MVP;
uniform vec4 u_color;

void main(){
    gl_Position = u_MVP * position;
    mycolor = u_color;
}