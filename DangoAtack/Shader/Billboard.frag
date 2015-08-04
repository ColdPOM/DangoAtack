#version 400 core

uniform sampler2D Texture;

in vec2 uv;

layout (location = 0) out vec4 flag_color;

 
void main(){
    flag_color = texture2D(Texture, uv);
}