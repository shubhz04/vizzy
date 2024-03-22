#include "../../headers/components/transform.h"

using namespace Vizzy;

void Transform::calculate_model_matrix() {

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, scale);
};

Transform::Transform(glm::vec3 _pos, float _rot , glm::vec3 _scale) {
	position = _pos; rotation = _rot; scale = _scale;
	modelMatrix = glm::mat4(1.0f);
}

void Transform::set_position(glm::vec3 _pos) {
	position = _pos; 
	calculate_model_matrix();
}

//rotation in degrees
void Transform::set_rotation(float _rot) {
	rotation = _rot;
	calculate_model_matrix();
}

void Transform::set_scale(glm::vec3 _scale) {
	scale = _scale;
	calculate_model_matrix();
}

void Transform::apply() { calculate_model_matrix(); }
