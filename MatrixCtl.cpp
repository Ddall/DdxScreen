/* 
 * File:   MatrixCtl.cpp
 * Author: Allan
 * 
 * Created on 30 octobre 2011, 13:46
 */

#include "MatrixCtl.h"
#include <wiring_shift.c> // shiftOut / digitalWrite DEFINITION
#include <Tlc5940.h>

long frameBuffer[8][8] ={ {0x000000,0x000000,0xffff00,0xffff00,0xffff00,0xffff00,0x000000,0x000000}, {0x000000,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0x000000}, {0xffff00,0xffff00,0x0000ff,0xffff00,0xffff00,0x0000ff,0xffff00,0xffff00}, {0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00}, {0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00}, {0xffff00,0xffff00,0x0000ff,0xffff00,0xffff00,0x0000ff,0xffff00,0xffff00}, {0x000000,0xffff00,0xffff00,0x0000ff,0x0000ff,0xffff00,0xffff00,0x000000}, {0x000000,0x000000,0xffff00,0xffff00,0xffff00,0xffff00,0x000000,0x000000} }; 


// PUBLIC

    // GLOBAL CTL

void MatrixCtl::refresh(){
    Tlc.clear(); // CLEAR THE LINE
    for(int row =0; row < MATRIX_HEIGHT; row++ ){
        for(int led = 0; led < MATRIX_WIDTH; led++){
            setColor(led, frameBuffer[row][led]);
        }
        turnOff();
        Tlc.update();
        while(Tlc.updateInProgress());
        setRow(row);
        
    }
}



// PRIVATE
    //ROW CTL

void MatrixCtl::setRow(int nRow){
    // SELECT THE REGISTER
        //PUSH DATA (MSBFIRST == LAST REGISTER FIRST!!!)
    if(nRow < 8){ // REGISTER #1 DRIVES ROWS 0 to 7, 
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, byte(0));
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, byte(0));
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, bit(nRow));
    }
    else if(nRow < 16){ //REGISTER #2 DRIVES ROWS 8 to 15,
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, byte(0));
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, bit(nRow));  
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, byte(0));
    }
    else if(nRow < 24){ // REGISTER #3 DRIVES ROWS 16 to 23,
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, bit(nRow));
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, byte(0));
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, byte(0));
    }
    
    // TOGGLE THE LATCH PIN TO UPDATE ROWS
    toggleLatch();
    currentRow = nRow;
}


void MatrixCtl::toggleLatch(){
    digitalWrite(LATCHPIN, 0);
    digitalWrite(LATCHPIN, 1);
}

void MatrixCtl::turnOff(){
    // SEND INVALID DATA TO THE SRs
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, bit(100));
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, bit(100));
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, bit(100));  
    
    toggleLatch();
}


// COLOR CTL
void MatrixCtl::setColor(int nLed, long hexColor){
    // WARNING: THIS WILL NOT WORK ON FINAL HARDWARE
    Tlc.set(nLed, ((hexColor >> 16) & 0xFF) * MAX_RED);
    Tlc.set(nLed+16,((hexColor >> 8) & 0xFF) * MAX_GREEN);
    Tlc.set(nLed+32,(hexColor & 0xFF) * MAX_BLUE);
}

void MatrixCtl::setLine(long[], long hexColor){
    // TODO: FINISH setLine();
}

void MatrixCtl::lineUpdate(){
    Tlc.update();
}

void MatrixCtl::lineUpdate(bool wait){
    Tlc.update();
    if(wait){
        while(Tlc.updateInProgress()); // WAIT
    }
}
// PREINSTANCIATED MATRIX VARIABLE
MatrixCtl Matrix;