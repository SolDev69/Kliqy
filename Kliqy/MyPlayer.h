#pragma once
#include "Shape.h"

class MyPlayer :
    public Shape
{
private:
    int m_base;
    int m_height;
public:
    void draw(Gdiplus::Graphics& graphics);
    MyPlayer(int x, int y, int base, int height);
    double radius();
    int base();
    int height();
};

