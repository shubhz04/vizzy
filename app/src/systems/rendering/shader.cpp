#include <iostream>
#include <glad/glad.h>
#include <glad/glad.h>
#include "../../../headers/systems/rendering/render.h"
#include "../../../headers/utility/files.h"
#include "../../../headers/utility/debug.h"
#include <glm/gtc/type_ptr.hpp>

using namespace Vizzy;

Shader::Shader(const char* _vertShaderFilename, const char* _fragShaderFilename) {

	refID = glCreateProgram();


	std::string vertShaderSource = Vizzy::FileManager::read_file(_vertShaderFilename).c_str();
	std::string fragShaderSource = Vizzy::FileManager::read_file(_fragShaderFilename).c_str();

	attach_vertex_shader(vertShaderSource.c_str());
	attach_fragment_shader(fragShaderSource.c_str());
	link_shader_program();
}

void Shader::attach_vertex_shader(const char* _srcData) {

	unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &_srcData, NULL);
	glCompileShader(vertShader);

	//check for any errors while compiling
	if (has_compile_error(vertShader,"VERTEX_SHADER"))
		return;

	glAttachShader(refID,vertShader);
	glDeleteShader(vertShader);
}
void Shader::attach_fragment_shader(const char* _srcData) {
	unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &_srcData, NULL);
	glCompileShader(fragShader);

	//check for any errors while compiling
	if (has_compile_error(fragShader,"FRAG_SHADER"))
		return;

	glAttachShader(refID, fragShader);
	glDeleteShader(fragShader);
}
void Shader::link_shader_program() {
	glLinkProgram(refID);

	if (has_link_error())
		return;
}

bool Shader::has_compile_error(unsigned int _shader,const char* _shaderType) {
	int success;
	char infoLog[512];

	glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		//compilation failed
		glGetShaderInfoLog(_shader, 512, NULL, infoLog);
		Debug::log(_shaderType," compilation failed : ", infoLog);
		return true;
	}

	//compilation successfull
	return false;
}
bool Shader::has_link_error() {
	int success;
	char infoLog[512];

	glGetShaderiv(refID, GL_LINK_STATUS, &success);

	if (!success) {
		//linking failed
		glGetProgramInfoLog(refID, 512, NULL, infoLog);
		Debug::log("Linking Shader Program failed :  ", infoLog);
		return true;
	}

	//linking successfull
	return false;
}


#pragma region Utility
void Vizzy::Shader::U1f(unsigned int _shader, const char* _param, float _value)
{
	glUseProgram(_shader);
	glUniform1f(glGetUniformLocation(_shader, _param), _value);
}
void Vizzy::Shader::Vec2f(unsigned int _shader, const char* _param, glm::vec2 _value)
{
	glUseProgram(_shader);
	glUniform2f(glGetUniformLocation(_shader, _param), _value.x,_value.y);
}
void Vizzy::Shader::Vec4f(unsigned int _shader, const char* _param, glm::vec4 _val) {
	glUseProgram(_shader);
	glUniform4f(glGetUniformLocation(_shader, _param), _val.x, _val.y, _val.z, _val.w);
}
void Vizzy::Shader::Mat4f(unsigned int _shader, const char* _param, glm::mat4 _val)
{
	glUseProgram(_shader);
	glUniformMatrix4fv(glGetUniformLocation(_shader, _param), 1, GL_FALSE, glm::value_ptr(_val));
}
#pragma endregion
