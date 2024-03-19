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

void App::initialize() {

	//lets try reading that file
	Resources::LoadShader("sprite", "assets/shaders/vert.glsl", "assets/shaders/frag.glsl");

};



GameObject wallpaper(0, "base-canvas");

void App::start() {
	wallpaper.transform.set_position(glm::vec3(200, 200, 0));
	wallpaper.transform.set_rotation(0);
	wallpaper.transform.set_scale(glm::vec3(300, 300, 1.0f));

};
void App::update() {};
void App::exit() {};

void App::resize(int _x,int _y) {
	width = _x; height = _y;
};