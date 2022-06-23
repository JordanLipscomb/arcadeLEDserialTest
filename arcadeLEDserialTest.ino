//Constant Variables
#define PIN 6

void setup() {
  Serial.begin(19200);
  Serial.setTimeout(500);
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);

}

void loop() {
  if (Serial.available() > 0){
    String str = Serial.readString();
    Serial.println(str);
    
    if (str == "LEDon"){
      digitalWrite(PIN, HIGH);
    }

    if (str == "LEDoff"){
      digitalWrite(PIN, LOW);
    }
    
  }
}
