/* centering_4 using multi-sample smoothing using a 'long' and a 'float' as the average.
 *  
 *  By: Andrew Tuline
 *  
 *  Date: January 2020
 *  
 *  Centering sound samples using smoothing.
 *  
 */


#define MIC_PIN    5                                        // Microphone
#define NSAMPLES  32                                        // Number of samples.

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

  uint16_t  micIn;
  
  micIn = analogRead(MIC_PIN);                              // Sample the microphone. Range will result in 0 to 1023.
  micLev = ((micLev * 31) + micIn) / 32;                    // Smooth it out over the last 32 samples.
  
  Serial.print(540); Serial.print(" ");                     // Fake out the 'auto' re-sizing for the serial plotter in the Arduino IDE.
  Serial.print(510); Serial.print(" ");
  Serial.print(480); Serial.print(" ");
  Serial.println(micLev); Serial.print(" ");
  
} // getSample()
