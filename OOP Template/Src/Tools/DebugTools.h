#pragma once
#include "../includes.h"



struct Quadtree;
struct Quad;
class DebugTools {
public:
	DebugTools() {};
	void update();
private:
	int x, y;
	bool Lclicked = false;
	bool Rclicked = false;
	bool Lshift = false;
};

