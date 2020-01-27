#ifndef SINEPHASE_H
#define SINEPHASE_H

// This routine modifies phases of a sinewave based on sampleAvg

void sinephase() {

// Local definitions

// Persistent local variables

// Temporary local variables


  for (int i=0; i<NUM_LEDS; i++) {

    int hue = sampleAvg*2 + sin8(i*4+beatsin16(13,-20,50));
    int bri = hue;
    bri = bri*bri/255;
    leds[i] = ColorFromPalette(currentPalette, hue, bri, currentBlending);
    
  }

} // sinephase()


#endif
