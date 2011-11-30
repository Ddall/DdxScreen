/* 
 * File:   MatrixCtl.h
 * Author: Allan
 *
 * Created on 30 octobre 2011, 13:46
 */

#ifndef MATRIXCTL_H
#define	MATRIXCTL_H

// #####GLOGAL DEFINITION#####
    #define MATRIX_HEIGHT 8
    #define MATRIX_WIDTH 8


// #####ROW CTL#####
    // shiftOut / digitalWrite DEFINITION
//    #include <wiring_shift.c> // NO NEED...
    #include <FastDigital.h>

    // SHIFT REGISTER WIRING CONFIGURATION
    #define DATAPIN 5 // BLU WIRE
    #define CLOCKPIN 6 // YELLOW WIRE
    #define LATCHPIN 7 // GREEN WIRE


// #####COLOR CTL#####
    // TLC5940 CONTROL LIBRARY
    #include <Tlc5940.h>

    // SOFTWARE COLOR CORRECTION
    #define MAX_RED 1400 / 255
    #define MAX_GREEN 3150 / 255
    #define MAX_BLUE 2600 / 255


class MatrixCtl {
public:
    void refresh();
    void disable();
    void paint(long color);

private:
    // ROW CTL
    void setRow(int nRow);
    void turnOff();
    void toggleLatch();


    // COLOR CTL
    void setColor(int nLed, long hexColor);
    void setLine(long[MATRIX_WIDTH], long hexColor);
    void lineUpdate();
    void lineUpdate(bool wait);

    int currentRow;
    bool needUpdate;

};

// PREINSTANCIATED MATRIX VARIABLE
extern MatrixCtl Matrix;

#endif	/* MATRIXCTL_H */
