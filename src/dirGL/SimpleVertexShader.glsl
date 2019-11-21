#version 330 core

layout(location = 0) in vec4 position;

out vec4 mycolor;

uniform mat4 u_MVP;
uniform vec4 u_color;

float scalar = position.z / 20;

void main(){
    gl_Position = u_MVP * position;
    if(position.z < 0.1){
        mycolor = vec4(vec3(u_color*scalar), 0.9f) ;
    }
    else{
        mycolor = u_color;
    }

    //mycolor = vec4(vec3(u_color*scalar), 1.0f) ;
}