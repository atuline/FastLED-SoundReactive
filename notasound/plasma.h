#ifndef PLASMA_H
#define PLASMA_H

void plasma() {

// Local definitions

// Persistent local variables
  static int16_t thisphase = 0;                                                 // Phase of a cubicwave8.
  static int16_t thatphase = 0;                                                 // Phase of the cos8.

// Temporary local variables
  uint16_t thisbright;
  uint16_t colorIndex;


  thisphase += beatsin8(6,-4,4);                                                // You can change direction and speed individually.
  thatphase += beatsin8(7,-4,4);                                                // Two phase values to make a complex pattern. By Andrew Tuline.

  for (int k=0; k<NUM_LEDS; k++) {                                              // For each of the LED's in the strand, set a brightness based on a wave as follows.
    thisbright = cubicwave8((k*8)+thisphase)/2;    
    thisbright += cos8((k*10)+thatphase)/2;                                     // Let's munge the brightness a bit and animate it all with the phases.
    colorIndex=thisbright;
    thisbright = qsuba(thisbright, 255 - sampleAvg*4);                    // qsuba chops off values below a threshold defined by sampleAvg. Gives a cool effect.
 
 //#define qsuba(x, b)  ((x>b)?x-b:0)                            // Unsigned subtraction macro. if result <0, then => 0.
    
    leds[k] += ColorFromPalette( currentPalette, colorIndex, thisbright, currentBlending);   // Let's now add the foreground colour.
  }

     fadeToBlackBy(leds, NUM_LEDS, 64); 
     
} // plasma()

#endif
