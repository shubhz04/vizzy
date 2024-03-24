#pragma once
#include <glm/glm.hpp>
#include "render.h"
namespace Vizzy {
	class SceneRenderer {
	public:
		
		static void render(Mesh& _mesh,Material& _mat,glm::mat4 modelMatrix);

	};
}