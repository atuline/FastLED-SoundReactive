/* agcPI
 *  
 * By: Andrew Tuline
 *  
 * Date: Jan, 2020
 *  
 * An Automatic Gain Control for a microphone on an Arduino. 
 * 
 * This version uses a PI (proportional integral) control loop.
 * 
 * See: https://en.wikipedia.org/wiki/PID_controller
 * 
 * It also includes a ghetto peak detection capability, which is displayed on led[0].
 * 
 */
 
//#define FASTLED_ALLOW_INTERRUPTS 0                          // Used for ESP8266.
#include <FastLED.h>                                          // FastLED library.

#define MIC_PIN   A5                                          // Nano or A0 on ESP8266
uint8_t squelch = 7;                                          // Anything below this is background noise, so we'll make it '0'.
int sample;                                                   // Current sample.
float sampleAvg = 0;                                          // Can be used for smoothing signals.
float micLev = 0;                                             // Used to convert returned value to have '0' as minimum.
uint8_t maxVol = 11;                                          // Reasonable value for constant volume (above average) for 'peak detector'.
bool samplePeak = 0;                                          // Boolean flag for peak detected. Responding routine must reset this flag.

uint8_t targetAgc = 60;                                       // This is our setPoint at ~20% of max for the adjusted output.
float kp = 2, ki = 4;                                         // Proportional and Integral tuning constants. Kept as floating point in case we find better tuning.
int err;                                                      // Current offset from our target.
int minn = -20000, maxx = 20000;                              // Keep everything in check with these values.
int samplePI;                                                 // Sensitivity is calculated by the PI routine.
float samplePIAvg;                                            // Calculated and stored average calculated sample is used for closed loop feedback.

// Fixed definitions cannot change on the fly.
#define LED_DT 12                                             // Data pin to connect to the strip.
#define LED_CK 11                                             // Clock pin for WS2801 or APA102.
#define COLOR_ORDER GRB                                       // It's GRB for WS2812 and BGR for APA102.
#define LED_TYPE WS2812                                       // Using APA102, WS2812, WS2801. Don't forget to modify LEDS.addLeds to suit.
#define NUM_LEDS 30                                           // Number of LED's.

uint8_t max_bright = 255;                                     // Overall brightness.
struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.



void setup() {
  Serial.begin(115200);                                       // Initialize serial port for debugging.
  delay(1000);
  analogReference(EXTERNAL);                                  // Nano or other 5V AVR8 when using a 3.3V microphone.
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2812
  FastLED.setBrightness(max_bright);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);             // FastLED Power management set at 5V, 500mA
} // setup()



void loop() {

  EVERY_N_MILLIS(10) {
    fadeToBlackBy(leds, NUM_LEDS, 4);                         // 8 bit, 1 = slow, 255 = fast
    fadeToBlackBy(leds, 1, 32);    
  }
  
  getSample();                                                // Sample the microphone.
  agcPI();                                                   // Calculated the PI adjusted value as samplePI.
  ledShow();
  FastLED.show();
 
} // loop()



void ledShow() {

  leds[(millis() % (NUM_LEDS-1)) +1 ] = CHSV(samplePI, 255, samplePI);
  if (samplePeak) {leds[0] = CHSV(0,0,128); samplePeak = 0;}    // Add a peak twinkle to the first LED.
 
} // ledShow()



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

}  // getSample()



void agcPI() {                                                // A PI Control loop to automatically adjust sound sensitivity.

  float sensitivity;                                          // Sensitivity is calculated by the PI routine.
  static float startt = 0;                                    // Accumulated (or integral) value for Ki.

  err = targetAgc - samplePIAvg;                              // Calculate the average error from the target. Is continuously going up. This should be closed loop.
  startt = constrain(startt + err, minn, maxx);               // Calculate summation (Integral) error, but constrain it.
  
  sensitivity = kp * err + ki * startt;                       // Sensitivity is the direct (Proportional) error plus the above Integral error.
  if (sensitivity <= 3000) sensitivity = 3000;                // Minimum sensitity multiplier should be 1. Andrew Tuline. I don't want divide by 0.
  samplePI = abs(sample * sensitivity / 3000);
  if(samplePI > 255) samplePI = 255;

  samplePIAvg = ((samplePIAvg * 15) + samplePI) / 16;         // Smooth it out over the last 16 samples and use as feedback for the (now closed) PI loop.

//------------ Oscilloscope output ---------------------------
//  Serial.print(sample); Serial.print(" ");
//  Serial.print(sampleAvg); Serial.print(" ");
//  Serial.print(micLev); Serial.print(" ");
//  Serial.print(err); Serial.print(" ");
//  Serial.print(startt); Serial.print(" ");
//  Serial.print(samplePI); Serial.print(" ");
//  Serial.print(samplePIAvg); Serial.print(" ");
//  Serial.print(sensitivity/3000); Serial.print(" ");
//  Serial.print(targetAgc); Serial.print(" ");
  Serial.print(0); Serial.print(" ");
  Serial.println(" ");

} // agcPI()
