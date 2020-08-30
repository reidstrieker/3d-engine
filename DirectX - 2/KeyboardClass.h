#pragma once
#include "KeyboardEvent.h"
#include <queue>

class KeyboardClass {
public:
	KeyboardClass(); // constructor
	bool KeyIsPressed(const unsigned char keycode); // checks if a key is pressed
	bool KeyBufferIsEmpty(); // checks if the key buffer is empty
	bool CharBufferIsEmpty(); // checks if the char buffer is empty
	KeyboardEvent ReadKey(); // reads for a key
	unsigned char ReadChar(); // reads for a char
	void OnKeyPressed(const unsigned char key);
	void OnKeyReleased(const unsigned char key);
	void OnChar(const unsigned char key);
	void EnableAutoRepeatKeys();
	void DisableAutoREpeatKeys();
	void EnableAutoRepeatChars();
	void DisableAutoRepeatChars();
	bool IsKeysAutoRepeat();
	bool IsCharsAutoRepeat();
private:
	bool autoRepeatKeys = false;
	bool autoRepeatChars = false;
	bool keyStates[256];
	std::queue<KeyboardEvent> keyBuffer;
	std::queue<unsigned char> charBuffer;
};