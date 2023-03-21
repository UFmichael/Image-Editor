#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

class Image { 
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };

    struct Pixel {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
    };

    public:
    Header header;
    vector<Pixel> pixels;
    string file_path;

    Image();
    Image(string file);
    Image(string file, string path);

    void getFileImage(string filepath);
    void printFileHeader(Header file);
    void copyPixels(string filepath);
    void writeFile(string filepath);
    void addColor(string color, int value);
    void multiplyColor(string color, int value);
    void setGrey(string color);
    void reloadImage();
    void setSize(int length, int width);
    bool operator == (const Image& rhs);
    Image operator * (const Image& rhs);
    Image operator = (const Image& rhs);
    Image operator - (const Image& rhs);
    void mergeThree(Image &g, Image &b);
    void rotate(Image &a);
    void screen(Image &a);
    void overlay(Image &a);
};