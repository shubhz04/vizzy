#include "../headers/app.h"
#include "../headers/utility/files.h"
#include "../headers/utility/resources.h"
using namespace Vizzy;

App::App(int _appWidth, int _appHeight, const char* _appTitle, int _targetFPS) {
	width = _appWidth;
	height = _appHeight;
	title = _appTitle;

	targetFPS = _targetFPS;
}



GameObject wallpaper(0, "base-canvas");


void App::initialize() {

	//lets try reading that file
	Resources::LoadShader("default-shader", "assets/shaders/vert.glsl", "assets/shaders/frag.glsl");

	this->scene.add(&wallpaper);


	this->scene.camera.set_projection_matrix(Resources::GetShader("default-shader").refID, width, height);
	this->scene.initialize();
};


void App::start() {
	wallpaper.transform.set_position(glm::vec3(200, 200, 0));
	wallpaper.transform.set_scale(glm::vec3(300, 300, 1.0f));


};
void App::update() {

	this->scene.update();
	this->scene.render();
};
void App::exit() {};

void App::resize(int _x, int _y) {
	this->width = _x;
	this->height = _y;
	this->scene.camera.set_projection_matrix(Resources::GetShader("default-shader").refID
		, this->width
		, this->height);
};