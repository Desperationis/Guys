#include "Food.h"
#include "Setup.h"
#include "Tools/Rect.h"


const int Food::value = 40;
Uint32 Food::counter = 0;

Food::Food() {
	int x = rand() % WINDOW::WIDTH;
	int y = rand() % WINDOW::HEIGHT;
	rect = new Rect(x, y, FOOD::SIZE, FOOD::SIZE);
	id = counter;
}

Food::Food(int x, int y) {
	rect = new Rect(x, y, FOOD::SIZE, FOOD::SIZE);
	id = counter;
}


void Food::render() {
	rect->renderFill(0, 155, 0, 255);
}

