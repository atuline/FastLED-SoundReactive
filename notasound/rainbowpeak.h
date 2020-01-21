#ifndef RAINBOWPEAK_H
#define RAINBOWPEAK_H

void rainbowpeak() {

// Local definitions

// Persistent local variables

// Temporary local variables
  uint8_t beatA = beatsin8(17, 0, 255);                                           // Starting hue.

  
  if (samplePeak) {                                                               // Trigger a rainbow with a peak.
    
    samplePeak = 0;                                                               // Got a peak, now reset it.
    
    uint8_t locn = random8(0,NUM_LEDS);
    fill_rainbow(leds + locn, random8(0,(NUM_LEDS-locn)), beatA, 8);
  }
  
  fadeToBlackBy(leds, NUM_LEDS, 40);                                              // Fade everything. By Andrew Tuline.

} // rainbowpeak()

#endif
