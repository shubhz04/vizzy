#pragma once
namespace Vizzy {
	//scene-objects are not meant to be rendered but can exist as data containers independently to recieve callbacks
	class SceneObject {
	
	public:
		SceneObject() {};
		virtual void initialize() {};
		virtual void start() {};
		virtual void update() {};
		virtual void render() {};
	};
}