#pragma once
#include "vizzy_internal.h"
namespace Vizzy {
	class App {
	public:
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
		void exit();

		void resize(int _x, int _y);
		
	
	
	
	};
}
