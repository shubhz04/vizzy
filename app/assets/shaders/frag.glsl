//basic fragment shader
#version 330 core

in vec2 _texCoords;

uniform vec4 _MainColor;

uniform sampler2D texture1;

//final output of this shader
out vec4 fragColor;
void main(){
	fragColor = texture(texture1,_texCoords) ;
	//fragColor = vec4(_texCoords,0,1);
};