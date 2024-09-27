#include "rectangle.h"

RectangleShape::RectangleShape(int x, int y, int w, int h, Color c) {
    this->x = x;
    this->y = y;
    width = w;
    height = h;
    color = c; 
}

void RectangleShape::draw() {
    DrawRectangle(x, y, width, height, color);
}
