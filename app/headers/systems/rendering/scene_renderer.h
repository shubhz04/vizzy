#pragma once
#include <glm/glm.hpp>
#include "render.h"
namespace Vizzy {
	class SceneRenderer {
	public:
		
		static void render(Mesh& _mesh,Material& _mat,glm::mat4 modelMatrix,glm::vec2 _expansionOrigin,glm::vec2 _size,float _radius);

	};
}