#pragma once
#include <glm/glm.hpp>

namespace Vizzy {
	class Camera {
	public:
		glm::mat4 projectionMatrix;
		glm::vec3 position;

		Camera() {};
		Camera(float _screenWidth, float _screenHeight);
		void set_projection_matrix(unsigned int _shader,float _screenWidth,float _screenHeight);
	};
}