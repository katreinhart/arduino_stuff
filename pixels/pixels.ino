#include <Adafruit_NeoPixel.h>

const int data_pin = 6;
const int num_pixels = 16;

Adafruit_NeoPixel ring = Adafruit_NeoPixel(16, data_pin, NEO_RGBW + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  ring.begin();
  ring.setBrightness(5);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< ring.numPixels(); i++) {
      ring.setPixelColor(i, Wheel(((i * 256 / ring.numPixels()) + j) & 255));
    }
    ring.show();
    delay(20);
  }
  
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return ring.Color(25 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return ring.Color(0, WheelPos * 3, 25 - WheelPos * 3);
  }
  WheelPos -= 170;
  return ring.Color(WheelPos * 3, 25 - WheelPos * 3, 0);
}
