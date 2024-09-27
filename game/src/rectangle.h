#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "raylib.h"

class RectangleShape {
public:
    float x, y;
    float width, height;
    Color color = WHITE;
    
    RectangleShape(int x, int y, int w, int h, Color c);

    void draw();
};

#endif 
