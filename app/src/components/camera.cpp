#include "../../headers/components/camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
using namespace Vizzy;
Vizzy::Camera::Camera(float _screenWidth, float _screenHeight)
{
	projectionMatrix = glm::ortho(0.0f, _screenWidth, _screenHeight, 0.0f, -1.0f, 100.0f);
	position = glm::vec3(0.0f, 0.0f, -10.0f);
}

void Vizzy::Camera::set_projection_matrix(unsigned int _shader, float _screenWidth, float _screenHeight)
{
	projectionMatrix = glm::ortho(0.0f, _screenWidth, _screenHeight, 0.0f, -1.0f, 100.0f);
	glUseProgram(_shader);
	glUniformMatrix4fv(glGetUniformLocation(_shader, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

}


