#pragma once
#include "../systems/rendering/render.h"
#include "transform.h"
#include "sceneobject.h"


namespace Vizzy {
	class GameObject : public SceneObject{

	private:
		int id = 0;

	public:
		const char* name;

		Vizzy::Transform transform;
		Vizzy::Material material;
		Vizzy::Mesh mesh;
		
		// Remove in other projects
		// --Custom Properties--
		glm::vec2 expansionOrigin;
		float maskRadius;
		// ---------------------
		GameObject(int _id = 0, const char* _name = "default-object");

		void initialize() override;
		void start() override;
		void update() override;
		void render() override;
		
	};
}