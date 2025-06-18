#ifndef MATRIXIMAGE_H
#define MATRIXIMAGE_H

#include <iostream>
#include <vector>
#include <string>
#include "pixel.h"
#include "rapidjson.h"
#include "document.h"

class MatrixImage
{
public:
    MatrixImage() : onset(-99), offset(-99){}

    int onset;
    int offset;
    int isi;
    std::vector<Pixel> pixels;
    void reset();
    bool parseInfo(std::string jsonstring);
};

#endif // MATRIXIMAGE_H
