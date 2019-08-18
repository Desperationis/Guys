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
	static const int MULTIPLIER; // How many pieces of fruit grow
	static const int ENERGY; // How much energy a plant gives
};

struct HOOMAN {
	static const int SIGHT; // How far hooman can see on speed 1
	static const int BEGIN; // Initial numbers
	static bool RENDER_SIGHT; // Toggle to render the "eyes" of the hoomans
	static bool RESET; // Toggle to reset
};

struct QUADTREE {
	static const int MAX_ITERATION; // How far the tree can divide
	static bool RENDER;
};

struct DEBUG {
	static const bool OUT_OF_BOUNDS; // will this display out of bounds info?
};
