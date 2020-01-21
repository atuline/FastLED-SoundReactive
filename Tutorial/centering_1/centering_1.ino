/* Sound sampling - Pre-defined centering.
 *  
 *  By: Andrew Tuline
 *  
 *  Date: Jan 2020
 *  
 *  Basic code to read from the Sparkfun INMP401 microphone at 5V on Arduino Nano and UNO and center it.
 *  
 */

#define MIC_PIN    5                                        // Microphone, or A0 on a WeMOS D1 Mini.
#define DC_OFFSET  510                                      // DC offset in mic signal. I subtract this value from the raw sample.


void setup() {
  Serial.begin(115200);
  analogReference(EXTERNAL);                                // Comment out this line for 3.3V Arduino's, or 5V microphones.
  delay(1000);
} // setup()



void loop() {
  getSample();                                              // Sample the sounds.
} // loop()



void getSample() {

  uint16_t micIn;                                           // Current sample was 0-1023.
  int16_t micLev;                                           // Here, we subtract the offset, so this should be 16 bit signed.

  micIn = analogRead(MIC_PIN);                              // Sample the microphone.
  micLev = micIn - DC_OFFSET;                               // Signed value centering around 0.
  
  Serial.print(micLev); Serial.print(" ");
  Serial.print(20); Serial.print(" ");                      // Fake out the 'auto' re-sizing for the serial plotter in the Arduino IDE.
  Serial.print(-20); Serial.println(" ");

} // getSample()
