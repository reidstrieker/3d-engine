#pragma once
#include "MouseEvent.h"
#include <queue>

class MouseClass {
public:
	void OnLeftPressed(int x, int y); // left click down
	void OnLeftReleased(int x, int y); // left click up
	void OnRightPressed(int x, int y); // right click down
	void OnRightReleased(int x, int y); // right click up
	void OnMiddlePressed(int x, int y); // middle click down
	void OnMiddleReleased(int x, int y); // middle click up
	void OnWheelUp(int x, int y); // scroll wheel up
	void OnWheelDown(int x, int y); // scroll wheel down
	void OnMouseMove(int x, int y); // mouse move
	void OnMouseMoveRaw(int x, int y); // raw mouse input

	bool IsLeftDown(); // is left being clicked
	bool IsMiddleDown(); // is middle being clicked
	bool IsRightDown(); // is right being clicked

	int GetPosX(); // get the x position
	int GetPosY(); // get the y position
	MousePoint GetPos(); // get the position coordinates

	bool EventBufferIsEmpty(); // check if the event buffer is empty
	MouseEvent ReadEvent(); // read the events

private:
	std::queue<MouseEvent> eventBuffer; // queue for event buffer
	bool leftIsDown = false; // if left is currently pressed
	bool rightIsDown = false; // if right is currently pressed
	bool mbuttonDown = false; // if middle is currently pressed
	int x = 0; // current x position
	int y = 0; // current y position
};