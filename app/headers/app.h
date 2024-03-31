#pragma once
#include "vizzy_internal.h"
#include "utility/files.h"
#include "utility/resources.h"
#include "utility/dwm.h"
namespace Vizzy {
	class App {
	public:
		//internal-data
		static long int hwnd;

		//app-properties
		int width, height;
		const char* title;
		int targetFPS;
		//data-container
		Vizzy::Scene scene;


		//def-constrct
		App(int _appWidth, int _appHeight,const char* _appTitle = "Default App",int _targetFPS = 60);
	
		

		void initialize();
		void start();
		void update();
		void render();
		void exit();

		void resize(int _x, int _y);	
	};
}
