/*
  How do you see me now?
*/

// EDIT Tlc5940.cpp -> SET NUM_TLCS
#include "params.h"
#include "DdxCtl.h"
#include "Tlc5940.h"
#include <FastDigital.h>

// INIT
long buffer[MATRIX_HEIGHT][MATRIX_WIDTH] = { {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000} }; 
DdxCtl screen; // CREATE THE SCREEN
screen.setBuffer(buffer);

void setup(){
    // 
    pinModeFast(DATAPIN, OUTPUT);
    pinModeFast(CLOCKPIN, OUTPUT);
    pinModeFast(LATCHPIN, OUTPUT);
    digitalWriteFast(LATCHPIN, HIGH);
    //
    
}


void loop(){
    screen.refresh();
}
