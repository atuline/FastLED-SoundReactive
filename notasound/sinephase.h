#ifndef SINEPHASE_H
#define SINEPHASE_H

// This routine modifies phases of a sinewave based on sampleAvg

void sinephase() {

// Local definitions

// Persistent local variables

// Temporary local variables


  for (int i=0; i<NUM_LEDS; i++) {

    int hue = sin8(i*4+sampleAgc) + sin8(i*4+beatsin16(6,-100,100) + sin8(i*4+beatsin16(13,-20,50)) - sin8(i*4+sampleAgc));

    int bri = hue;
//    bri = bri*bri/255;
    bri = bri*bri/255;        // Remember, it's already halved, so is equivalent to v = v*v*v*v
    leds[i] = ColorFromPalette(currentPalette, hue, bri, currentBlending);
    
  }

} // sinephase()


#endif
