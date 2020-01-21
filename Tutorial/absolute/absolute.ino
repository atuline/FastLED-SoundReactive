/* take the absolute value of the centered data.
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

  int16_t micIn;
  
  micIn = analogRead(MIC_PIN);                              // Sample the microphone. Range will result in 0 to 1023.
  micLev = ((micLev * 31) + micIn) / 32;                    // Smooth it out over the last 32 samples.
  
  micIn = micIn - micLev;
  micIn = abs(micIn);

 
  Serial.print(micIn); Serial.print(" ");
  Serial.print(0); Serial.print(" ");
  Serial.print(100); Serial.print(" ");
  Serial.println(" ");
  
} // getSample()
