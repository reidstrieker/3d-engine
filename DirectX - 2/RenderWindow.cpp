#include "WindowContainer.h"

bool RenderWindow::Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height) {
	this->hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide(this->window_title);
	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide(this->window_class);

	this->RegisterWindowClass();

	// window creation

	this->handle = CreateWindowEx(0, // extended windows style (0 for default)
		this->window_class_wide.c_str(), // window class name
		this->window_title_wide.c_str(), // window title
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, // window style
		0, // window X position
		0, // window Y position
		this->width, // window width
		this->height, // window height
		NULL, // handle to parent of window
		NULL, // handle to menu or child window identifier
		this->hInstance, // handle to instance of module to be used with window
		pWindowContainer); // param to create window (pointer to window container)

	// check if window was successfully created

	if (this->handle == NULL) { 
		ErrorLogger::Log(GetLastError(), "CreateWindowEX Failed for window: " + this->window_title);
		return false;
	}

	// bring window up on screen, set as main focus

	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

	return true;
}

bool RenderWindow::ProcessMessages() {
	MSG msg; // create a message
	ZeroMemory(&msg, sizeof(MSG)); // init message structure by zeroing memory on it

	if (PeekMessage(&msg, // address of where to store message (if it exists)
		this->handle, // handle to window to be checked for messages (pass NULL to check all messages)
		0, // minimum filter message value
		0, // maximum filter message value
		PM_REMOVE)) // remove message after capturing it via PeekMessage
	{
		TranslateMessage(&msg); // translate message from virtual key messages into character messages
		DispatchMessage(&msg); // dispatch message to our Window Proc for window
	}

	// check if window is closed

	if (msg.message == WM_NULL) { // WM_QUIT for one window
		if (!IsWindow(this->handle)) {
			this->handle = NULL; // message processing loop destroys the window
			UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
			return false;
		}
	}

	return true;
}

HWND RenderWindow::GetHWND() const {
	return this->handle;
}

RenderWindow::~RenderWindow() {
	if (this->handle != NULL) {
		UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
		DestroyWindow(handle);
	}
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	default: {
		WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)); // retrieve ptr to window class
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam); // forward message to window class handler
	}
	}
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { // window messages are dispatched to here
	switch (uMsg) {
	case WM_NCCREATE: { // triggered upon creation of window

		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam); // creation of pointer to window container
		WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams); // extracts pointer
		if (pWindow == nullptr) {
			ErrorLogger::Log("Critical Error: Pointer to window container is null during WM_NCCREATE.");
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow)); // setting the user data to be the pointer pWindow to the container window
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect)); // changes the window proc to HandleMsgRedirect (redirects messages to window container)
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam); // call WindowProc from the window container
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	
	
}

void RenderWindow::RegisterWindowClass() {
	WNDCLASSEX wc; // window class to be filled
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // redraws on width/height change from resize/movement
	wc.lpfnWndProc = HandleMessageSetup; // pointer to window proc function for handling messages from window
	wc.cbClsExtra = 0; // number of extra bytes to allocate
	wc.cbWndExtra = 0; // number of extra bytes to allocate
	wc.hInstance = this->hInstance; // handle to instance containing window proc
	wc.hIcon = NULL; // handle to class icon
	wc.hIconSm = NULL; // handle to small icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // handle to cursor (set to default)
	wc.hbrBackground = NULL; // handle to class background brush
	wc.lpszMenuName = NULL; // pointer to a string for menu
	wc.lpszClassName = this->window_class_wide.c_str(); // pointer to a wide string for class name
	wc.cbSize = sizeof(WNDCLASSEX); // size of the struct

	RegisterClassEx(&wc); // registers the class
}