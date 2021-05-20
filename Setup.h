#pragma once

struct WINDOW {
	static int WIDTH;
	static int HEIGHT;
	static int FPS;
	static bool FPS_COUNTER;
	static bool VSYNC;
};

struct FOOD {
	static int SIZE; // How big it is
	static int BEGIN; // Initial amount of food
	static int GROWTH; // How many frames before food grows
	static int MULTIPLIER; // How many pieces of fruit grow
	static int ENERGY; // How much energy a plant gives
};

struct HOOMAN {
	static int SIZE; // How big it is
	static int SIGHT; // How far hooman can see on speed 1
	static int BEGIN; // Initial numbers
	static bool RENDER_SIGHT; // Toggle to render the "eyes" of the hoomans
	static bool RESET; // Toggle to reset
};

struct QUADTREE {
	static int MAX_ITERATION; // How far the tree can divide
	static bool RENDER;
};

struct DEBUG {
	static bool OUT_OF_BOUNDS; // will this display out of bounds info?
};
