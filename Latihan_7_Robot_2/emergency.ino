void emergency(){
  unsigned long currentMillis = millis();
  digitalWrite(Relay_pin1, LOW);
  digitalWrite(Relay_pin2, HIGH);
  digitalWrite(Relay_pin3, HIGH);
  stop();
  if (currentMillis - delayStart >= 5000){
    digitalWrite(Relay_pin1, HIGH);
    digitalWrite(Relay_pin2, HIGH);
    digitalWrite(Relay_pin3, HIGH);
    ActivatedSystem = false;
    stop();
    Serial.println("Fuck");
    c = 100;
  }
}



