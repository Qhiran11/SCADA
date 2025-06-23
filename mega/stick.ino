String usbX;
String usbY;

int x;
int y;

void stick_usb(){
    int proximityValue = digitalRead(proximityPin);
    baca_serial();
    x = sumbuX;
    y = sumbuY;
            if (x == 0 && y == 0) {
                stop();
            } else if (x == 0 && y == 1) {
                // Serial.println("⬇️ Mundur");
                analogWrite(l_pwmx, 0);
                analogWrite(l_pwmy, 0);
                analogWrite(r_pwmx, 120);
                analogWrite(r_pwmy, 100);
                analogWrite(l_pwmz, 0);
                analogWrite(r_pwmz, 0);
                
            } else if (x == 0 && y == 2) {
                // Serial.println("⬆️ Maju");
                analogWrite(l_pwmx, 120);
                analogWrite(l_pwmy, 100);
                analogWrite(r_pwmx, 0);
                analogWrite(r_pwmy, 0);
                analogWrite(l_pwmz, 0);
                analogWrite(r_pwmz, 0);
                // mundur_compas();
            }
            else if (x == 1 && y == 0 && proximityValue == 0) {
                // Serial.println("➡️ Kanan");
                kanan_bola();
                // kanan_compas();
                
            } else if (x == 2 && y == 0 && proximityValue == 0) {
                // Serial.println("⬅️ Kiri");
                kiri_bola();
                // kiri_compas();
                
            }

             else if (x == 1 && y == 0) {
                // Serial.println("➡️ Kanan");
                _kanan();
                // kanan_compas();
                
            } else if (x == 2 && y == 0) {
                // Serial.println("⬅️ Kiri");
                _kiri();
                // kiri_compas();
                
            }else if (x == 5 && y == 1) {
                // Serial.println("➡️ putar Kanan");
                analogWrite(l_pwmx, 0);
                analogWrite(l_pwmy, 60); //roda kiri maju
                analogWrite(r_pwmx, 60); // roda kanan mundur
                analogWrite(r_pwmy, 0);
                analogWrite(l_pwmz, 60);
                analogWrite(r_pwmz, 0); // roda belakang kanan
                // kanan_compas();
            }else if (x == 4 && y == 1) {
                // Serial.println("⬅️ putar Kiri");
                analogWrite(l_pwmx, 60);
                analogWrite(l_pwmy, 0);
                analogWrite(r_pwmx, 0);
                analogWrite(r_pwmy, 60);
                analogWrite(l_pwmz, 0);
                analogWrite(r_pwmz, 60);
                // kiri_compas();
                
            }

            
            // if (x == 1 && y == 1){
            //   digitalWrite(Relay_pin3, LOW);
            // }
            // else if (x == 3 && y == 3){
            //   digitalWrite(Relay_pin3, HIGH);
            // }

          



    // if (proximityValue == 1 || (x == 3 && y == 3)) {
    //   digitalWrite(Relay_pin3, HIGH);
    // }

    // else if (proximityValue == 0 || (x == 1 && y == 1)) {
    //   Serial.println("Proximity value: 0");
    //   digitalWrite(Relay_pin3, LOW);
    // }
}