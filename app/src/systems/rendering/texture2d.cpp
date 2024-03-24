#pragma once 

#include "../../../headers/systems/rendering/render.h"
#include "../../../headers/utility/debug.h"
#include "../../../headers/utility/resources.h"
#include <glad/glad.h>
#include <stb/stb_image.h>

using namespace Vizzy;



void  Texture2D::load_image(const char* _filename) {
	
	//generates textures in open-gl and binds it as the current tex
	glGenTextures(1, &refID);
	glBindTexture(GL_TEXTURE_2D, refID);

	// set the texture wrapping/filtering options (on the currently bound texture object)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	unsigned char* data = stbi_load(_filename, &width, &height, &nrChannels, 0);

	//sets whether alpha is present or not
	texFormat = (nrChannels > 3) ? GL_RGBA : GL_RGB;

	if (data)
		glTexImage2D(GL_TEXTURE_2D, 0, this->texFormat, this->width, this->height, 0, this->texFormat, GL_UNSIGNED_BYTE, data);
	else 
		Debug::log("Failed to load texture : ");

	//frees up the tempdata after upload
	stbi_image_free(data);

	glUseProgram(Resources::GetShader("default-shader"));
	glUniform1i(glGetUniformLocation(Resources::GetShader("default-shader"), "texture1"), 0);

	Debug::log("Loaded Texture : ","\n -filename: ", _filename, "\n -w: ", width, " \n -h: ", height, " \n -format (RGB: 6407): ", texFormat, "\n -refID: ", refID);

};