#include <Adafruit_NeoPixel.h>

// Pins
const int data_pin = 6;
const int num_pixels = 16;

// Time to wait between "frames" of animation
const int wait = 10;      // milliseconds (ms)

// R, G, B levels for each LED
byte r[num_pixels];
byte g[num_pixels];
byte b[num_pixels];

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, data_pin, NEO_RGBW + NEO_KHZ800);

void setup() {

  // Set random seed
  randomSeed(analogRead(A0));

  // Initialize NeoPixels
  pixels.begin();
  for ( int i = 0; i < num_pixels; i++ ) {
    r[i] = 0;
    g[i] = 0;
    b[i] = 0;
    pixels.setPixelColor(i, pixels.Color(r[i], g[i], b[i]));
  }
  pixels.setBrightness(5);
  pixels.show();
}

void loop() {

  int led = -1;

  // Randomly turn on an LED...randomly
  if ( random(100) < 2 ) {
    led = random(num_pixels);
    r[led] = random(256);
    g[led] = random(256);
    b[led] = random(256);
  }

  // Slowly fade out LEDs
  for ( int i = 0; i < num_pixels; i++ ) {
    if ( r[i] > 0 ) {
      r[i]--;
    }
    if ( g[i] > 0 ) {
      g[i]--;
    }
    if ( b[i] > 0 ) {
      b[i]--;
    }
  }

  // Write values to LEDs
  for ( int i = 0; i < num_pixels; i++ ) {
    pixels.setPixelColor(i, pixels.Color(r[i], g[i], b[i]));
  }
  pixels.show();

  delay(wait);
}
