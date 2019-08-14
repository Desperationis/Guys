#pragma once

struct WINDOW {
	static const int WIDTH;
	static const int HEIGHT;
	static const int FPS;
};

struct FOOD {
	static const int SIZE;
	static const int BEGIN;
	static const int GROWTH; // How many frames before food grows
	static const int ENERGY; // How much energy a plant gives
};

struct HOOMAN {
	static const int SIGHT; // How far hooman can see
	static const int BEGIN; // Initial numbers
};

struct QUADTREE {
	static const int MAX_ITERATION; // How far the tree can divide
};
