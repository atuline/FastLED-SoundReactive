# FastLED-SoundReactive

Sound Reactive displays for FastLED

By: Andrew Tuline


Here's some sound reactive demos for FastLED. Except for my original Open Music
Labs FFT demo running on a Nano, they have been tested both with an Arduino Nano
as well as an ESP8266 based WeMOS D1 Mini. Most importantly, my demos do NOT use
delay statements as delays can cause havoc with polled inputs such as triggered
buttons.

These new demos use Automatic Gain Control, so that quiet sounds still get a reaction
and continuous loud ones don't overdrive all the LED's.

* One method uses direct Proportional control against an average.
* The other uses a Proportional Integral control loop using a calculated average
  as feedback.

Note: Not all the demos have been cutover to AGC. . I'll get there.


Thanks to Ben Hencke of PixelBlaze fame for writing some PI sound code that I was
able to learn from and eventually adapt to an Arduino.



**Sound functionality**
- Continuous sampling of sounds via ADMP401 microphone.
- Auto offset centering.
- Implement squelch of background noise.
- Averaging of last 32 samples.
- Ghetto peak detection.
- Integration of sound with various display routines.
- IR control capability.
- No MSGEQ7 required for my FFT/FHT routines.
- Using Open Music Labs FHT for Arduino Nano.
- Using ArduinoFFT for ESP8266.


## My FastLED Animation Philosophy

- Do NOT use delay statements in the loop as that breaks input routines (i.e. button).
- Do not use nested loops (for performance reasons).
- Use millis() as a real time counter unless a fixed counter is required.
- Spend a bit more time using high school math (ie trigonometry), rather than just count pixels.
- Keep the display routines as short as possible.
- Data typing as strict as possible i.e. why define an int when a uint8_t is all that is required. Oh, and floats are not used at all.
- Localize variables to each routine as much as possible.
- Break out the display routines into separate .h files for increased readability and modularity.
- Be generous with comments.


## Microphones

If you go out and buy one of those cheap sound sensors from aliexpress, you will be sorely disappointed. The ADMP401 MEMS microphone includes an amplifier (with a gain of 67db), which provides a line in signal that's adequate for the Arduino works just fine. Those sound sensors don't. You have been warned.

## Files

* getSample  - Basic sound sampling with auto-centering.
* agcAvg     - Sampling with averaging AGC and CHSV output.
* agcAvg_Pal - Sampling with averaging AGC and Palette output.
* agcPI      - Sampling with Proportional Controller AGC and CHSV output.
* agcPI_Pal  - Sampling with Proportional Controller AGC and Palette output.


* sound_bracelet - More LED's with rising amplitude. Has a trailing LED. Hastily converted to use FastLED.
* sound_noise    - Perlin noise coming out from the center.
* sound_pal      - Sample at end is propagated to the other end.
* sound_ripple   - Sampled peaks generate ripples throughout.
* sound_wave     - Sample in middle is propagated out from the center.

Not done yet:

A LOT more sound reactive demos to come. Also, working on 'notasound', which is the big one.



##agcAvg and agcPI

The purpose of agcAvg and agcPI routines is to ensure the LED's are not under or over driven at any volume level.
In practice, I haven't used agcPI as the agcAvg version is simpler and seems to suffice.
So much for the 2 months I spent getting agcPI running.



## More

Information about the awesome FastLED Library is available from: [fastled.io](http://fastled.io/)

Download FastLED from: [github.com/FastLED/FastLED](https://github.com/FastLED/FastLED)

FastLED Documentation is at: [http://fastled.io/docs/3.1/modules.html](http://fastled.io/docs/3.1/modules.html)

The FastLED community is at [https://www.reddit.com/r/fastled](https://www.reddit.com/r/fastled)


-----------------------------------------------------------------------------------

My Youtube channel is at:               https://www.youtube.com/user/atuline/videos
My Github account is at:                https://github.com/atuline
My Gists are at:                        https://gist.github.com/atuline
My Pastebins are at:                    https://pastebin.com/u/atuline
FastLED support forum:					https://www.reddit.com/r/fastled
