#include "KeyboardClass.h"

KeyboardClass::KeyboardClass() {
	for (int i = 0; i < 256; i++)
		this->keyStates[i] = false; // initialize all key states to false
}

bool KeyboardClass::KeyIsPressed(const unsigned char keycode) {
	return this->keyStates[keycode];
}

bool KeyboardClass::KeyBufferIsEmpty() {
	return this->keyBuffer.empty();
}

bool KeyboardClass::CharBufferIsEmpty() {
	return this->charBuffer.empty();
}

KeyboardEvent KeyboardClass::ReadKey() {
	if (this->keyBuffer.empty()) {
		return KeyboardEvent(); // return empty keyboard event if no keys are read
	}
	else {
		KeyboardEvent e = this->keyBuffer.front(); // get first keyboard event from queue
		this->keyBuffer.pop(); // remove first item from queue
		return e; // returns keyboard event
	}
}

unsigned char KeyboardClass::ReadChar() {
	if (this->charBuffer.empty()) {
		return 0u; // return 0 (NULL char) if no keys are read
	}
	else {
		unsigned char e = this->charBuffer.front(); // get first char from queue
		this->charBuffer.pop(); // remove first char from queue
		return e; // returns char
	}
}

void KeyboardClass::OnKeyPressed(const unsigned char key) { // pushes a new keyboard event into queue
	this->keyStates[key] = true;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void KeyboardClass::OnKeyReleased(const unsigned char key) { // same as above
	this->keyStates[key] = false;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void KeyboardClass::OnChar(const unsigned char key) { // same as above
	this->charBuffer.push(key);
}

void KeyboardClass::EnableAutoRepeatKeys() {
	this->autoRepeatKeys = true;
}

void KeyboardClass::DisableAutoREpeatKeys() {
	this->autoRepeatKeys = false;
}

void KeyboardClass::EnableAutoRepeatChars() {
	this->autoRepeatChars = true;
}

void KeyboardClass::DisableAutoRepeatChars() {
	this->autoRepeatChars = false;
}

bool KeyboardClass::IsKeysAutoRepeat() {
	return this->autoRepeatKeys;
}

bool KeyboardClass::IsCharsAutoRepeat() {
	return this->autoRepeatChars;
}