/* squelch of background noise in sampled sounds.
 *  
 *  By: Andrew Tuline
 *  
 *  Date: January 2020
 *  
 *  
 */


#define MIC_PIN    5                                        // Microphone

float micLev;


void setup() {
  Serial.begin(115200);
  analogReference(EXTERNAL);                                // Comment out this line for 3.3V Arduino's.
  delay(1000);
} // setup()



void loop() {
  getSample();                                              // Sample the sounds.
} // loop()



void getSample() {

  uint8_t squelch = 7;                                      // Let's try a squelch value of 7.
  int16_t micIn;
  static uint16_t sample;
  
  micIn = analogRead(MIC_PIN);                              // Sample the microphone. Range will result in 0 to 1023.
  micLev = ((micLev * 31) + micIn) / 32;                    // Smooth it out over the last 32 samples.
  
  micIn = micIn - micLev;
  micIn = abs(micIn);

  sample = (micIn <= squelch) ? 0 : (sample + micIn) / 2;   // Using a ternary operator to smooth out the last 2 (or 4 if you want) samples. Less glitchy this way.
  
  Serial.print(micIn); Serial.print(" ");
  Serial.print(sample); Serial.print(" ");
  Serial.println(" ");
  
} // getSample()
