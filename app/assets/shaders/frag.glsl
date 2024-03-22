//basic fragment shader
#version 330 core

in vec2 _texCoords;

uniform vec4 _MainColor;

//final output of this shader
out vec4 fragColor;
void main(){
	fragColor = _MainColor;
};