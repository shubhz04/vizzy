#include "../../../headers/systems/rendering/scene_renderer.h"
#include "../../../headers/systems/rendering/render.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "../../../headers/utility/debug.h"
using namespace Vizzy;


void SceneRenderer::render(
	unsigned int _VAO, 
	unsigned int _VBO, 
	unsigned int _EBO,
	unsigned int _shaderProgram,
	glm::vec4 _mainColor,
	glm::mat4 _modelMatrix) 
{

	glUseProgram(_shaderProgram);
	glBindVertexArray(_VAO); 
	Shader::Mat4f(_shaderProgram, "modelMatrix", _modelMatrix);
	Shader::Vec4f(_shaderProgram, "_MainColor", _mainColor);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	
	
}