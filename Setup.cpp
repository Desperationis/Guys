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


#include "Setup.h"

int WINDOW::WIDTH = 1920;
int WINDOW::HEIGHT = 1000;
int WINDOW::FPS = 60;
bool WINDOW::FPS_COUNTER = false;
bool WINDOW::VSYNC = true;

int QUADTREE::MAX_ITERATION = 5;
bool QUADTREE::RENDER = false;

int FOOD::SIZE = 10;
int FOOD::BEGIN = 0;
int FOOD::GROWTH = 5;
int FOOD::MULTIPLIER = 200;
int FOOD::ENERGY = 100;

int HOOMAN::SIGHT = 500;
int HOOMAN::BEGIN = 400;
int HOOMAN::SIZE = 10;
bool HOOMAN::RENDER_SIGHT = false;
bool HOOMAN::RESET = false;

bool DEBUG::OUT_OF_BOUNDS = false;
