/* 
 * File:   ColCtl.cpp
 * Author: info03
 * 
 * Created on 11 octobre 2011, 10:56
 */
#include <Tlc5940.h>
#include "ColCtl.h"

void ColCtl::setColor(int led, long hexColor){
    set(led,   ( (hexColor >> 16) & 0xFF) * MAX_RED);
    set(led+16,( (hexColor >> 8) & 0xFF) * MAX_GREEN);
    set(led+32,( hexColor & 0xFF) * MAX_BLUE);
}

void ColCtl::update(void){
    update();
}

void ColCtl::updateSync(void){
    update();
    while (Tlc.updateInProgress());
}

// for the preinstantiated Col variable.
ColCtl Col;