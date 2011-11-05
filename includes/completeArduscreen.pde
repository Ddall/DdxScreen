//
// Drifting along...
//

// TODO: 
// - DOUBLE FRAME BUFFER = DOUBLE RAINBOW?

#include "Tlc5940.h"
// -> GO TO C:\Program Files (x86)\arduino-0022\libraries\Tlc5940 TO DEFINE NUM_TLCS


// ####### SHIFT REGISTERS PARAMETERS ####### //

  // DELETE THIS SECTION IF USING TRUE C shiftOut()
  const byte dataPin = 5; // BLU WIRE
  const byte clockPin = 6; // YELLOW WIRE
  const byte latchPin = 7; // GREEN WIRE
  
  //VARIABLES USED IN setRow()
  byte register0 = 0;
  byte register1 = 0;
  byte register2 = 0;
  

// ####### TLC5940/COLOR PARAMS ####### //

  // COLOR CORRECTION - MAX PWM VALUES 
  // USE COEF TO BYPASS map(): COEF = OUT_MAX / IN_MAX
  // DONT DELETE IN THE FINAL VERSION TO COMPENSATE IREF'S RESISTORS MARGIN OF ERROR
  const int MAX_RED_COEF = 1400 / 255;
  const int MAX_GREEN_COEF = 3150 / 255;
  const int MAX_BLUE_COEF = 2600 / 255;
  
// ####### OUTPUT MATRIX PARAMS ####### //

  // SIZE
  const byte X_MATRIX = 8;
  const byte Y_MATRIX = 8;
  
// ** MATRIXES AND PATTERNS **
//const int N_CHARS = 2;
//long table[N_CHARS][8][8] = {{ {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0xff00ff,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0xff00ff,0x000000,0x00ff00,0x000000,0x000000,0x000000}, {0x000000,0x000000,0xff00ff,0x000000,0x00ff00,0x000000,0x000000,0x000000}, {0x000000,0x000000,0xff00ff,0x000000,0x00ffff,0x000000,0x000000,0x000000}, {0x000000,0x000000,0xff00ff,0x000000,0xff00ff,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0xff00ff,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000} }, { {0x000000,0x000000,0xffff00,0xffff00,0xffff00,0xffff00,0x000000,0x000000}, {0x000000,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0x000000}, {0xffff00,0xffff00,0x0000ff,0xffff00,0xffff00,0x0000ff,0xffff00,0xffff00}, {0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00}, {0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00}, {0xffff00,0xffff00,0x0000ff,0xffff00,0xffff00,0x0000ff,0xffff00,0xffff00}, {0x000000,0xffff00,0xffff00,0x0000ff,0x0000ff,0xffff00,0xffff00,0x000000}, {0x000000,0x000000,0xffff00,0xffff00,0xffff00,0xffff00,0x000000,0x000000} }}; 

// SMILEY FACE
long buffer[8][8] ={ {0x000000,0x000000,0xffff00,0xffff00,0xffff00,0xffff00,0x000000,0x000000}, {0x000000,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0x000000}, {0xffff00,0xffff00,0x0000ff,0xffff00,0xffff00,0x0000ff,0xffff00,0xffff00}, {0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00}, {0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00,0xffff00}, {0xffff00,0xffff00,0x0000ff,0xffff00,0xffff00,0x0000ff,0xffff00,0xffff00}, {0x000000,0xffff00,0xffff00,0x0000ff,0x0000ff,0xffff00,0xffff00,0x000000}, {0x000000,0x000000,0xffff00,0xffff00,0xffff00,0xffff00,0x000000,0x000000} }; 

// STRANGE PINK/GREEN/TURQUOISE PATTERN
//long buffer[8][8] ={ {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0xff00ff,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0xff00ff,0x000000,0x00ff00,0x000000,0x000000,0x000000}, {0x000000,0x000000,0xff00ff,0x000000,0x00ff00,0x000000,0x000000,0x000000}, {0x000000,0x000000,0xff00ff,0x000000,0x00ffff,0x000000,0x000000,0x000000}, {0x000000,0x000000,0xff00ff,0x000000,0xff00ff,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0xff00ff,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000} }; 

// ALL BLACK - DEFAULT BUFFER
// long buffer[8][8] ={ {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}, {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000} }; 

// ** END PATTERNS **

// *** SETUP ***
void setup(){
  // SHIFT REGISTER PINS SETUP TODO: REWRITE THIS USING TRUE C
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
    
  Tlc.init(0); // TLC Init (0 to default)

}
// ** END SETUP **

// *** LOOP ***
void loop(){
  refreshScreen(); 
} // END LOOP

// ** LOGIC STUFFS **

//changeImage: Changes the image stored in the buffer by looking for a new image in it's table (or A table in the future)
void changeImage(int nImage){

} // END changeImage()


// *** DISPLAY FUNCTIONS ***
// refreshScreen: display whaterver is in tha frame buffer
boolean needUpdate = 0;

void refreshScreen(){
  for(uint8_t x=0; x <= X_MATRIX; ++x){ // VERTICLAL LOOP
    needUpdate = 0;
    
    Tlc.clear();
    Tlc.update();
    while(tlc_needXLAT);
    
    for(int y=0; y<= Y_MATRIX; y++){ // HORIZONTAL LOOP
      if(buffer[x][y] != 0x000000){ // SKIP BLACK PIXELS -> MAKES LOOP TOO FAST! LOLOLOLOL NEEDS TO ADD A SMALL DELAY
        setColor(y, buffer[x][y]);
        needUpdate = 1;
      }
    } // END HORIZONTAL LOOP
    
    if(needUpdate){ // UPDATE TLC ONLY IF NEEDED
      setRow(x);
      Tlc.update();
      while(tlc_needXLAT);
    }
    
  } // END VERTICAL LOOP
}// END refreshScreen()

// setRow: Turns nRow up on the shiftRegister array
void setRow(int nRow){
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

  // PUSH 'THEM BYTES TO THE REGISTERS (PUSH LAST REGISTER FIRST)
  // TODO: REWRITE shiftOut WITH FIXED PINS AND TRUE C FUNCTIONS ONLY (wiring is wasting too much time)
  shiftOut(dataPin, clockPin, MSBFIRST, register2);
  shiftOut(dataPin, clockPin, MSBFIRST, register1);
  shiftOut(dataPin, clockPin, MSBFIRST, register0);
  
  // TOOGLE LATCH PIN TO WRITE NEW VALUES -> TRUE C VERSION OF digitalWrite() // TODO: BEURK PAS PORTABLE
  PORTD &= ~_BV(PD7);
  PORTD |= _BV(PD7);
} // END setRow()

// setColor: Apply hex value to a row (led)
int red, green, blue = 0;

void setColor(int led, long color){
  // - EXTRACT THE 16bit VALUE FOR EACH CHANNEL
  // - APPLY THE COLOR CORRECTION COEF
  // - SET THE TLC VALUE
  Tlc.set(led, ((color >> 16) & 0xFF) * MAX_RED_COEF);
  Tlc.set(led+16,( (color >> 8) & 0xFF) * MAX_GREEN_COEF);
  Tlc.set(led+32, ( color & 0xFF) * MAX_BLUE_COEF);
} // END setColor()


// setColorDebug: Print out the HEX VALUES to serial
void setColorDebug(int led, long color){
  
  int red = ((color >> 16) & 0xFF) * MAX_RED_COEF;
  int green = ( (color >> 8) & 0xFF) * MAX_GREEN_COEF;
  int blue =  ( color & 0xFF) * MAX_BLUE_COEF;
  
  Tlc.set(led, red);
  Tlc.set(led+16, green);
  Tlc.set(led+32, blue);
  
  Serial.print(led, DEC);
  Serial.print("\t");
  Serial.print(red, DEC);
  Serial.print("\t");
  Serial.print(green, DEC);
  Serial.print("\t");
  Serial.println(blue, DEC);
}

void setNull(int led){
  Tlc.set(led, 0);
  Tlc.set(led+16, 0);
  Tlc.set(led+32, 0);
}

// ** END DISPLAY FUNCTIONS **
