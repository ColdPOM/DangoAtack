#version 400 core

uniform sampler2D Texture;
uniform mat4 modelMatrix;
uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform float time;

in vec3 normal;
in vec2 uv;

layout (location = 0) out vec4 flag_color;

vec4 light = vec4(1, 1, -1, 0);

// óêêîê∂ê¨
float rnd(vec2 p){
    return fract(sin(dot(p ,vec2(12.9898,78.233))) * 43758.5453);
}
 
void main(){
	float cos = clamp(dot(normalize(modelMatrix * vec4(normal, 0)), normalize(light)), 0, 1);
	vec4 color = ambientColor + diffuseColor * cos;

    flag_color = texture2D(Texture, uv) * color;
}