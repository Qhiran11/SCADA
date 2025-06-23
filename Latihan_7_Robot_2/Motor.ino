// // Faktor koreksi kecepatan
// int KamerabaseSpeed = 50; // Sesuaikan dengan kecepatan awal

// // Variabel PID
// float KameraKp = 5.0;   // Gain Proportional
// float KameraKi = 0.1;   // Gain Integral
// float KameraKd = 1.0;   // Gain Derivative

// float Kameraerror = 0, KameralastError = 0;
// float Kameraintegral = 0;
// float Kameraderivative = 0;
// float KamerapidOutput = 0;

// void maju_kamera() {
//     if (Serial.available() >= 4) {  // 2 byte untuk X, 2 byte untuk Y
//         sumbuX = (Serial.read() << 8) | Serial.read();  // Gabungkan 2 byte menjadi int16_t
//         sumbuY = (Serial.read() << 8) | Serial.read();
//     }
    
//     int targetX = 400; // Posisi tengah layar
//     int errorX = sumbuX - targetX; // Hitung error berdasarkan posisi bola

//     // Hitung PID
//     Kameraintegral += errorX;
//     Kameraderivative = errorX - KameralastError;
//     KamerapidOutput = (KameraKp * errorX) + (KameraKi * Kameraintegral) + (KameraKd * Kameraderivative);
//     KameralastError = errorX;

//     // Sesuaikan kecepatan motor berdasarkan PID
//     int speedX = KamerabaseSpeed - KamerapidOutput; // Motor kanan
//     int speedY = KamerabaseSpeed + KamerapidOutput; // Motor kiri

//     // Pastikan nilai PWM dalam rentang 0 - 255
//     speedX = constrain(speedX, 0, 100);
//     speedY = constrain(speedY, 0, 100);

//     // Set kecepatan motor
//     analogWrite(r_pwmx, speedX);
//     analogWrite(l_pwmy, speedY);

//     // Tampilkan data di Serial Monitor

//     delay(50); // Delay untuk stabilitas PID
// }
