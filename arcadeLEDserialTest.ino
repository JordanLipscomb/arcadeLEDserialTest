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
    
    if (str == "O"){
      digitalWrite(PIN, HIGH);
    }

    if (str == "I"){
      digitalWrite(PIN, LOW);
    }
  }
}
