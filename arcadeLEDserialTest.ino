#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define nLEDS 109
#define ledBright 255

Adafruit_NeoPixel pixelStrip = Adafruit_NeoPixel(nLEDS,LED_PIN,NEO_RGBW+NEO_KHZ800);
unsigned long eventRef = 0UL;
long brightness;
const unsigned int MAX_MESSAGE_LENGTH = 12;
String aLEDswitch;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  aLEDswitch = "rainbow";
  pixelStrip.setBrightness(ledBright);
  pixelStrip.begin();
  pixelStrip.show();
}

void loop() {
  //Reads in strings send to the Arduino over the serial.
  arcadeSerialBuffer();
  //Switches LED color patterns based on string received from arcadeSerialBuffer()
  if (aLEDswitch == "off"){
    solidColors(1000UL,0,0,0);
  }
  else if (aLEDswitch == "green"){
    solidColors(10000UL,255,0,0);
  }
  else if (aLEDswitch == "red"){
    solidColors(10000UL,0,255,0);
  }
  else if (aLEDswitch == "blue"){
    solidColors(10000UL,0,0,255);
  }
  else{
    rainbow(1000UL);
  }
}
//========================================================
//Light Pattern Functions
//========================================================
//Solid Colors
void solidColors(unsigned long solidInterval,int g,int r,int b){
  unsigned long prog=millis()-eventRef;
  if (prog<=solidInterval){
    for(int i=0;i<nLEDS;i++){
      pixelStrip.setPixelColor(i,pixelStrip.Color(g,r,b));
      pixelStrip.show();
    }
    //GRB Colors Serial Debug
    char grbDebug[4]="(,)";
    Serial.print(grbDebug[0]);
    Serial.print(g);
    Serial.print(grbDebug[1]);
    Serial.print(r);
    Serial.print(grbDebug[1]);
    Serial.print(b);
    Serial.println(grbDebug[2]);
  }
  else {
    eventRef=millis();
  }
}
//========================================================
//Rainbow
void rainbow(unsigned long animInterval){
  unsigned long prog = millis() - eventRef;
  if (prog <= animInterval) {

    for(int i=0;i<nLEDS;i++){
      pixelStrip.setPixelColor(i,pixelStrip.Color(0,128,128));
      pixelStrip.show();
    }
    Serial.println("Lights are RAINBOW");
    /*
    uint16_t i, j;
    for(j=0; j<256*cycles; j++) {
      for(i=0; i<nLEDS; i++) {
        pixelStrip.setPixelColor(i, rainbowWheel((i+j) & 255));
      }
      pixelStrip.show();
    }
    */
  }
  else {
    eventRef = millis();
  }
}
/*
//========================================================
//Color Picker
//========================================================
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
*/
//========================================================
//Arcade String Serial Buffer
//========================================================
void arcadeSerialBuffer(){
  //Check for data in the serial receive buffer
  while (Serial.available() > 0){
    //Create an array to hold incoming message and sets the byte position in the serial buffer
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;
    //Read next byte in the serial recieve buffer
    char inByte = Serial.read();
    //Check if incoming message is not a terminating character
    if(inByte != '\n' && (message_pos <= MAX_MESSAGE_LENGTH - 1)){
      //Add the incoming byte to our message
      message[message_pos] = inByte;
      message_pos++;
    }
    //Full message received
    else{
      //Add null character to message addess message to useable string
      message[message_pos] = '\0';
      aLEDswitch = message;
      //Reset for the next message
      Serial.end();
      Serial.begin(9600);
      message_pos = 0;
    }
  }
}
