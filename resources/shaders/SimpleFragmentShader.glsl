#version 330 core

// add
smooth in float frag_Depth;
in vec3 frag_Position;
// end

in vec4 mycolor;

out vec4 color;

void main(){
    color = mycolor;
    vec3 position = frag_Position;
}