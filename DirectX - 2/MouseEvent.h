#pragma once
struct MousePoint { // position of the mouse
	int x;
	int y;
};

class MouseEvent {
public:
	enum EventType {
		LPress,
		LRelease,
		RPress,
		RRelease,
		MPress,
		MRlease,
		WheelUp,
		WheelDown,
		Move,
		RAW_MOVE, // raw input move
		Invalid // invalid default type
	};
private:
	EventType type;
	int x;
	int y;
public:
	MouseEvent(); // default constructor
	MouseEvent(const EventType type, const int x, const int y); // constructor that takes event type and positions
	bool IsValid() const; // returns if is valid
	EventType GetType() const; // returns event type
	MousePoint GetPos() const; // returns position coordinates
	int GetPosX() const; // returns x position
	int GetPosY() const; // returns y position
};