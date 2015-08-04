#version 400 core

uniform mat4 modelMatrix;

in vec3 Vertex;
in vec2 UV;

out vec2 uv;

void main(){
	gl_Position = modelMatrix * vec4(Vertex, 1.0);
	uv = UV;
}