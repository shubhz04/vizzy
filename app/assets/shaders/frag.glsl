//basic fragment shader
#version 330 core

in vec2 _texCoords;


//final output of this shader
out vec4 fragColor;
void main(){
	fragColor = vec4(0.2f,0.3f,0.4f,1);
};