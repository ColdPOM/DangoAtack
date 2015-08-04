#version 400 core

in vec4 Frag_color;

layout (location = 0) out vec4 flag_color;
 
void main(){
    flag_color = Frag_color;
}