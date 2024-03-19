#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Vizzy {
	class Transform {
	private:
		void calculate_model_matrix();

	public:
		glm::mat4	modelMatrix;

		glm::vec3	position;
		glm::vec3	scale;
		float		rotation;

		Transform(glm::vec3 _position = glm::vec3(1.0f), float _rotation = 0, glm::vec3 _scale = glm::vec3(1.0f));

		void set_position(glm::vec3 _pos);
		void set_rotation(float _rot);
		void set_scale(glm::vec3 _scale);

		void apply();


	};
}