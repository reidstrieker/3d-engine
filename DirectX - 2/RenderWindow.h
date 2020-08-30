#pragma once
#include "ErrorLogger.h"

class WindowContainer;

class RenderWindow {
public:
	bool Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height); // parameters to create window
	bool ProcessMessages(); // reads/processes all messages sent to window
	HWND GetHWND() const;
	~RenderWindow(); // destructor
private:
	void RegisterWindowClass();
	HWND handle = NULL; // handle to window
	HINSTANCE hInstance = NULL; // handle to application instance
	std::string window_title = "";
	std::wstring window_title_wide = L"";
	std::string window_class = "";
	std::wstring window_class_wide = L"";
	int width = 0;
	int height = 0;
};