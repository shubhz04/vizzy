#include "../headers/app.h"
#include "../headers/utility/files.h"
#include "../headers/utility/resources.h"
using namespace Vizzy;

App::App(int _appWidth, int _appHeight, const char* _appTitle, int _targetFPS) {
	width = _appHeight;
	height = _appHeight;
	title = _appTitle;

	targetFPS = _targetFPS;

}

void App::initialize() {

	//lets try reading that file
	Resources::LoadShader("sprite", "assets/shaders/vert.glsl", "assets/shaders/frag.glsl");


};
void App::start() {};
void App::update() {};
void App::exit() {};

void App::resize(int _x,int _y) {
	width = _x; height = _y;
};