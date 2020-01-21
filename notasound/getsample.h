#ifndef GETSAMPLE_H
#define GETSAMPLE_H

void getSample() {
  
  int16_t micIn;                                              // Current sample starts with negative values and large values, which is why it's 16 bit signed.
  static long peakTime;
  
  micIn = analogRead(MIC_PIN);                                // Poor man's analog Read.
  micLev = ((micLev * 31) + micIn) / 32;                      // Smooth it out over the last 32 samples for automatic centering. Needs to be a float.
  micIn -= micLev;                                            // Let's center it to 0 now.
  micIn = abs(micIn);                                         // And get the absolute value of each sample.
  sample = (micIn <= squelch) ? 0 : (sample + micIn)/2;       // Using a ternary operator, the resultant sample is either 0 or it's a bit smoothed out with the last sample.
  sampleAvg = ((sampleAvg * 31) + sample) / 32;               // Smooth it out over the last 32 samples.

  if (sample > (sampleAvg+maxVol) && millis() > (peakTime + 50)) {    // Poor man's beat detection by seeing if sample > Average + some value.
    samplePeak = 1;
    peakTime=millis();
  }                                                           // Then we got a peak, else we don't. Display routines need to reset the samplepeak value in case they miss the trigger.
  
}  // getSample()



void agcAvg() {                                                   // A simple averaging multiplier to automatically adjust sound sensitivity.

  multAgc = (sampleAvg < 1) ? targetAgc : targetAgc / sampleAvg;  // Make the multiplier so that sampleAvg * multiplier = setpoint
  sampleAgc = sample * multAgc;
  if (sampleAgc > 255) sampleAgc = 255;

//------------ Oscilloscope output ---------------------------
//  Serial.print(targetAgc); Serial.print(" ");
//  Serial.print(multAgc); Serial.print(" ");
//  Serial.print(sampleAgc); Serial.print(" ");

//  Serial.print(sample); Serial.print(" ");
//  Serial.print(sampleAvg); Serial.print(" ");
//  Serial.print(micLev); Serial.print(" ");
//  Serial.print(samplePeak); Serial.print(" "); samplePeak = 0;
//  Serial.print(100); Serial.print(" ");
//  Serial.print(0); Serial.print(" ");
//  Serial.println(" ");

} // agcAvg()

#endif
