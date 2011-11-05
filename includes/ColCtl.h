/* 
 * File:   ColCtl.h
 * Author: info03
 *
 * Created on 11 octobre 2011, 10:56
 */
#include <Tlc5940.h>

#ifndef COLCTL_H
#define	COLCTL_H

// SOFTWARE COLOR CORRECTION
// THIS IS USED TO CORRECT IREFs MARGIN OF ERROR
#define MAX_RED 1400 / 255
#define MAX_GREEN 3150 / 255
#define MAX_BLUE 2600 / 255


class ColCtl : protected Tlc5940 {
public:
    void setColor(int nLed, long hexVal);
    void update(void);
    void updateSync(void);
private:

};

// for the preinstantiated Col variable.
extern ColCtl Col;

#endif	/* COLCTL_H */

