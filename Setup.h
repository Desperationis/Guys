// Simulation of life written in C++ and SDL. 
// Copyright (C) 2021 Diego Contreras
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


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
