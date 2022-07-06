#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define nLEDS 109
#define ledBright 255

unsigned long eventRef = 0UL;
long brightness;
const unsigned int MAX_MESSAGE_LENGTH = 12;
String aLEDswitch;
Adafruit_NeoPixel pixelStrip = Adafruit_NeoPixel(nLEDS,LED_PIN,NEO_GRBW+NEO_KHZ800);

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
    lightsOff(1000UL);
  }
  if (aLEDswitch == "green"){
    solidGreen(1000UL);
  }
  if (aLEDswitch == "red"){
    solidRed(1000UL);
  }
  if (aLEDswitch == "blue"){
    solidBlue(1000UL);
  }
  else{
    rainbow(1000UL);
  }
}
//========================================================
//Light Pattern Functions
//========================================================
//Lights Off
void lightsOff(unsigned long defltInterval){
  unsigned long prog = millis() - eventRef;
  if (prog <= defltInterval){
    for(int i=0;i<nLEDS;i++){
      pixelStrip.setPixelColor(i,0,0,0,0);
      pixelStrip.show();
    }
    Serial.println("Lights are off");
  }
  else {
    eventRef = millis();
  }
}
//========================================================
//Solid Green
void solidGreen(unsigned long defltInterval){
  unsigned long prog = millis() - eventRef;
  if (prog <= defltInterval){
    for(int i=0;i<nLEDS;i++){
      pixelStrip.setPixelColor(i,255,0,0,0);
      pixelStrip.show();
    }
    Serial.println("Lights are GREEN");
  }
  else {
    eventRef = millis();
  }
}
//========================================================
//Solid Red
void solidRed(unsigned long defltInterval){
  unsigned long prog = millis() - eventRef;
  if (prog <= defltInterval){
    for(int i=0;i<nLEDS;i++){
      pixelStrip.setPixelColor(i,0,255,0,0);
      pixelStrip.show();
    }
    Serial.println("Lights are RED");
  }
  else {
    eventRef = millis();
  }
}
//========================================================
//Solid Blue
void solidBlue(unsigned long defltInterval){
  unsigned long prog = millis() - eventRef;
  if (prog <= defltInterval){
    for(int i=0;i<nLEDS;i++){
      pixelStrip.setPixelColor(i,0,0,255,0);
      pixelStrip.show();
    }
    Serial.println("Lights are BLUE");
  }
  else {
    eventRef = millis();
  }
}
//========================================================
//Rainbow
void rainbow(unsigned long animInterval){
  unsigned long prog = millis() - eventRef;
  if (prog <= animInterval) {

    for(int i=0;i<nLEDS;i++){
      pixelStrip.setPixelColor(i,64,191,191,0);
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
