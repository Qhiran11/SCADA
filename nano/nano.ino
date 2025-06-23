#define proximityPin A0

int a = 12;

void setup() {
  Serial.begin(9600);
  pinMode(a, OUTPUT);
  pinMode(proximityPin, INPUT);
}

void loop() {
  int proximityValue = digitalRead(proximityPin);
  digitalWrite(a, proximityValue == 1 ? HIGH : LOW);
  if (proximityValue == 0) {
    Serial.println("Ganti");
  }
}
