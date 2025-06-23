void baca_serial(){
  if (Serial.available() >= 4) {  // 2 byte untuk X, 2 byte untuk Y
        sumbuX = (Serial.read() << 8) | Serial.read();  // Gabungkan 2 byte menjadi int16_t
        sumbuY = (Serial.read() << 8) | Serial.read();
    }
}

int roda_x;
int roda_y;
bool cs = false;
void maju_custom(){
    if (Serial.available() >= 4) {  // 2 byte untuk X, 2 byte untuk Y
      roda_y = (Serial.read() << 8) | Serial.read();  // Gabungkan 2 byte menjadi int16_t
      roda_x = (Serial.read() << 8) | Serial.read();   
    }
    analogWrite(l_pwmx, roda_x); /// roda kanan maju
    analogWrite(l_pwmy, roda_y); /// roda kiri maju
    if (cs == false){
      analogWrite(l_pwmz, 0);
      analogWrite(r_pwmz, 0);
      
      analogWrite(r_pwmx, 0);
      analogWrite(r_pwmy, 0);
    
      digitalWrite(r_enz, LOW);
      digitalWrite(l_enz, LOW);
      cs = true;
    }
    
    
}
