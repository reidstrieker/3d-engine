#pragma once
#include "WindowContainer.h"
class Engine : WindowContainer { // Engine inherits from WindowContainer
public:
	bool Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height); // parameters to create window
	bool ProcessMessages(); // same as ProcessMessages from RenderWindow


	void Update();
};