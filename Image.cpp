#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <algorithm>
#include "image.h"

using namespace std;

Image::Image(){
    file_path = "error";
    cout << "no path given" << endl;
}

Image::Image(string file){
    file_path = "../input/" + file + ".tga";
    getFileImage(file_path);
}
Image::Image(string file, string path){
    file_path = path + file + ".tga";
    getFileImage(file_path);
}

void Image::getFileImage(string filepath){
    ifstream file(filepath, ios_base::binary);

    if (file.is_open()) {
        // file.read(&header.idLength, 4);
        file.read(&header.idLength, sizeof(header.idLength));
        file.read(&header.colorMapType, sizeof(header.colorMapType));
        file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
        file.read(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
        file.read(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
        file.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
        file.read(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
        file.read(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
        file.read(reinterpret_cast<char*>(&header.width), sizeof(header.width));
        file.read(reinterpret_cast<char*>(&header.height), sizeof(header.height));
        file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

        unsigned int pixel_number = header.width * header.height;

        vector<Pixel> px(pixel_number);
        for (unsigned int i = 0; i < pixel_number; i++){
            file.read(reinterpret_cast<char*>(&px[i].blue), 1);
            file.read(reinterpret_cast<char*>(&px[i].green), 1);
            file.read(reinterpret_cast<char*>(&px[i].red), 1);
        }
        pixels = px;
//        cout << "File Image Data Has Been Read." << endl;
    }
}

void Image::printFileHeader(Header file){
    cout << "Header Info" << endl;
    cout << "------------" << endl;
	cout << "ID Length: " << (int) file.idLength << endl;
	cout << "Color Map Type: " << (int) file.colorMapType << endl;
	cout << "Data Type Code: " << (int) file.dataTypeCode << endl;
	cout << "Color Map Origin: " << (int) file.colorMapOrigin << endl;
	cout << "Color Map Length: " << (int) file.colorMapLength << endl;
	cout << "Color Map Depth: " << (int) file.colorMapDepth << endl;
	cout << "x Origin: " << (int) file.xOrigin << endl;
	cout << "y Origin: " << (int) file.yOrigin << endl;
	cout << "Width: " << (int) file.width << endl;
	cout << "Height: " << (int) file.height << endl;
	cout << "Bits Per Pixel: " << (int) file.bitsPerPixel << endl;
	cout << "Image Descriptor: " << (int) file.imageDescriptor << endl;

}

void Image::copyPixels(string filepath){
    ofstream outfile(filepath, ios_base::binary);
    if (outfile.is_open()){
        for (unsigned int i = 0; i < pixels.size(); i++){
            outfile.write(reinterpret_cast<char*>(&pixels[i].blue), 1);
            outfile.write(reinterpret_cast<char*>(&pixels[i].green), 1);
            outfile.write(reinterpret_cast<char*>(&pixels[i].red), 1);
        }
    }
}

void Image::writeFile(string filepath){

    string filename = "../output/" + filepath;
    ofstream outfile(filename, ios_base::binary);

    if (outfile.is_open()){
        outfile.write(reinterpret_cast<char*>(&header.idLength), sizeof(header.idLength));
        outfile.write(reinterpret_cast<char*>(&header.colorMapType), sizeof(header.colorMapType));
        outfile.write(reinterpret_cast<char*>(&header.dataTypeCode), sizeof(header.dataTypeCode));
        outfile.write(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
        outfile.write(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
        outfile.write(reinterpret_cast<char*>(&header.colorMapDepth), sizeof(header.colorMapDepth));
        outfile.write(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
        outfile.write(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
        outfile.write(reinterpret_cast<char*>(&header.width), sizeof(header.width));
        outfile.write(reinterpret_cast<char*>(&header.height), sizeof(header.height));
        outfile.write(reinterpret_cast<char*>(&header.bitsPerPixel), sizeof(header.bitsPerPixel));
        outfile.write(reinterpret_cast<char*>(&header.imageDescriptor), sizeof(header.imageDescriptor));

        for (unsigned int i = 0; i < pixels.size(); i++){
            outfile.write(reinterpret_cast<char*>(&pixels[i].blue), 1);
            outfile.write(reinterpret_cast<char*>(&pixels[i].green), 1);
            outfile.write(reinterpret_cast<char*>(&pixels[i].red), 1);
        }
    }
}

void Image::addColor(string color, int value){
    for (unsigned int i = 0; i < pixels.size(); i++){
        if (color == "red"){
            if ((pixels[i].red + value) > 255)
				pixels[i].red = 255; 
			else
				pixels[i].red += value; 
        }
        else if (color == "green"){
            if ((pixels[i].green + value) > 255)
				pixels[i].green = 255; 
			else
				pixels[i].green += value;
        }
        else if (color == "blue"){
            if ((pixels[i].blue + value) > 255)
				pixels[i].blue = 255; 
			else
				pixels[i].blue += value;
        }
        else {
            cout << "You did not pick a valid color." << endl;
            break; 
        }
    }
}

void Image::multiplyColor(string color, int value){
    for (unsigned int i = 0; i < pixels.size(); i++){
        if (color == "red"){
            if ((pixels[i].red * value) > 255)
				pixels[i].red = 255; 
			else
				pixels[i].red *= value; 
        }
        else if (color == "green"){
            if ((pixels[i].green * value) > 255)
				pixels[i].green = 255; 
			else
				pixels[i].green *= value;
        }
        else if (color == "blue"){
            if ((pixels[i].blue * value) > 255)
				pixels[i].blue = 255; 
			else
				pixels[i].blue *= value;
        }
        else {
            cout << "You did not pick a valid color." << endl;
            break; 
        }
    }
}

void Image::setGrey(string color){
    for (unsigned int i = 0; i < pixels.size(); i++){
        int val = 0;
        if (color == "red"){
            val = pixels[i].red;
			pixels[i].green = val;
			pixels[i].blue = val;
        }
        else if (color == "green"){
            val = pixels[i].green;
			pixels[i].blue = val;
			pixels[i].red = val;
        }
        else if (color == "blue"){
            val = pixels[i].blue;
			pixels[i].red = val;
			pixels[i].green = val;
        }
        else {
            cout << "You did not pick a valid color." << endl;
            break; 
        }
    }
}

void Image::reloadImage(){
    ifstream file(file_path, ios_base::binary);

    if (file.is_open()) {
        file.read(&header.idLength, sizeof(header.idLength));
        file.read(&header.colorMapType, sizeof(header.colorMapType));
        file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
        file.read(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
        file.read(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
        file.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
        file.read(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
        file.read(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
        file.read(reinterpret_cast<char*>(&header.width), sizeof(header.width));
        file.read(reinterpret_cast<char*>(&header.height), sizeof(header.height));
        file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

        unsigned int pixel_number = header.width * header.height;

        vector<Pixel> px(pixel_number);
        for (unsigned int i = 0; i < pixel_number; i++){
            file.read(reinterpret_cast<char*>(&px[i].blue), 1);
            file.read(reinterpret_cast<char*>(&px[i].green), 1);
            file.read(reinterpret_cast<char*>(&px[i].red), 1);
        }
        pixels = px;
        cout << "File Image Data Has Been Reloaded." << endl;
    }
}

void Image::setSize(int height, int width){
    header.height = height;
    header.width = width;
}

// bool Image::operator== (const Image& rhs){
//     char* argv[] = system("diff " + filepath + " "rhs.filepath)
    
//     if (argv.size() != 0) {
//         cout << "difference" << endl;
//         for (unsigned int i = 0; i < argv.size(); i++)
//             cout << argv[i] << endl;
//         return false;
//     }
//     return true;
// }

bool Image::operator== (const Image& rhs){
    bool val = true;
    if (header.idLength != rhs.header.idLength) {
		cout << "Id length Difference" << endl;
		val = false;
	}
    if (header.colorMapType != rhs.header.colorMapType) {
		cout << "Color Map Type Difference" << endl;
		val = false;
	}
    if (header.dataTypeCode != rhs.header.dataTypeCode) {
		cout << "Data Type Code Difference" << endl;
		val = false;
	}
	if (header.colorMapOrigin != rhs.header.colorMapOrigin) {
		cout << "Color Map Origin Difference" << endl;
		val = false;
	}
	if (header.colorMapLength != rhs.header.colorMapLength) {
		cout << "Color Map Length Difference" << endl;
		val = false;
	}
	if (header.colorMapDepth != rhs.header.colorMapDepth) {
		cout << "Color Map Depth Difference" << endl;
		val = false;
	}
	if (header.xOrigin != rhs.header.xOrigin) {
		cout << "X Origin Difference" << endl;
		val = false;
	}
	if (header.yOrigin != rhs.header.yOrigin) {
		cout << "Y Origin Difference" << endl;
		val = false;
	}
	if (header.width != rhs.header.width) {
		cout << "Width Difference" << endl;
		val = false;
	}
	if (header.height != rhs.header.height) {
		cout << "Height Difference" << endl;
		val = false;
	}
	if (header.bitsPerPixel != rhs.header.bitsPerPixel) {
		cout << "Bits Per Pixel Difference" << endl;
		val = false;
	}
	if (header.imageDescriptor != rhs.header.imageDescriptor) {
		cout << "Image Descriptor Difference";
		val = false;
	}
	if (pixels.size() != rhs.pixels.size()) {
		cout << "Pixel Count Difference";
		val = false;
	}    
    for (unsigned int i = 0; i < pixels.size(); i++) {
		if (pixels[i].red != rhs.pixels[i].red) {
//			cout << "Red Pixel Difference at " << i << endl;
			val = false;
		}
		if (pixels[i].green != rhs.pixels[i].green) {
//			cout << "Green Pixel Difference at " << i << endl;
			val = false;
		}
		if (pixels[i].blue != rhs.pixels[i].blue) {
//			cout << "Blue Pixel Difference at " << i << endl;
			val = false;
		}
	}
    return val;
}

Image Image::operator * (const Image& rhs){
    for (unsigned int i = 0; i < pixels.size(); i++) {
		pixels[i].red = (int)(((float)pixels[i].red * (float)rhs.pixels[i].red/255)+0.5f);
        pixels[i].green = (int)(((float)pixels[i].green * (float)rhs.pixels[i].green/255)+0.5f);
        pixels[i].blue = (int)(((float)pixels[i].blue * (float)rhs.pixels[i].blue/255)+0.5f);
    }
    return *this;
}

Image Image::operator - (const Image& rhs){
    for (unsigned int i = 0; i < pixels.size(); i++) {
		pixels[i].red = ((int)(pixels[i].red - rhs.pixels[i].red) < 0) ? 0 : (int)(pixels[i].red - rhs.pixels[i].red);
        pixels[i].green = ((int)(pixels[i].green - rhs.pixels[i].green) < 0) ? 0 : (int)(pixels[i].green - rhs.pixels[i].green);
        pixels[i].blue = ((int)(pixels[i].blue - rhs.pixels[i].blue) < 0) ? 0 : (int)(pixels[i].blue - rhs.pixels[i].blue);
    }
    return *this;
}

void Image::mergeThree(Image &g, Image &b){
    for (unsigned int i = 0; i < pixels.size(); i++){
        pixels[i].green = g.pixels[i].green;
        pixels[i].blue = b.pixels[i].blue;
    }
}

void Image::rotate(Image &a){
    for (unsigned int i = 0; i < pixels.size(); i++) {
		pixels[i] = a.pixels[pixels.size()-i-1];
	}
}

Image Image::operator = (const Image& rhs){
    header.idLength = rhs.header.idLength;
    header.colorMapType = rhs.header.colorMapType;
    header.dataTypeCode = rhs.header.dataTypeCode;
    header.colorMapOrigin = rhs.header.colorMapOrigin;
    header.colorMapLength = rhs.header.colorMapLength;
    header.colorMapDepth = rhs.header.colorMapDepth;
    header.xOrigin = rhs.header.xOrigin;
    header.yOrigin = rhs.header.yOrigin;
    header.width = rhs.header.width;
    header.height = rhs.header.height;
    header.bitsPerPixel = rhs.header.bitsPerPixel;
    header.imageDescriptor = rhs.header.imageDescriptor;
    unsigned int pixel_number = header.width * header.height;
    vector<Pixel> px(pixel_number);
    for (unsigned int i = 0; i < pixel_number; i++){
        px[i].red = rhs.pixels[i].red;
        px[i].blue = rhs.pixels[i].blue;
        px[i].green = rhs.pixels[i].green;    
    }
    pixels = px;

    return *this;
}

void Image::screen(Image &a){
    for (unsigned int i = 0; i < pixels.size(); i++) {
        pixels[i].blue = (int)(((1-((1-(float)pixels[i].blue/255)*(1-(float)a.pixels[i].blue/255)))*255)+0.5f);
        pixels[i].green = (int)(((1-((1-(float)pixels[i].green/255)*(1-(float)a.pixels[i].green/255)))*255)+0.5f);
        pixels[i].red = (int)(((1-((1-(float)pixels[i].red/255)*(1-(float)a.pixels[i].red/255)))*255)+0.5f);
    }
}

void Image::overlay(Image &a){
    for (unsigned int i = 0; i < pixels.size(); i++) {
        pixels[i].blue = ((float)a.pixels[i].blue/255 > 0.5f) ? (int)(((1-(2*(1-(float)pixels[i].blue/255)*(1-(float)a.pixels[i].blue/255)))*255)+0.5f) : (int)((((2*((float)pixels[i].blue)/255)*((float)a.pixels[i].blue/255))*255)+0.5f);
        pixels[i].green = ((float)a.pixels[i].green/255 > 0.5f) ? (int)(((1-(2*(1-(float)pixels[i].green/255)*(1-(float)a.pixels[i].green/255)))*255)+0.5f) : (int)((((2*((float)pixels[i].green)/255)*((float)a.pixels[i].green/255))*255)+0.5f);
        pixels[i].red = ((float)a.pixels[i].red/255 > 0.5f) ? (int)(((1-(2*(1-(float)pixels[i].red/255)*(1-(float)a.pixels[i].red/255)))*255)+0.5f) : (int)((((2*((float)pixels[i].red)/255)*((float)a.pixels[i].red/255))*255)+0.5f);;
    }
}