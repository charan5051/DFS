//
//  main.cpp
//  Sudoku
//
#include <iostream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "VisualDisplay.h"

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    VisualDisplay display;
    display.load("imgs/sudoku.png");
    display.run();
    return 0;
}
