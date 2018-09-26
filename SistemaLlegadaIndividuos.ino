#define sensor 2
#define led 12

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(sensor);

  if (value == LOW) {
    digitalWrite(led, HIGH);
    Serial.println("prendido");
  } else {
    digitalWrite(led, LOW);
    Serial.println("apagado");
  }
 
  delay(1000);
}
