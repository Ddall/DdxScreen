/*
  How do you see me now?
*/

// EDIT Tlc5940.cpp -> SET NUM_TLCS
#include "params.h"
#include "FastDigital.h"
#include <Tlc5940.h>
#include "MatrixCtl.h"


void setup(){
    Tlc.init(0);
}

void loop(){
    Matrix.refresh();
}
