/* centering_2 with for loop based averaging.
 *  
 *  By: Andrew Tuline
 *  
 *  Date: January 2020
 *  
 *  Centering sound samples using a for loop and integer averaging. Average is about 510.
 *  
 *  This is slow.
 *  
 */


#define MIC_PIN    5                                        // Microphone
#define NSAMPLES  32                                        // Number of samples.

void setup() {
  Serial.begin(115200);
  analogReference(EXTERNAL);                                // Comment out this line for 3.3V Arduino's.
  delay(1000);
} // setup()



void loop() {
  getSample();                                              // Sample the sounds.
} // loop()



void getSample() {

  uint16_t micIn;
  long sampleTotal = 0;                                     // Could easily use a uint16_t (0 to 65535).
  uint16_t micLev = 0;                                      // Not using signed numbers for this.
  
  for (int i = 0; i<NSAMPLES; i++) {
    micIn = analogRead(MIC_PIN);                            // Sample the microphone. Range will result in 0 to 1023.
    sampleTotal += micIn;
  }

  micLev = sampleTotal / NSAMPLES;

  Serial.print(micLev); Serial.print(" ");
  Serial.print(540); Serial.print(" ");
  Serial.print(510); Serial.print(" ");
  Serial.print(480); Serial.println(" ");

  
} // getSample()
