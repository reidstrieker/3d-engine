#include "Engine.h"


// entry point for windows applications

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // handle to instance of application
	_In_opt_ HINSTANCE hPrevInstance, // handle to previous instance
	_In_ LPWSTR lpCmdLine, // pointer to command line
	_In_ int nCmdShow) // for showing the window
{
	Engine engine;
	engine.Initialize(hInstance, "Title", "MyWindowClass", 800, 600);
	while (engine.ProcessMessages() == true) {
		engine.Update();
	}

	return 0;
}