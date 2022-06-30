//Constant Variables
#define PIN 6
//Dynamic Variables

void setup() {
  Serial.begin(19200);
  Serial.setTimeout(10);
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);
}

void loop() {
  switch (Serial.read()){
    case '1':
    digitalWrite(PIN,HIGH);
    break;
    case '0':
    digitalWrite(PIN,LOW);
    break;
  }
}
