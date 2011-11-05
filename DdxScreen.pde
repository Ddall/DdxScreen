/*
  How do you see me now?
*/

// MATRIX DEFINITION
#define MATRIX_HEIGHT 8
#define MATRIX_WIDTH 8


// EDIT Tlc5940.cpp -> SET NUM_TLCS
#include <Tlc5940.h>
#include "MatrixCtl.h"


void setup(){
    Tlc.init(0);
}

void loop(){
    Matrix.refresh();
            
}
