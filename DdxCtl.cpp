/* 
 * File:   DdxCtl.cpp
 * Author: info03
 * 
 * Created on 30 novembre 2011, 09:56
 */

#include "DdxCtl.h"
#include "params.h"
#include <FastDigital.h>
#include "Tlc5940.h"
#include <wiring_shift.c>


// PUBLIC
DdxCtl::DdxCtl() {
    m_width = MATRIX_WIDTH;
    m_height = MATRIX_HEIGHT;
    
    m_rate = MATRIX_REFRESH_RATE;
    m_currRow = 0;
    
    m_buffer = 0;
    
 // TODO FIX THESE TWO!!
 //   pinModeFast(LATCHPIN, OUTPUT);
 //   digitalWriteFast(LATCHPIN, HIGH);
}

void DdxCtl::refresh(){
    for(int y = 0; y < MATRIX_HEIGHT; y++){  // CYCLE ROWS
        
        for(int x = 0; x < MATRIX_WIDTH; x++){ // CYCLE LEDS
           // setColor(x, m_buffer[y][x]);
        }
        
        //delayMicroseconds() // NEED TO WAIT?
        
        turnOff(); // TURNS THE ROW OFF DURING UPDATE
        Tlc.update();
        while(Tlc.updateInProgress()); // WAIT FOR UPDATE TO FINISH (USING HARDWARE SPI MAKE Tlc.update(); ASYNCHRONOUS
        setRow(y); // TURN THE NEW UP
    }
}

void DdxCtl::setBuffer(long *buffer){
    m_buffer = buffer;
}

// ROW CTL
void DdxCtl::setRow(int nRow){
    // SELECT THE REGISTER
    //PUSH DATA (MSBFIRST == LAST REGISTER FIRST!!!)
    if(nRow < 8){ // REGISTER #1 DRIVES ROWS 0 to 7, 
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, bit(nRow));
    }
    else if(nRow < 16){ //REGISTER #2 DRIVES ROWS 8 to 15,
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, bit(nRow - 8));  
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    }
    else if(nRow < 24){ // REGISTER #3 DRIVES ROWS 16 to 23,
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, bit(nRow - 16));
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    }
    
    // TOGGLE THE LATCH PIN TO UPDATE ROWS
    this->toggleLatch();
    
    m_currRow = nRow;    
}

void DdxCtl::nextRow(){
    if(m_currRow < m_height){
        m_currRow = 0;
    }

    this->setRow(m_currRow);
    
}

void DdxCtl::toggleLatch(){
    // TODO FIX THESE
    // digitalWriteFast(LATCHPIN, LOW);
    // digitalWriteFast(LATCHPIN, HIGH);
    
    digitalWrite(LATCHPIN, LOW);
    digitalWrite(LATCHPIN, HIGH);
}

void DdxCtl::turnOff(){
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    
    this->toggleLatch();
}

// COLOR CTL
void DdxCtl::setColor(int nLed, long hexColor){
    
}

void DdxCtl::updateRow(){
    
}