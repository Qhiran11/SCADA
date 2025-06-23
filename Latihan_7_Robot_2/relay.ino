void setup_pin_relay() {
  
  pinMode(Relay_pin1, OUTPUT);
  pinMode(Relay_pin2, OUTPUT);
  pinMode(Relay_pin3, OUTPUT);
  pinMode(Relay_pin4, OUTPUT);
 
  digitalWrite(Relay_pin1, HIGH);
  digitalWrite(Relay_pin2, HIGH);
  digitalWrite(Relay_pin3, HIGH);
  digitalWrite(Relay_pin4, HIGH); 
}



void berhenti_isi(){
  digitalWrite(Relay_pin1, HIGH);
  digitalWrite(Relay_pin2, HIGH);
  digitalWrite(Relay_pin3, HIGH);
}

void isi_keras(){
  digitalWrite(Relay_pin1, HIGH);
  digitalWrite(Relay_pin2, HIGH);
  digitalWrite(Relay_pin3, LOW);
}

void isi_pelan(){
  digitalWrite(Relay_pin1, HIGH);
  digitalWrite(Relay_pin2, LOW);
  digitalWrite(Relay_pin3, HIGH);
}

void tendang(){
  digitalWrite(Relay_pin1, LOW);
  digitalWrite(Relay_pin2, HIGH);
  digitalWrite(Relay_pin3, HIGH);
}
