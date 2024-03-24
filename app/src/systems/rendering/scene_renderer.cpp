#include "../../../headers/systems/rendering/scene_renderer.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "../../../headers/utility/debug.h"
#include "../../../headers/utility/resources.h"
using namespace Vizzy;


void SceneRenderer::render(Mesh& _mesh, Material& _mat, glm::mat4 _modelMatrix)
{
	glUseProgram(_mat.shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _mat.mainTex.refID);
	glBindVertexArray(_mesh.VAO);

	Shader::Mat4f(_mat.shader, "modelMatrix", _modelMatrix);
	Shader::Vec4f(_mat.shader, "_MainColor", glm::vec4(0.2f, 0.3f, 0.5f, 1));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}