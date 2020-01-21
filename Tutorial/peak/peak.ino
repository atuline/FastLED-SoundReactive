  /* Ghetto peak detection.
 *  
 * By: Andrew Tuline
 *  
 * Date: Jan, 2020
 *  
 * Horrible peak detection on an Arduino.
 * 
 */


#define MIC_PIN   5                                           // Analog port for microphone
uint8_t squelch = 7;                                          // Anything below this is background noise, so we'll make it '0'.
int sample;                                                   // Current sample.
float sampleAvg = 0;                                          // Smoothed Average.
float micLev = 0;                                             // Used to convert returned value to have '0' as minimum.
uint8_t maxVol = 11;                                          // Reasonable value for constant volume for 'peak detector', as it won't always trigger.
bool samplePeak = 0;                                          // Boolean flag for peak. Responding routine must reset this flag.


void setup() {
  delay(1000);
  Serial.begin(115200);                                       // Initialize serial port for debugging.
  analogReference(EXTERNAL);                                  // Nano or other 5V AVR8 when using a 3.3V microphone.
} // setup()



void loop() {
  getSample();                                                // Sample the microphone.
} // loop()



void getSample() {
  
  int16_t micIn;                                              // Current sample starts with negative values and large values, which is why it's 16 bit signed.
  static long peakTime;
  
  micIn = analogRead(MIC_PIN);                                // Poor man's analog Read.
  micLev = ((micLev * 31) + micIn) / 32;                      // Smooth it out over the last 32 samples for automatic centering.
  micIn -= micLev;                                            // Let's center it to 0 now.
  micIn = abs(micIn);                                         // And get the absolute value of each sample.

  sample = (micIn <= squelch) ? 0 : (sample + micIn) / 2;     // Using a ternary operator, the resultant sample is either 0 or it's a bit smoothed out with the last sample.

  sampleAvg = ((sampleAvg * 31) + sample) / 32;               // Smooth it out over the last 32 samples.

  if (sample > (sampleAvg+maxVol) && millis() > (peakTime + 50)) {    // Poor man's beat detection by seeing if sample > Average + some value.
    samplePeak = 1;                                                   // Then we got a peak, else we don't. Display routines need to reset the samplepeak value in case they miss the trigger.
    peakTime=millis();                
  }                                                           

  Serial.print(sample); Serial.print(" ");
  Serial.print(sampleAvg); Serial.print(" ");
  Serial.print(samplePeak*60); Serial.print(" ");
  Serial.print(0); Serial.print(" ");
  Serial.print(60); Serial.print(" ");
  Serial.println(" ");
  

  samplePeak = 0;

}  // getSample()
