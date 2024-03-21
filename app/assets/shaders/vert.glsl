//basic vertex shader for displaying tris
#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexCoords;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
out vec2 _texCoords;

void main(){

	gl_Position = vec4(vPos,1.0f);
	_texCoords = vTexCoords;
};