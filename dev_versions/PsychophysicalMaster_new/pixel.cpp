#include "pixel.h"


Pixel::Pixel() : x(0), y(0), r(0), g(0), b(0) {}



string Pixel::toJSON() const
{
    return "["+to_string(x)+","+to_string(y)+","+to_string(r)+","+to_string(g)+","+to_string(b)+"]";
}
