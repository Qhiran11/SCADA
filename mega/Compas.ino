
// #define CMPS12_ADDRESS 0x60 // Alamat I2C CMPS12



// // Kecepatan dasar motor
// int baseSpeed = 100;
// int baseSpeedY = 60; // Sesuaikan dengan kebutuhan

// // PID Variables
// float Kp = 3.0;
// float Ki = 0.1;
// float Kd = 1.0;

// float error = 0, lastError = 0;
// float integral = 0;
// float derivative = 0;
// float pidOutput = 0;
// int targetAngle = 0; // Sudut target untuk bergerak lurus



// void maju_compas() {
//     int angleZ = bacaCMPS12(); // Baca sudut yaw dari CMPS12

//     // Hitung error dan normalisasi agar dalam rentang -180° sampai 180°
//     error = angleZ - targetAngle;
//     if (error > 180)  error -= 360;
//     if (error < -180) error += 360;

//     // Hitung PID
//     integral += error;
//     derivative = error - lastError;
//     pidOutput = (Kp * error) + (Ki * integral) + (Kd * derivative);
//     lastError = error;

//     // Sesuaikan kecepatan motor berdasarkan PID
//     int speedY = baseSpeed - pidOutput; // Motor kanan
//     int speedX = baseSpeed + pidOutput; // Motor kiri

//     // Pastikan nilai PWM dalam rentang 0 - 255
//     speedX = constrain(speedX, 0, 120);
//     speedY = constrain(speedY, 0, 120);

//     // Set kecepatan motor
//     analogWrite(l_pwmx, speedX);
//     analogWrite(r_pwmy, speedY);

//     // Tampilkan data di Serial Monitor
//     Serial.print("AngleZ: "); Serial.print(angleZ);
//     Serial.print(" | Error: "); Serial.print(error);
//     Serial.print(" | PID Output: "); Serial.print(pidOutput);
//     Serial.print(" | SpeedX: "); Serial.print(speedX);
//     Serial.print(" | SpeedY: "); Serial.println(speedY);

//     delay(50); // Delay untuk stabilitas PID
// }

// // Fungsi untuk membaca sudut yaw dari CMPS12
// int bacaCMPS12() {
//     Wire.beginTransmission(CMPS12_ADDRESS);
//     Wire.write(2); // Register untuk yaw angle (high byte)
//     Wire.endTransmission();
//     Wire.requestFrom(CMPS12_ADDRESS, 2);

//     if (Wire.available() >= 2) {
//         int highByte = Wire.read();
//         int lowByte = Wire.read();
//         int angle = (highByte << 8) + lowByte; // Gabungkan high dan low byte
//         return angle / 10; // Konversi ke derajat (0 - 359)
//     }
//     return 0; // Jika gagal membaca, kembalikan 0
// }

// void mundur_compas() {
//     int angleZ = bacaCMPS12(); // Baca sudut yaw dari CMPS12

//     // Hitung error dan normalisasi agar dalam rentang -180° sampai 180°
//     error = angleZ - targetAngle;
//     if (error > 180)  error -= 360;
//     if (error < -180) error += 360;

//     // Hitung PID
//     integral += error;
//     derivative = error - lastError;
//     pidOutput = (Kp * error) + (Ki * integral) + (Kd * derivative);
//     lastError = error;

//     // Sesuaikan kecepatan motor berdasarkan PID
//     int speedY = baseSpeedY + pidOutput; // Motor kanan
//     int speedX = baseSpeedY - pidOutput; // Motor kiri

//     // Pastikan nilai PWM dalam rentang 0 - 255
//     speedX = constrain(speedX, 0, 120);
//     speedY = constrain(speedY, 0, 120);

//     // Set kecepatan motor
//     analogWrite(r_pwmx, speedX);
//     analogWrite(l_pwmy, speedY);

//     // Tampilkan data di Serial Monitor
//     Serial.print("AngleZ: "); Serial.print(angleZ);
//     Serial.print(" | Error: "); Serial.print(error);
//     Serial.print(" | PID Output: "); Serial.print(pidOutput);
//     Serial.print(" | SpeedX: "); Serial.print(speedX);
//     Serial.print(" | SpeedY: "); Serial.println(speedY);

//     delay(50); // Delay untuk stabilitas PID
// }


// void kanan_compas() {
//     // Baca sudut yaw dari sensor (nilai seharusnya mendekati 0)
//     int angleZ = bacaCMPS12();

//     // PID untuk menjaga orientasi dengan target sudut 0°
//     error = angleZ;  // Target = 0, sehingga error = angleZ - 0
//     if (error > 180)  error -= 360;
//     if (error < -180) error += 360;

//     integral += error;
//     derivative = error - lastError;
//     pidOutput = (Kp * error) + (Ki * integral) + (Kd * derivative);
//     lastError = error;

//     // Kecepatan dasar untuk gerak lateral (bisa disesuaikan)
//     int lateralBaseSpeedKiri = 60;
//     int lateralBaseSpeedBelakang = 60;
    
//     // Roda kiri: bergerak maju, ditambah koreksi PID
//     int leftWheelSpeed = lateralBaseSpeedBelakang + pidOutput;
//     // Roda kanan: bergerak mundur, dikurangi koreksi PID
//     int rightWheelSpeed = lateralBaseSpeedKiri - pidOutput;

//     leftWheelSpeed = constrain(leftWheelSpeed, 0, 120);
//     rightWheelSpeed = constrain(rightWheelSpeed, 0, 120);

//     // Kecepatan dasar untuk kanan belakang agar bergerak ke kanan
//     int rearWheelSpeed = 40;  // Ubah nilai ini sesuai kebutuhan

//     // Set kecepatan motor:
//     // Roda belakang maju (misalnya dikontrol oleh l_pwmx)
//     analogWrite(l_pwmz, leftWheelSpeed);
//     // Roda kiri mundur (misalnya dikontrol oleh l_pwmy sesuai pola mundur_compas)
//     analogWrite(r_pwmy, rightWheelSpeed);
//     // Roda kanan bergerak ke kanan (misalnya dikontrol oleh l_pwmz)
//     analogWrite(r_pwmx, rearWheelSpeed);

//     // Pastikan motor yang tidak terpakai dimatikan
//     analogWrite(l_pwmx, 0);
//     analogWrite(l_pwmy, 0);
//     analogWrite(r_pwmz, 0);

//     // Debug output di Serial Monitor
//     Serial.print("AngleZ: "); Serial.print(angleZ);
//     Serial.print(" | Error: "); Serial.print(error);
//     Serial.print(" | PID Output: "); Serial.print(pidOutput);
//     Serial.print(" | Left Wheel: "); Serial.print(leftWheelSpeed);
//     Serial.print(" | Right Wheel: "); Serial.print(rightWheelSpeed);
//     Serial.print(" | Rear Wheel: "); Serial.println(rearWheelSpeed);

//     delay(50); // Delay untuk stabilitas PID
// }

// void kiri_compas() {
//     // Baca sudut yaw dari sensor (nilai seharusnya mendekati 0)
//     int angleZ = bacaCMPS12();

//     // PID untuk menjaga orientasi dengan target sudut 0°
//     error = angleZ;  // Target = 0, sehingga error = angleZ - 0
//     if (error > 180)  error -= 360;
//     if (error < -180) error += 360;

//     integral += error;
//     derivative = error - lastError;
//     pidOutput = (Kp * error) + (Ki * integral) + (Kd * derivative);
//     lastError = error;

//     // Kecepatan dasar untuk gerak lateral (bisa disesuaikan)
//     int lateralBaseSpeedKiri = 70;
//     int lateralBaseSpeedBelakang = 50;
    
//     // Roda kiri: bergerak maju, ditambah koreksi PID
//     int leftWheelSpeed = lateralBaseSpeedBelakang + pidOutput;
//     // Roda kanan: bergerak mundur, dikurangi koreksi PID
//     int rightWheelSpeed = lateralBaseSpeedKiri - pidOutput;

//     leftWheelSpeed = constrain(leftWheelSpeed, 0, 120);
//     rightWheelSpeed = constrain(rightWheelSpeed, 0, 120);

//     // Kecepatan dasar untuk kanan belakang agar bergerak ke kanan
//     int rearWheelSpeed = 40;  // Ubah nilai ini sesuai kebutuhan
//     // int rearWheelSpeed = 75;  // Ubah nilai ini sesuai kebutuhan

//     // Set kecepatan motor:
//     // Roda belakang maju (misalnya dikontrol oleh l_pwmx)
//     analogWrite(r_pwmz, rightWheelSpeed);
//     // Roda kiri mundur (misalnya dikontrol oleh l_pwmy sesuai pola mundur_compas)
//     analogWrite(l_pwmx, leftWheelSpeed);
//     // Roda kanan bergerak ke kanan (misalnya dikontrol oleh l_pwmz)
//     analogWrite(l_pwmy, rearWheelSpeed); /// jangan di ubah

//     // Pastikan motor yang tidak terpakai dimatikan
//     analogWrite(r_pwmx, 0);
//     analogWrite(r_pwmy, 0);
//     analogWrite(l_pwmz, 0);

//     // Debug output di Serial Monitor
//     Serial.print("AngleZ: "); Serial.print(angleZ);
//     Serial.print(" | Error: "); Serial.print(error);
//     Serial.print(" | PID Output: "); Serial.print(pidOutput);
//     Serial.print(" | Left Wheel: "); Serial.print(leftWheelSpeed);
//     Serial.print(" | Right Wheel: "); Serial.print(rightWheelSpeed);
//     Serial.print(" | Rear Wheel: "); Serial.println(rearWheelSpeed);

//     delay(50); // Delay untuk stabilitas PID
// }



