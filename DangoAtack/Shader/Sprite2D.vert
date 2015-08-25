#version 400 core

in vec3 Vertex;
in vec2 UV;

uniform mat4 modelMatrix;
uniform vec2 ReducadScale;

out vec2 uv;

void main(){
	gl_Position = modelMatrix * (vec4(Vertex, 1.0) * vec4(ReducadScale, 1.0, 1.0));
	uv = UV;
}