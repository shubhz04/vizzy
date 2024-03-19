#pragma once
#include "../systems/rendering/render.h"
#include "transform.h"
#include "../utility/resources.h"
class GameObject {

private:


public:
	Vizzy::Transform transform;
	Vizzy::Material material;
	Vizzy::Mesh mesh;

	GameObject(int _id = 0, const char* _name = "default-object");

};