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
