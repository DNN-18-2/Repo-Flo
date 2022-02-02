#include "FastLED.h"

#define NUM_LEDS 12
#define PIN 7

byte bright = 10;
byte rate = 0;
byte w = 1;
byte baza = 0;

boolean button1WasUp = true;
boolean button2WasUp = true;
boolean button3WasUp = true;

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(7, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

  FastLED.addLeds <WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(bright);
}

void knopka () {
  boolean button1IsUp = digitalRead(8);
  boolean button2IsUp = digitalRead(10);
  boolean button3IsUp = digitalRead(12);

  if (button1WasUp && !button1IsUp) {
    delay(10);
    button1IsUp = digitalRead(8);
    if (!button1IsUp) { bright = bright + 50; if (bright > 250) { bright = 1; }
    }
  }
  button1WasUp = button1IsUp;

  if (button2WasUp && !button2IsUp) {
    delay(10);
    button2IsUp = digitalRead(10);
    if (!button2IsUp) { rate = rate + 10; if (rate > 50) { rate = 0; }
    }
  }
  button2WasUp = button2IsUp;

  if (button3WasUp && !button3IsUp) {
    delay(10);
    button3IsUp = digitalRead(12);
    if (!button3IsUp) { w++; if (w > 7) { w = 1; }
    }
  }
  button3WasUp = button3IsUp;
}

void loop() {

  while (w == 1) {
    knopka(); 
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(255, 7, 10);
    }
    baza++;
    FastLED.setBrightness(bright);
    FastLED.show();
    delay(50 - rate);
  }

  while (w == 2) {
    knopka();
    static uint8_t starthue = 0;
    fill_rainbow( leds + 5, NUM_LEDS - 5, --starthue, rate);
    uint8_t secs = (millis() / 1000) % (rate * 2);
    if (secs < rate) { FastLED.setTemperature( Tungsten100W ); leds[0] = Tungsten100W; }
    else { FastLED.setTemperature( OvercastSky ); leds[0] = OvercastSky; }
    FastLED.setBrightness(bright);
    FastLED.show();
  }

  while (w == 3) {
    knopka();
    fadeToBlackBy(leds, NUM_LEDS, (rate + 1) * 2);
    int pos = random16(NUM_LEDS);
    leds[pos] += CHSV(255, 7, 0);
    FastLED.setBrightness(bright);
    FastLED.show();
  }

  while (w == 4) {
    knopka();
    fadeToBlackBy(leds, NUM_LEDS, (rate + 1) * 2);
    int pos = beatsin16(13, 0, NUM_LEDS - 1);
    leds[pos] += CHSV(255, 7, 0);
    FastLED.setBrightness(bright);
    FastLED.show();
  }

  while (w == 5) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].nscale8(250);
      }
    for (int i = 0; i < NUM_LEDS; i++) {
      knopka();
      leds[i] = CHSV(255, 7, 10);
      FastLED.setBrightness(bright);
      FastLED.show();
      delay(rate);
    }
  }

  while (w == 6) {
    knopka();
    fadeToBlackBy(leds, NUM_LEDS, (rate + 1) * 2);
    for (int i = 0; i < 8; i++) {
      leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(255, 7, 0);
    }
    FastLED.setBrightness(bright);
    FastLED.show();
    delay(10);
  }

  while (w == 7) {
    knopka();
    fill_rainbow( leds, NUM_LEDS, baza++, 7);
    if (random8() < 80) { leds[ random16(NUM_LEDS) ] += CRGB::White; }
    FastLED.setBrightness(bright);
    FastLED.show();
    delay(50 - rate);
  }
}
