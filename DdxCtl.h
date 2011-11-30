/* 
 * File:   DdxCtl.h
 * Author: info03
 *
 * Created on 30 novembre 2011, 09:56
 */

#ifndef DDXCTL_H
#define	DDXCTL_H

class DdxCtl {
public:
    DdxCtl();
    
    void refresh();
    void setBuffer(long *buffer);

private:
    int m_width;
    int m_height;
    int m_currRow;
    int m_rate;
    long* m_buffer;
    
    // ROW CTL
    void setRow(int nRow);
    void nextRow();
    void toggleLatch();
    void turnOff();
    
    
    // COLOR CTL
    void setColor(int nLed, long hexColor);
    void updateRow();

};

#endif	/* DDXCTL_H */

