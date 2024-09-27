#ifndef SHAPE_H
#define SHAPE_H

class Shape {
public:
    virtual void draw() = 0; 
    virtual ~Shape() = default; // Virtual destructor for proper cleanup
};

#endif // SHAPE_H
