#define GLFW_EXPOSE_NATIVE_WIN32
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include <thread>

#include "headers/app.h"
#include "headers/utility/debug.h"
#include "headers/utility/files.h"
#include "headers/systems/time.h"

#pragma region Variables

Vizzy::App app(800, 600, "Vizzy", 75);

//fps-limiter
float targetFrameTime = 1.0f / app.targetFPS; //in ms (ex: 1000/60 approx 16 ms)
float deltaTime, lastFrameTime, currFrameTimeBuffer;

#pragma endregion
#pragma region Callbacks
void viewport_resize_callback(GLFWwindow* _window, int _x, int _y);
#pragma endregion
#pragma region ModuleFunc
void process_input();
void window_resize_callback(GLFWwindow* _window);
#pragma endregion


int main() {
#pragma region Init GLFW


	Debug::log("Starting App");

	//initializes glfw
	glfwInit();

	//set window hints for creating the window and context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create a window, and check if its created
	GLFWwindow* window = glfwCreateWindow(app.width, app.height, app.title, NULL, NULL);
	if (window == NULL) {
		Debug::log("Creating window failed. Exiting...");
		glfwTerminate();
		return -1;
	}


	//makes the current context from the window
	glfwMakeContextCurrent(window);

	//setting Vsync for not wasting GPU, swap with our monitors refresh rate basically capping it 
	glfwSwapInterval(1);

	//load glad for OpenGl
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		//if failed intializing
		Debug::log("Glad initialize failed...");
		glfwTerminate();
		return -1;
	}

	//creates the opengl viewport and registers the callback for resize
	glViewport(0, 0, app.width, app.height);
	glfwSetWindowRefreshCallback(window, window_resize_callback);
	glfwSetFramebufferSizeCallback(window, viewport_resize_callback);
#pragma endregion

	//starts the input thread
	Vizzy::Mouse::initialize((long)glfwGetWin32Window(window));
	std::thread inputThread(process_input);
	
	//Fires the app initalize events
	app.initialize();
	app.start();

	while (!glfwWindowShouldClose(window)) {
		
		//set time data
		Time::time = glfwGetTime(); //in seconds
		Time::deltaTime = Time::time - lastFrameTime; //in ms
		lastFrameTime = Time::time;

		if (currFrameTimeBuffer > targetFrameTime) {
			//clears the screen with a solid color
			glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//Update call here
			app.update();

			//swaps the front buffer with the backbuffer to show the rendered stuffs
			glfwSwapBuffers(window);
			currFrameTimeBuffer = 0;
		}
		else
			currFrameTimeBuffer += Time::deltaTime;


		//Polls for window updates
		glfwPollEvents();
	}

	//exit-area
	app.exit();
	

	inputThread.detach();
	Vizzy::Mouse::dispose();

	glfwTerminate();
	return 0;
}


#pragma region Definitions
void viewport_resize_callback(GLFWwindow* _window, int _x, int _y) {

	Debug::log("Viewport resized");
	glViewport(0, 0, _x, _y);
	app.resize(_x, _y);
}

void process_input() {
	while(true){
		Vizzy::Mouse::process_events();
		Sleep(5);
	}
}
void window_resize_callback(GLFWwindow* _window) {

	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Update call here
	app.update();

	//swaps the front buffer with the backbuffer to show the rendered stuffs
	glfwSwapBuffers(_window);
	glFinish();
}
#pragma endregion
