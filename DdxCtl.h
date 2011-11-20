/* 
 * File:   DdxCtl.h
 * Author: Allan
 *
 * Created on 20 novembre 2011, 16:55
 */

#ifndef DDXCTL_H
#define	DDXCTL_H



class DdxCtl {
public:
    DdxCtl();

    // MATRIX CTL
    void setBuffer();
    void refresh();
    void setRate(int rate);
    void turnOff();
    

private:
    // ATTIBUTES
    int m_width;
    int m_height;
    int m_currRow;
    int m_rate;
    long* buffer[MATRIX_HEIGHT][MATRIX_WIDTH];

    // ROW CTL
    void setRow(const int nRow );
    void nextRow();
    void setNoRow();
        // LOW LEVEL STUFFS
        void toggleLatch();
//        void shiftOut();

    // COLOR CTL
    void setColor(int nLed, long hexColor);
    void updateRow();

};

#endif	/* DDXCTL_H */
