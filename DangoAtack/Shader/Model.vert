#version 400 core

uniform mat4 pvmMatrix;

in vec3 Vertex;
in vec3 Normal;
in vec2 UV;

out vec3 normal;
out vec2 uv;

void main(){
	gl_Position = pvmMatrix * vec4(Vertex, 1.0);
	normal = Normal;
	uv = UV;
}