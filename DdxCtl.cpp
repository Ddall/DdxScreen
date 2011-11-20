/* 
 * File:   DdxCtl.cpp
 * Author: Allan
 * 
 * Created on 20 novembre 2011, 16:55
 */
#include "params.h"
#include "DdxCtl.h"
#include <wiring_shift.c> // shiftOut / digitalWrite DEFINITION
#include "FastDigital.h"
#include <Tlc5940.h>

 // ############ CONSTRUCTEUR ############

DdxCtl::DdxCtl() {
    m_width = MATRIX_WIDTH;
    m_height = MATRIX_HEIGHT;
    
    m_rate = MATRIX_REFRESH_RATE;
    m_currRow = 0;
    
    pinModeFast(LATCHPIN, OUTPUT);
    digitalWriteFast(LATCHPIN, HIGH);
}

// ############ MATRIX CTL ############

DdxCtl::refresh(){
    
}


// ############ ROW CTL ############

DdxCtl::setRow(const int nRow){
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

DdxCtl::nextRow(){
    if(m_currRow < MATRIX_HEIGHT){
        m_currRow++;
    }else{
        m_currRow = 0;
    }
    
    this->setRow(m_currRow);
}

DdxCtl::toggleLatch(){
    digitalWriteFast(LATCHPIN, LOW);
    digitalWriteFast(LATCHPIN, HIGH);
}

DdxCtl::setNoRow(){
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    
    this->toggleLatch();
}

DdxCtl::setRate(int rate){
    
}

// ############ COLOR CTL ############

DdxCtl::setColor(int nLed, long hexColor){
    // WARNING MODIFIER CES VALEURS SUR L'HARDWARE FINAL
    
    Tlc.set(nLed, ((hexColor >> 16) & 0xFF) * MAX_RED);
    Tlc.set(nLed+16,((hexColor >> 8) & 0xFF) * MAX_GREEN);
    Tlc.set(nLed+32,(hexColor & 0xFF) * MAX_BLUE);
}

DdxCtl::updateRow(){
    Tlc.update();
}