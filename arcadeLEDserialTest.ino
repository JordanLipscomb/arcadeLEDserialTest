#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define nLEDS 109
#define ledBright 255

unsigned long eventRef = 0UL;
long brightness;
int aLEDswitch = 0;
Adafruit_NeoPixel pixelStrip = Adafruit_NeoPixel(nLEDS, LED_PIN, NEO_RGBW + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pixelStrip.setBrightness(ledBright);
  pixelStrip.begin();
  pixelStrip.show();
}

void loop() {
  if (Serial.available() > 0){
    aLEDswitch = Serial.read();
  }
  if (aLEDswitch == '1'){
    for(int i=0;i<nLEDS;i++){
      pixelStrip.setPixelColor(i,100,0,0);
      pixelStrip.show();
    }
    //rainbow(30000UL,25);
  }
  else {
    lightsOff(10000UL);
  }
}

void lightsOff(unsigned long defltInterval){
  unsigned long prog = millis() - eventRef;
  if (prog <= defltInterval){
    for(int i=0;i<nLEDS;i++){
      pixelStrip.setPixelColor(i,0,0,0);
      pixelStrip.show();
    }
  }
  else {
    aLEDswitch = '1';
  }
}

void rainbow(unsigned long animInterval, uint8_t cycles){
  unsigned long prog = millis() - eventRef;
  if (prog <= animInterval) {
    
    uint16_t i, j;
    for(j=0; j<256*cycles; j++) {
      for(i=0; i<nLEDS; i++) {
        pixelStrip.setPixelColor(i, rainbowWheel((i+j) & 255));
      }
      pixelStrip.show();
    }
    
  }
  else {
    eventRef = millis();
  }
}

//Color Pickers
//--------------------
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t rainbowWheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixelStrip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixelStrip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixelStrip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  
}
uint8_t red(uint32_t c) {
  return (c >> 16);
}
uint8_t green(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}
