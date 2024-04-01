#include "../headers/app.h"
#include "../headers/utility/vmath.h"
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
	Resources::LoadTexture2D("popcat", "C:\\Users\\shubhz\\Downloads\\ffile.png");
	Resources::LoadTexture2D("apple", "C:\\Users\\shubhz\\Downloads\\file.jpg");

	// [---Add Scene Bindings---]
	this->scene.add(&wallpaper);


	// [----Initialize Scene----]
	this->scene.camera.set_projection_matrix(Resources::GetShader("default-shader").refID, width, height);
	this->scene.initialize();
};


void App::start() {
	// Start is called once after initialization.
	Shader::Vec2f(Resources::GetShader("default-shader"), "screen", glm::vec2(this->width, this->height));

	wallpaper.transform.set_position(glm::vec3(0, 0, 0));
	wallpaper.transform.set_scale(glm::vec3(this->width, this->height, 1.0f));
	wallpaper.material.mainTex.refID = Resources::GetTexture2D("popcat");
	wallpaper.material.secondaryTex.refID = Resources::GetTexture2D("apple");


	wallpaper.expansionOrigin = glm::vec2(this->width, this->height);

	// Temp
	Vizzy::DWM::log_hwnds();

};
void App::update() {
	// Update is called every frame.
	// ---- Do all Object state changes here ----

	
	CubicBezier t;
	t.sP = glm::vec2(0,0);
	t.cp1 = glm::vec2(0.9f,0.9f);
	t.cp2 = glm::vec2(1,0);
	t.eP = glm::vec2(1,1);
	float spPoint =  get_bezier_point(t, glm::clamp((Time::time - 4) / 2.0f,0.0f,1.0f)).y;
	spPoint *= 1.2f;
	wallpaper.maskRadius = spPoint;
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