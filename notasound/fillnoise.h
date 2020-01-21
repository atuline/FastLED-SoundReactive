#ifndef FILLNOISE_H
#define FILLNOISE_H

void fillnoise() {                                                             // Another perlin noise based routine.

// Local definitions
  #define xscale 160
  #define yscale 160

// Persistent local variables
  static int16_t xdist;                                                         // A random number for our noise generator.
  static int16_t ydist;

// Temporary local variables



  if (sampleAvg > NUM_LEDS) sampleAvg = NUM_LEDS;                               // Clip the sampleAvg to maximize at NUM_LEDS.
  
  for (int i= (NUM_LEDS-sampleAvg/2)/2; i<(NUM_LEDS+sampleAvg/2)/2; i++) {      // The louder the sound, the wider the soundbar.
    uint8_t index = inoise8(i*sampleAvg+xdist, ydist+i*sampleAvg);              // Get a value from the noise function. I'm using both x and y axis.

    leds[i] = ColorFromPalette(currentPalette, index, sampleAgc, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }                                                                             // Effect is a NOISE bar the width of sampleAvg. Very fun. By Andrew Tuline.

  xdist += beatsin8(5,0,3);                                                     // Moving forward in the NOISE field, but with a sine motion.
  ydist += beatsin8(4,0,3);                                                     // Moving sideways in the NOISE field, but with a sine motion.

  waveit();                                                                     // Move the pixels to the left/right, but not too fast.
  
  fadeToBlackBy(leds+NUM_LEDS/2-1, 2, 64);                                     // Fade the center, while waveit moves everything out to the edges.
                                                                              
} // fillnoise()

#endif
