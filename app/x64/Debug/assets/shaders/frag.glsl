//basic fragment shader
#version 330 core

in vec2 _texCoords;

uniform vec4 _MainColor;
uniform sampler2D _PrimaryTex;
uniform sampler2D _SecondaryTex;


uniform float radius;
uniform vec2 center;
uniform vec2 size = vec2(800,600);

//customize sdf

//final output of this shader
out vec4 fragColor;

float sdf_circle(vec2 _samplePos,vec2 _center,float _radius){
	
	//length from origin of uv space
	float currLen =  length((_samplePos - _center) * (1/_radius));
	
	//inverts the color
	currLen  =  1 - currLen;

	//now colors fade in starting from 1 -- 0.9 -- 0.8 -- ... - 0
	//so we want to make the gradient high , so scale the factors by 100-200, 
	//values less than 1 will get more squashed creaeting a definite border
	currLen *= 100;

	//normalizes the value again by clamping
	currLen = clamp(currLen,0,1);
	return currLen ;
};


void main(){
	//fragColor = texture(_PrimaryTex,_texCoords) ;
	vec2 scaledTexCoords =  normalize(size) * _texCoords;
	float mask = sdf_circle ( scaledTexCoords, center, radius);

	vec4 baseLayer = texture(_PrimaryTex, _texCoords) * vec4(mask);
	vec4 topLayer = texture(_SecondaryTex, _texCoords) * vec4(1 - mask);

	fragColor = baseLayer + topLayer;
};