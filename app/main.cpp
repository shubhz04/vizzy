#define GLFW_EXPOSE_NATIVE_WIN32
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include <thread>


#include "headers/app.h"
#include "headers/utility/debug.h"
#include "headers/systems/time.h"


//app----->  (width | height| name | fps)
Vizzy::App app(800, 600, "Vizzy", 75);

//fps-limiter => [VALUES IN SECONDS] 
float targetFrameTime = 1.0f / app.targetFPS;
float deltaTime;
float lastFrameTime;
float currFrameTimeBuffer;


void process_input();

#pragma region Callbacks
void viewport_resize_callback(GLFWwindow* _window, int _x, int _y);
void window_resize_callback(GLFWwindow* _window);
#pragma endregion

int main() {
#pragma region Init GLFW

	Debug::log("Starting App ...");

	// Initializes glfw
	glfwInit();

	// Set window hints for creating the window and context.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window, and check if its created.
	GLFWwindow* window = glfwCreateWindow(app.width, app.height, app.title, NULL, NULL);
	if (window == NULL) {
		Debug::log("Creating window failed. Exiting...");
		glfwTerminate();
		return -1;
	}

	// Make the current context from the window.
	glfwMakeContextCurrent(window);

	// Setting Vsync for not wasting GPU.
	glfwSwapInterval(1);

	// Load glad for OpenGL.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		//if failed intializing
		Debug::log("Glad initialize failed...");
		glfwTerminate();
		return -1;
	}

	// Creates the opengl viewport and register the callbacks for resize.
	glViewport(0, 0, app.width, app.height);
	glfwSetWindowRefreshCallback(window, window_resize_callback);
	glfwSetFramebufferSizeCallback(window, viewport_resize_callback);

	Debug::log("OpenGL context initialized.");
#pragma endregion

#pragma region ExtraConfigGL
	// Doesn't causes the app to crash if NON-POTS textures are uploaded by user.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Enables alpha blending for transparent textures.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#pragma endregion

	// Initializes utility classes.
	Vizzy::Mouse::initialize((long)glfwGetWin32Window(window));
	Vizzy::DWM::initialize();

	// Starts the input thread and DWM thread
	std::thread inputThread(process_input);
	std::thread dwmThread(Vizzy::DWM::dwm_loopback);

	// Fires the app initalize events.
	app.initialize();
	app.start();

	while (!glfwWindowShouldClose(window)) {

		// Set time data.
		Time::time = glfwGetTime(); //in seconds
		Time::deltaTime = Time::time - lastFrameTime; //in seconds
		lastFrameTime = Time::time;

		// set-framerate-cap
		if (currFrameTimeBuffer > targetFrameTime) {

			//clears the screen with a solid color
			glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//Update call here
			app.update();

			// Draw the current state if the desktop is focused, (SAVES GPU!!)
			if (!Vizzy::DWM::isFocused) {
				app.render();
				glfwSwapBuffers(window);
			}

			// Resets the timebuffer after a frame is done
			currFrameTimeBuffer = 0;

			// Poll for window events
			glfwPollEvents();
		}
		else
			currFrameTimeBuffer += Time::deltaTime;

	}

	// exit-area
	app.exit();

	inputThread.detach();
	dwmThread.detach();


	Vizzy::Mouse::dispose();

	glfwTerminate();
	return 0;
}


#pragma region Definitions

// Runs a loop to continously peek into the message queue and process events on seperate thread
void process_input() {
	while (true) {
		Vizzy::Mouse::process_events();
		Sleep(5);
	}
}


//resize viewport when framebuffersize changes
void viewport_resize_callback(GLFWwindow* _window, int _x, int _y) {

	glViewport(0, 0, _x, _y);
	app.resize(_x, _y);
}
//continues drawing even while resizing windows
void window_resize_callback(GLFWwindow* _window) {

	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	app.update();

	glfwSwapBuffers(_window);
	glFinish();
}
#pragma endregion
