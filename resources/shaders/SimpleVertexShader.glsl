#version 330 core

layout(location = 0) in vec4 position;

out vec4 mycolor;

// add
out vec3 frag_Position;
out float frag_Depth;
// end

uniform mat4 u_MVP;
uniform vec4 u_color;

float scalar = position.z / 20;

void main(){

    gl_Position = u_MVP * position;

    if(position.z < 0.15){
        mycolor = vec4(vec3(u_color*scalar), 1.f) ;
        mycolor = u_color;
    }
    else{
        mycolor = u_color;
    }

    // add
    frag_Position = vec3(u_MVP * position);
    frag_Depth = gl_Position.z;
    // end

}