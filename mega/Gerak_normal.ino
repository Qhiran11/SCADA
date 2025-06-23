void setup_motor() {
    // Set pin motor sebagai output
    pinMode(r_eny, OUTPUT);
    pinMode(l_eny, OUTPUT);
    pinMode(r_pwmy, OUTPUT);
    pinMode(l_pwmy, OUTPUT);
    
    pinMode(r_enx, OUTPUT);
    pinMode(l_enx, OUTPUT);
    pinMode(r_pwmx, OUTPUT);
    pinMode(l_pwmx, OUTPUT);


    pinMode(r_enz, OUTPUT);
    pinMode(l_enz, OUTPUT);
    pinMode(r_pwmz, OUTPUT);
    pinMode(l_pwmz, OUTPUT);
    stop();
    motor_HIGH();

}
void motor_HIGH(){
    digitalWrite(r_eny, HIGH);
    digitalWrite(l_eny, HIGH);
    digitalWrite(r_enx, HIGH);
    digitalWrite(l_enx, HIGH);
    digitalWrite(r_enz, HIGH);
    digitalWrite(l_enz, HIGH);
}


void stop (){
  reset_nilai_PidMpu();
  analogWrite(r_pwmx, 0);
  analogWrite(l_pwmx, 0);
  analogWrite(r_pwmy, 0);
  analogWrite(l_pwmy, 0);
  analogWrite(r_pwmz, 0);
  analogWrite(l_pwmz, 0);

}


void putar_kiri(){
    
    analogWrite(l_pwmx, 30);
    analogWrite(r_pwmy, 30);

    analogWrite(l_pwmy, 0);
    analogWrite(r_pwmx, 0);

    analogWrite(l_pwmz, 0);
    analogWrite(r_pwmz, 30);
}

void putar_kanan(){
    analogWrite(l_pwmy, 30);
    analogWrite(r_pwmx, 30);

    analogWrite(r_pwmy, 0);
    analogWrite(l_pwmx, 0);
    

    analogWrite(r_pwmz, 0);
    analogWrite(l_pwmz, 30);
}


void _maju(){
    analogWrite(l_pwmx, 120);
    analogWrite(l_pwmy, 100);
    analogWrite(r_pwmx, 0);
    analogWrite(r_pwmy, 0);
    analogWrite(l_pwmz, 0);
    analogWrite(r_pwmz, 0);
}

void _mundur(){
    analogWrite(l_pwmx, 0);
    analogWrite(l_pwmy, 0);
    analogWrite(r_pwmx, 120);
    analogWrite(r_pwmy, 100);
    analogWrite(l_pwmz, 0);
    analogWrite(r_pwmz, 0);
}

void _kiri(){
    analogWrite(l_pwmx, 60); // kanan maju
    analogWrite(l_pwmy, 0); // kiri mundur
    analogWrite(r_pwmx, 0);
    analogWrite(r_pwmy, 50);
    analogWrite(l_pwmz, 100);
    analogWrite(r_pwmz, 0);
}

void _kanan(){
    analogWrite(l_pwmx, 0);
    analogWrite(l_pwmy, 50); // kiri maju
    analogWrite(r_pwmx, 60); // kanan mundur
    analogWrite(r_pwmy, 0);
    analogWrite(l_pwmz, 0);
    analogWrite(r_pwmz, 100); // belakang kanan
}



void _kiri2(){
    analogWrite(l_pwmx, 40); // kanan maju
    analogWrite(l_pwmy, 0); // kiri mundur
    analogWrite(r_pwmx, 0);
    analogWrite(r_pwmy, 30);
    analogWrite(l_pwmz, 70);
    analogWrite(r_pwmz, 0);
}

void _kanan2(){
    analogWrite(l_pwmx, 0);
    analogWrite(l_pwmy, 30); // kiri mundur
    analogWrite(r_pwmx, 40); // kanan maju
    analogWrite(r_pwmy, 0);
    analogWrite(l_pwmz, 0);
    analogWrite(r_pwmz, 70); // belakang kanan
}


void kiri_bola(){
    analogWrite(l_pwmx, 40); // kanan maju
    analogWrite(l_pwmy, 0); // kiri mundur
    analogWrite(r_pwmx, 0);
    analogWrite(r_pwmy, 50);
    analogWrite(l_pwmz, 70);
    analogWrite(r_pwmz, 0);
}

void kanan_bola(){
    analogWrite(l_pwmx, 0);
    analogWrite(l_pwmy, 40); // kiri maju
    analogWrite(r_pwmx, 60); // kanan mundur
    analogWrite(r_pwmy, 0);
    analogWrite(l_pwmz, 0);
    analogWrite(r_pwmz, 70); // belakang kanan
}


void maju_custom(int roda_x, int roda_y){
    analogWrite(l_pwmx, roda_x); /// roda kanan maju
    analogWrite(r_pwmy, roda_y); /// roda kiri maju
    
    
    analogWrite(r_pwmx, 0);
    analogWrite(l_pwmy, 0);
    
    analogWrite(l_pwmz, 0);
    analogWrite(r_pwmz, 0);
}


