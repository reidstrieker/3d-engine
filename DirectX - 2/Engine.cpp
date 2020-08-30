#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height) {
	if (!this->render_window.Initialize(this, hInstance, window_title, window_class, width, height)) // if render window fails to initialize, return false
		return false;
	
	if (!gfx.Initialize(this->render_window.GetHWND(), width, height)) // if graphics fail to initialize, return false
		return false;
	
	return true;
}

bool Engine::ProcessMessages() {
	return this->render_window.ProcessMessages(); // returns processed render window messages
}

void Engine::Update() {
	while (!keyboard.CharBufferIsEmpty()) {
		unsigned char ch = keyboard.ReadChar();
	}
	
	while (!keyboard.KeyBufferIsEmpty()) {
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
	}

	while (!mouse.EventBufferIsEmpty()) {
		MouseEvent me = mouse.ReadEvent();
		if (me.GetType() == MouseEvent::EventType::RAW_MOVE) { // all that is currently done in this loop is output the changes in the raw mouse input
			std::string outmsg = "X: ";
			outmsg += std::to_string(me.GetPosX());
			outmsg += ", ";
			outmsg += "Y: ";
			outmsg += std::to_string(me.GetPosY());
			outmsg += "\n";
			OutputDebugStringA(outmsg.c_str());
		}
	}
}