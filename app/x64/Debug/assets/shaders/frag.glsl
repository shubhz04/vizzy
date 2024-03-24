//basic fragment shader
#version 330 core

in vec2 _texCoords;

uniform vec4 _MainColor;

uniform sampler2D _primaryTex;
uniform sampler2D _SecondaryTex;

//final output of this shader
out vec4 fragColor;
void main(){
	fragColor = texture(_primaryTex,_texCoords) *  _MainColor;
	//fragColor = vec4(_texCoords,0,1);
};