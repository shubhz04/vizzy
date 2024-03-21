#pragma once
#include "../../headers/components/sceneobject.h"
#include "../../headers/components/camera.h"
#include <list>

namespace Vizzy {
	
	class Scene {
	private:
		std::list<SceneObject*> sceneObject;

	public:
		Vizzy::Camera camera;

		

		void add(SceneObject* _obj) {
			sceneObject.push_back(_obj);
		};

		void initialize() {
			for (auto& obj : sceneObject)
				obj->initialize();
		}
		void start() {
			for (auto& obj : sceneObject)
				obj->start();
		}
		void update() {
			for (auto& obj : sceneObject)
				obj->update();
		}
		void render() {
			for (auto& obj : sceneObject)
				obj->render();
		}
	};
}