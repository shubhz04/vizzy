#include "../headers/app.h"
using namespace Vizzy;

App::App(int _appWidth, int _appHeight, const char* _appTitle, int _targetFPS) {
	width = _appWidth;
	height = _appHeight;
	title = _appTitle;

	targetFPS = _targetFPS;
}



GameObject wallpaper(0, "base-canvas");

void App::initialize() {


	// [-----Load Resources-----]
	Resources::LoadShader("default-shader", "assets/shaders/vert.glsl", "assets/shaders/frag.glsl");
	Resources::LoadTexture2D("popcat", "C:\\Users\\shubhz\\Downloads\\dia.png");
	Resources::LoadTexture2D("apple", "C:\\Users\\shubhz\\Downloads\\file.jpg");


	// [---Add Scene Bindings---]
	this->scene.add(&wallpaper);


	// [----Initialize Scene----]
	this->scene.camera.set_projection_matrix(Resources::GetShader("default-shader").refID, width, height);
	this->scene.initialize();
};


void App::start() {
	// Start is called once after initialization.
	wallpaper.transform.set_position(glm::vec3(0, 0, 0));
	wallpaper.transform.set_scale(glm::vec3(width, height, 1.0f));
	wallpaper.material.mainTex.refID = Resources::GetTexture2D("popcat");
	wallpaper.material.secondaryTex.refID = Resources::GetTexture2D("apple");


	// Temp
	Vizzy::DWM::log_hwnds();

	//Vizzy::OpenFolderDialogResult targetFolder = Vizzy::FileManager::open_folder_dialog();
	//std::string selectedPath = (targetFolder.result == SUCCCESS) ? targetFolder.path : "NULL";
	//Debug::log(selectedPath);

};
void App::update() {
	// Update is called every frame.
	// ----Do all Object state changes here----



	// ----------------------------------------
	// Finally push these changes by updating the scene
	this->scene.update();
};

void App::render() {
	// Render is called generally at sync with update, but sometimes 
	// it is called at diff rate for performance reasons.

	// Renders the active scene to the screen.
	this->scene.render();
}
void App::exit() {
	// Exit is called upon WM_EXIT.

};

void App::resize(int _x, int _y) {
	// Resize is called every time the user holds down and move the resize handle.
	this->width = _x; this->height = _y;
	this->scene.camera.set_projection_matrix(Resources::GetShader("default-shader").refID
		, this->width
		, this->height);
};