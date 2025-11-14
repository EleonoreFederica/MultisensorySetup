#ifndef PIXEL_H
#define PIXEL_H

#include <string>

using namespace std;

class Pixel
{
public:
    Pixel();
    Pixel(int _x,int _y,int _r,int _g,int _b): x(_x), y(_y), r(_r), g(_g), b(_b){}

    //fromJSON is taken care of in Visual_Stimulus
    string toJSON();

    int x;
    int y;
    int r;
    int g;
    int b;
};

#endif // PIXEL_H
