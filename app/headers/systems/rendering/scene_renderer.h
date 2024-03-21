#pragma once
#include <glm/glm.hpp>
namespace Vizzy {
	class SceneRenderer {
	public:
		
		static void render(unsigned int _VAO,unsigned int _VBO, unsigned int _EBO, unsigned int _shader,glm::mat4 modelMatrix);

	};
}