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

		// Sets the object position in screen-coords, Z-value is ignored for now.
		void set_position(glm::vec3 _pos);

		// Sets the object rotation in degrees
		void set_rotation(float _rot);

		// Sets the scale of the object in pixels
		void set_scale(glm::vec3 _scale);

		/* Recalculates the model matrix, if any values are not set through methods
		   -------------------
		   Example:
		   transform.position = glm::vec3(300,300, 0);
		   transform.apply();
		   -------------------
		*/
		void apply();


	};
}