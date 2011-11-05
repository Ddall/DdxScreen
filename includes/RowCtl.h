/* 
 * File:   RowCtl.h
 * Author: Allan
 *
 * Created on 10 octobre 2011, 21:08
 */

#ifndef ROWCTL_H
#define	ROWCTL_H

class RowCtl {
public:
    void set(int nRow);
    void next(void);
    void turnOff(void);
    
    int get(void);
    
private:
    int currRow;
    bool on;
    
    void toggleLatch(void);

};

// preinstantiated Row variable
extern RowCtl Row;

#endif	/* ROWCTL_H */