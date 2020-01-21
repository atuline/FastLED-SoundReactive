/* centering_3 using a FIFO buffer.
 *  
 *  By: Andrew Tuline
 *  
 *  Date: January 2020
 *  
 *  Centering sound samples using a FIFO buffer for calculating the average, which is about 510.
 *  
 */


#define MIC_PIN    5                                        // Microphone
#define NSAMPLES  64                                        // Number of samples.

void setup() {
  Serial.begin(115200);
  analogReference(EXTERNAL);                                // Comment out this line for 3.3V Arduino's.
  delay(1000);
} // setup()



void loop() {
  getSample();                                              // Sample the sounds.
} // loop()



void getSample() {
  
  uint16_t micIn = 0;                                       // Current sample, not signed since we're not subtracting the DC Offset.
  long sampleTotal = 0;
  uint16_t sampleAvg = 0;

  static int16_t sampleArray[NSAMPLES];                     // Array of samples.
  static uint16_t sampleSum = 0;                            // Sum of the last 64 samples.
  static uint8_t sampleCount = 0;                           // A rollover counter to cycle through the array.

  micIn = analogRead(MIC_PIN);                              // Sample the microphone.
  sampleSum += micIn - sampleArray[sampleCount];            // Add the new sample and remove the oldest sample in the array.
  sampleAvg = sampleSum / NSAMPLES;                         // Get an average.
  sampleArray[sampleCount] = micIn;                         // Update oldest sample in the array with new sample.
  sampleCount++;                                            // Update the counter for the array and rollover if we hit the max.
  sampleCount = sampleCount % NSAMPLES;

  Serial.print(540); Serial.print(" ");                     // Fake out the 'auto' re-sizing for the serial plotter in the Arduino IDE.
  Serial.print(510); Serial.print(" ");
  Serial.print(480); Serial.print(" ");
  Serial.println(sampleAvg); Serial.print(" ");
  
} // getSample()
