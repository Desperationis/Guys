#include "Setup.h"

const int WINDOW::WIDTH = 1920;
const int WINDOW::HEIGHT = 1000;
const int WINDOW::FPS = 60;
bool WINDOW::FPS_COUNTER = false;

const int QUADTREE::MAX_ITERATION = 5;
bool QUADTREE::RENDER = false;

const int FOOD::SIZE = 10;
const int FOOD::BEGIN = 0;
const int FOOD::GROWTH = 5;
const int FOOD::MULTIPLIER = 200;
const int FOOD::ENERGY = 100;

const int HOOMAN::SIGHT = 500;
const int HOOMAN::BEGIN = 400;
bool HOOMAN::RENDER_SIGHT = false;
bool HOOMAN::RESET = false;

const bool DEBUG::OUT_OF_BOUNDS = false;
