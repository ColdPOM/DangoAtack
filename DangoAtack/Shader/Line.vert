#version 400 core

uniform mat4 pvmMatrix;

in vec3 Vertex;
in vec3 Color;

out vec4 Frag_color;

void main(){
	gl_Position = pvmMatrix * vec4(Vertex, 1.0);
	Frag_color = vec4(Color, 1.0);
}