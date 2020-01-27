#ifndef FIREWIDE_H
#define FIREWIDE_H

void firewide() {                                                               // Create fire based on noise and sampleAvg. 

// Local definitions
  #define xscale 20                                                             // How far apart they are
  #define yscale 3                                                              // How fast they move

// Persistent local variables

// Temporary local variables
  uint16_t index = 0;                                                            // Current colour lookup value.


  currentPalette = CRGBPalette16(CHSV(0,255,2), CHSV(0,255,4), CHSV(0,255,6), CHSV(0, 255, 8),    // Fire palette definition. Lower value = darker.
                                 CHSV(0, 255, 16), CRGB::Red, CRGB::Red, CRGB::Red,                                   
                                 CRGB::DarkOrange,CRGB::DarkOrange, CRGB::Orange, CRGB::Orange,
                                 CRGB::Yellow, CRGB::Orange, CRGB::Yellow, CRGB::Yellow);
  
  for(int i = 0; i < NUM_LEDS; i++) {

    index = inoise8(i*xscale,millis()*yscale*NUM_LEDS/255);                       // X location is constant, but we move along the Y at the rate of millis(). By Andrew Tuline.

    index = (255 - i*256/NUM_LEDS) * index / 128;                                 // Now we need to scale index so that it gets blacker as we get close to one of the ends
                                                                                
    leds[NUM_LEDS/2-i/2+1] = ColorFromPalette(currentPalette, index, sampleAvg*4, NOBLEND);      // With that value, look up the 8 bit colour palette value and assign it to the current LED. 
    leds[NUM_LEDS/2+i/2-1] = ColorFromPalette(currentPalette, index, sampleAvg*4, NOBLEND);      // With that value, look up the 8 bit colour palette value and assign it to the current LED. 
    
  }                                                                               // The higher the value of i => the higher up the palette index (see palette definition).

} // firewide()

#endif
