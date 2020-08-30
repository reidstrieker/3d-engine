#pragma once

class KeyboardEvent {
public:
	enum EventType {
		Press, // if a user presses a key
		Release, // if a user releases a key
		Invalid // if an event is invalid
	};

	KeyboardEvent(); // first constructor generates an invalid event
	KeyboardEvent(const EventType type, const unsigned char key); // second constructor takes EventType and key
	bool IsPress() const; // true if press event
	bool IsRelease() const; // true if release event
	bool IsValid() const; // true if valid (press or release)
	unsigned char GetKeyCode() const; // returns key code

private:
	EventType type;
	unsigned char key;

};