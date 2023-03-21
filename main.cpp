#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <algorithm>
#include "image.h"
// #include "functions.h"

using namespace std;

int main(){
    Image car = Image("car");
    Image circles = Image("circles");
    Image layer_blue = Image("layer_blue");
    Image layer_green = Image("layer_green");
    Image layer_red = Image("layer_red");
    Image layer1 = Image("layer1");
    Image layer2 = Image("layer2");
    Image pattern1 = Image("pattern1");
    Image pattern2 = Image("pattern2");
    Image text = Image("text");
    Image text2 = Image("text2");

    // examples given to us
    Image part1 = Image("EXAMPLE_part1", "../examples/");
    Image part2 = Image("EXAMPLE_part2", "../examples/");
    Image part3 = Image("EXAMPLE_part3", "../examples/");
    Image part4 = Image("EXAMPLE_part4", "../examples/");
    Image part5 = Image("EXAMPLE_part5", "../examples/");
    Image part6 = Image("EXAMPLE_part6", "../examples/");
    Image part7 = Image("EXAMPLE_part7", "../examples/");
    Image part8_b = Image("EXAMPLE_part8_b", "../examples/");
    Image part8_g = Image("EXAMPLE_part8_g", "../examples/");
    Image part8_r = Image("EXAMPLE_part8_r", "../examples/");
    Image part9 = Image("EXAMPLE_part9", "../examples/");
    Image part10 = Image("EXAMPLE_part10", "../examples/");

    cout << endl;

    cout << "What would you like to do? " << endl;
    cout << "1. Multiply layer1.tga with pattern1.tga" << endl;
    cout << "2. Subtract layer2.tga with car.tga" << endl;
    cout << "3. Multiply layer1.tga with pattern2.tga and add text" << endl;
    cout << "4. Multiply layer2.tga with circles.tga combined with previous result using the subtract blending mode" << endl;
    cout << "5. Combine layer1.tga with pattern1.tga using the Overlay blending mode" << endl;
    cout << "6. Load car.tga and add 200 to the green channel" << endl;
    cout << "7. Load car.tga and scale the red channel by 4 and blue by 0" << endl;
    cout << "8. Load car.tga and write each channel to a separate file" << endl;
    cout << "9. Combine layer_red.tga, layer_green.tga, layer_blue.tga" << endl;
    cout << "10. Rotate text2.tga 180 degrees" << endl;
    cout << "Choice: " << endl;

    string choice;
    cin >> choice;
    cout << endl;

    if (choice == "1"){
        layer1 = layer1 * pattern1;
        layer1.writeFile("part1.tga");
        cout << "Test 1 " << endl;
        if (layer1 == part1) {
            cout << "Pass" << endl;
        }
        else {
            cout << "Fail" << endl;
        }
        layer1.reloadImage();
    }
    else if (choice == "2"){
        layer2 = car - layer2;
        layer2.writeFile("part2.tga");
        cout << "Test 2 " << endl;
        if (layer2 == part2) {
            cout << "Pass" << endl;
        }
        else {
            cout << "Fail" << endl;
        }
        layer2.reloadImage();
    }
    else if (choice == "3"){
        layer1 = layer1 * pattern2;
//        layer1.writeFile("Part3_Multiply.tga");
        text.screen(layer1);
        text.writeFile("part3.tga");
        cout << "Test 3" << endl;
        if (text == part3) {
            cout << "Pass" << endl;
        }
        else {
            cout << "Fail" << endl;
        }
        layer1.reloadImage();
        text.reloadImage();
    }
    else if (choice == "4"){
        layer2 = layer2 * circles;
        layer2 = layer2 - pattern2;
        layer2.writeFile("part4.tga");
        cout << "Test 4" << endl;
        if (layer2 == part4) {
            cout << "Pass" << endl;
        }
        else {
            cout << "Fail" << endl;
        }
        layer2.reloadImage();
    }
    else if (choice == "5"){
        layer1.overlay(pattern1);
        layer1.writeFile("part5.tga");
        cout << "Test 5" << endl;
        if (layer1 == part5) {
            cout << "Pass" << endl;
        }
        else {
            cout << "Fail" << endl;
        }
        layer1.reloadImage();
    }
    else if (choice == "6"){
        car.addColor("green", 200);
        car.writeFile("part6.tga");
        cout << "Test 6" << endl;
        if (car == part6) {
            cout << "Pass" << endl;
        }
        else {
            cout << "Fail" << endl;
        }
        car.reloadImage();
    }
    else if (choice == "7"){
        car.multiplyColor("red", 4);
        car.multiplyColor("blue", 0);
        car.writeFile("part7.tga");
        cout << "Test 7" << endl;
        if (car == part7) {
            cout << "Pass" << endl;
        }
        else {
            cout << "Fail" << endl;
        }
        car.reloadImage();
    }
    else if (choice == "8"){
        cout << "Test 8" << endl;
        car.setGrey("red");
        car.writeFile("part8_r.tga");
        if (car == part8_r) {
            cout << "Pass" << endl;
        }
        else {
            cout << "Fail" << endl;
        }
        car.reloadImage();
        car.setGrey("green");
        car.writeFile("part8_g.tga");
        if (car == part8_g) {
            cout << "Pass" << endl;
        }
        else {
            cout << "Fail" << endl;
        }
        car.reloadImage();
        car.setGrey("blue");
        car.writeFile("part8_b.tga");
        if (car == part8_b) {
            cout << "Pass" << endl;
        }
        else {
            cout << "Fail" << endl;
        }
        car.reloadImage();
    }
    else if (choice == "9"){
        layer_red.mergeThree(layer_green, layer_blue);
        layer_red.writeFile("part9.tga");
        cout << "Test 9" << endl;
        if (layer_red == part9) {
            cout << "Pass" << endl;
        }
        else {
            cout << "Fail" << endl;
        }
        layer_red.reloadImage();
    }
    else if (choice == "10"){
        Image test = text2;
        text2.rotate(test);
        text2.writeFile("part10.tga");
        cout << "Test 10" << endl;
        if (text2 == part10) {
            cout << "Pass" << endl;
        }
        else {
            cout << "Fail" << endl;
        }
        text2.reloadImage();
    }
    else {cout << "That was not a valid option." << endl;}
}