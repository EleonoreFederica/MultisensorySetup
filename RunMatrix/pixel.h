#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
public:
    int x;
    int y;
    int r;
    int g;
    int b;
    Pixel(int _x,int _y,int _r,int _g,int _b) : x(_x), y(_y), r(_r), g(_g), b(_b){}
    Pixel() : x(0), y(0), r(0), g(0), b(0){}
};


#endif // PIXEL_H
