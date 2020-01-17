/* sound_sample
 *  
 * By: Andrew Tuline
 *
 * Date: January, 2020
 *
 * Basic code to read and print values from a microphone. Includes an auto-leveller to handle any DC offsets.
 * 
 * If your microphone uses 3.3 with a 5V Arduino, then please read up on analogReference(EXTERNAL) in the setup().
 * 
 * You will, however, need to play around with the squelch value in order to remove background noise.
 * 
 * Note: Be very careful when defining the data type. I had defined micLev and sampleAvg as 'int' as the data was 
 * within that range, however small errors crept up as a result of the iterative multiplications to the point that 
 * it was causing significant issues at low sound levels. I eventually had to use floating point.
 *
 * Moral of the story: KNOW YOUR DATA!
 * 
 */

//#define FASTLED_ALLOW_INTERRUPTS 0                          // Used for ESP8266.
#include <FastLED.h>                                          // FastLED library.

#define MIC_PIN   5                                           // Analog port for microphone
uint8_t squelch = 7;                                          // Anything below this is background noise, so we'll make it '0'.
int sample;                                                   // Current sample.
float sampleAvg = 0;                                          // Smoothed Average.
float micLev = 0;                                             // Used to convert returned value to have '0' as minimum.
uint8_t maxVol = 11;                                          // Reasonable value for constant volume for 'peak detector', as it won't always trigger.
bool samplePeak = 0;                                          // Boolean flag for peak.


void setup() {
  
  analogReference(EXTERNAL);
  Serial.begin(115200);                                       // Initialize serial port for debugging.
  
} // setup()



void loop() {
  
    getSample();
    
} // loop()



void getSample() {
  
  int16_t micIn;                                              // Current sample starts with negative values and large values, which is why it's 16 bit signed.
  static long peakTime;
  
  micIn = analogRead(MIC_PIN);                                // Poor man's analog Read.
  micLev = ((micLev * 31) + micIn) / 32;                      // Smooth it out over the last 32 samples for automatic centering.

  micIn -= micLev;                                            // Let's center it to 0 now.
  micIn = abs(micIn);                                         // And get the absolute value of each sample.
  sample = (micIn <= squelch) ? 0 : (sample + micIn)/2;       // Using a ternary operator, the resultant sample is either 0 or it's a bit smoothed out with the last sample.
  sampleAvg = ((sampleAvg * 31) + sample) / 32;               // Smooth it out over the last 32 samples.

  if (sample > (sampleAvg+maxVol) && millis() > (peakTime + 50)) {    // Poor man's beat detection by seeing if sample > Average + some value.
    samplePeak = 1;
    peakTime=millis();
  }                                                           // Then we got a peak, else we don't. Display routines need to reset the samplepeak value in case they miss the trigger.

//------------ Oscilloscope output ---------------------------
//  Serial.print(micLev); Serial.print(" ");
  Serial.print(sample); Serial.print(" ");
//  Serial.print(micLev); Serial.print(" ");
//  Serial.print(sampleAvg); Serial.print(" ");
//  Serial.print(samplePeak); Serial.print(" "); samplePeak = 0;
//  Serial.print(0); Serial.print(" ");
//  Serial.print(255); Serial.print(" ");
  Serial.println(" ");

}  // getSample()
