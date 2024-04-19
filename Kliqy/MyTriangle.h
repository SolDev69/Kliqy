#pragma once
#include "Shape.h"

class MyTriangle :
    public Shape
{
private:
    double m_base;
    double m_height;
public:
    void draw(Gdiplus::Graphics& graphics);
    MyTriangle(double x, double y, double base, double height);
    double base();
    double height();
};

