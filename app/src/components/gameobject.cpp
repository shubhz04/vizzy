#include "../../headers/components/gameobject.h"
#include "../../headers/utility/resources.h"
#include "../../headers/systems/rendering/scene_renderer.h"
using namespace Vizzy;

GameObject::GameObject(int _id, const char* _name) {
	id = _id; name = _name;

};
void Vizzy::GameObject::initialize()
{

	mesh.initialize();
	material.shader.refID = Resources::GetShader("default-shader").refID;
};
void Vizzy::GameObject::start()
{

};

void GameObject::update() {

};

void GameObject::render() {
	SceneRenderer::render(
		mesh.VAO,
		mesh.VBO,
		mesh.EBO,
		material.shader.refID,
		transform.modelMatrix
	);
};
