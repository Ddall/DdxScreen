/* 
 * File:   RowCtl.cpp
 * Author: Allan
 * 
 * Created on 10 octobre 2011, 21:08
 */

#include "RowCtl.h"

// CONTAINS shiftOut DEFINITION
#include <wiring_shift.c>

// HOW MANY ROWS ?
#define NUM_ROWS 24
#define NUM_REGISTERS NUM_ROWS / 8

// SHIFT REGISTER CONFIGURATION
#define DATAPIN 5 // BLU WIRE
#define CLOCKPIN 6 // YELLOW WIRE
#define LATCHPIN 7 // GREEN WIRE


void RowCtl::set(int nRow){
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
}
/*
void RowCtl::set(int nRow){
  if( nRow < 8){
    register0 = bit(nRow);
    register1 = 0;
    register2 = 0;
  }
  else if (nRow < 16){
    register0 = 0;
    register1 = bit((nRow-8));
    register2 = 0;
  }
  else if (nRow < 24){
    register0 = 0;
    register1 = 0;
    register2 = bit((nRow-16));
  }
  else{
    register0 = 0;
    register1 = 0;
    register2 = 0;
  }

  // PUSH THE BYTES TO THE SHIFT REGISTERS (LAST REGISTER FIRST)
  shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, register2);
  shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, register1);
  shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, register0);
  
  // LATCH DATA
  toggleLatch();
}
 * */

void RowCtl::toggleLatch(){
    digitalWrite(LATCHPIN, 0);
    digitalWrite(LATCHPIN, 1);
}


void RowCtl::next(){
    if(currRow < NUM_ROWS){
        set(currRow++);
    }else{
        currRow = 0;
        set(currRow);
    }
}

void RowCtl::turnOff(){
    // SEND INVALID DATA TO THE SRs
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, bit(100));
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, bit(100));
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, bit(100));  
    
    toggleLatch();
}

int RowCtl::get(){
    return currRow;
}

// preinstantiated Row variable
RowCtl Row;