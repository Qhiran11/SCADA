#include <Wire.h>
#include <MPU6050_tockn.h>


MPU6050 mpu6050(Wire);


void setup_mpu(){
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true); // Kalibrasi gyroscope
}

int loop_mpu(){
  mpu6050.update();
  angleZ_Mpu = mpu6050.getAngleZ(); // Baca nilai kemiringan (yaw)
  while (angleZ_Mpu > 180)  angleZ_Mpu -= 360;
  while (angleZ_Mpu < -180) angleZ_Mpu += 360;
  return angleZ_Mpu;

}


// Kecepatan dasar motor
int mpu_baseSpeedX = 120;
int mpu_baseSpeedY = 100; // Sesuaikan dengan kebutuhan

// PID Variables
float mpu_Kp = 3.0;
float mpu_Ki = 0.1;
float mpu_Kd = 1.0;

float mpu_error = 0, mpu_lastError = 0;
float mpu_integral = 0;
float mpu_derivative = 0;
float mpu_pidOutput = 0;

void reset_nilai_PidMpu(){
  mpu_error = 0, mpu_lastError = 0;
  mpu_integral = 0;
  mpu_derivative = 0;
  mpu_pidOutput = 0;
}

void maju_mpu() {
    // Hitung error dan normalisasi agar dalam rentang -180° sampai 180°
    int mpu = loop_mpu();
    mpu_error = mpu - 0;
    
    

    // Hitung PID
    mpu_integral += mpu_error;
    mpu_derivative = mpu_error - mpu_lastError;
    mpu_pidOutput = (mpu_Kp * mpu_error) + (mpu_Ki * mpu_integral) + (mpu_Kd * mpu_derivative);
    mpu_lastError = mpu_error;

    // Sesuaikan kecepatan motor berdasarkan PID
    int speedY = mpu_baseSpeedY + mpu_pidOutput; //Motor kanan
    int speedX = mpu_baseSpeedX - mpu_pidOutput; // Motor kiri

    // Pastikan nilai PWM dalam rentang 0 - 255
    speedX = constrain(speedX, 30, 170);
    speedY = constrain(speedY, 30, 170);

    // Set kecepatan motor
    analogWrite(l_pwmx, speedX);
    analogWrite(l_pwmy, speedY);

    analogWrite(r_pwmx, 0);
    analogWrite(r_pwmy, 0);
    analogWrite(l_pwmz, 0);
    analogWrite(r_pwmz, 0);

    // Tampilkan data di Serial Monitor
    // Serial.print("angleZ_Mpu: "); Serial.print(angleZ_Mpu);
    // Serial.print(" | Error: "); Serial.print(mpu_error);
    // Serial.print(" | PID Output: "); Serial.print(mpu_pidOutput);
    // Serial.print(" | SpeedX: "); Serial.print(speedX);
    // Serial.print(" | SpeedY: "); Serial.println(speedY);

    delay(50); // Delay untuk stabilitas PID
}

void mundur_mpu() {
    // Hitung error dan normalisasi agar dalam rentang -180° sampai 180°
    int mpu = loop_mpu();
    mpu_error = mpu - 0;
    
    

    // Hitung PID
    mpu_integral += mpu_error;
    mpu_derivative = mpu_error - mpu_lastError;
    mpu_pidOutput = (mpu_Kp * mpu_error) + (mpu_Ki * mpu_integral) + (mpu_Kd * mpu_derivative);
    mpu_lastError = mpu_error;

    // Sesuaikan kecepatan motor berdasarkan PID
    int speedY = mpu_baseSpeedY - mpu_pidOutput; //Motor kanan
    int speedX = mpu_baseSpeedX + mpu_pidOutput; // Motor kiri

    // Pastikan nilai PWM dalam rentang 0 - 255
    speedX = constrain(speedX, 30, 170);
    speedY = constrain(speedY, 30, 170);

    // Set kecepatan motor
    analogWrite(r_pwmx, speedX);
    analogWrite(r_pwmy, speedY);

    analogWrite(l_pwmx, 0);
    analogWrite(l_pwmy, 0);
    analogWrite(l_pwmz, 0);
    analogWrite(r_pwmz, 0);

    // Tampilkan data di Serial Monitor
    // Serial.print("angleZ_Mpu: "); Serial.print(angleZ_Mpu);
    // Serial.print(" | Error: "); Serial.print(mpu_error);
    // Serial.print(" | PID Output: "); Serial.print(mpu_pidOutput);
    // Serial.print(" | SpeedX: "); Serial.print(speedX);
    // Serial.print(" | SpeedY: "); Serial.println(speedY);

    delay(50); // Delay untuk stabilitas PID
}

void kanan_mpu() {
    // Hitung error dan normalisasi agar dalam rentang -180° sampai 180°
    int mpu = loop_mpu();
    mpu_error = mpu - 0;

    // Hitung PID
    mpu_integral += mpu_error;
    mpu_derivative = mpu_error - mpu_lastError;
    mpu_pidOutput = (mpu_Kp * mpu_error) + (mpu_Ki * mpu_integral) + (mpu_Kd * mpu_derivative);
    mpu_lastError = mpu_error;

    int lateralBaseSpeedKanan = 60;
    int lateralBaseSpeedBelakang = 100;
    int rearWheelSpeed = 50;  // Ubah nilai ini sesuai kebutuhan
    
    
    // Sesuaikan kecepatan motor berdasarkan PID
    int speedZ = lateralBaseSpeedBelakang - mpu_pidOutput; 
    int speedX = lateralBaseSpeedKanan + mpu_pidOutput; // Roda kanan: bergerak mundur, dikurangi koreksi PID

    // Pastikan nilai PWM dalam rentang 0 - 255
    speedX = constrain(speedX, 0, 170);
    speedZ = constrain(speedZ, 0, 170);

    // Set kecepatan motor
    analogWrite(r_pwmx, speedX); // Roda kiri mundur (misalnya dikontrol oleh l_pwmy sesuai pola mundur_compas)
    analogWrite(l_pwmy, rearWheelSpeed);// Roda kanan bergerak ke kanan (misalnya dikontrol oleh l_pwmz)
    analogWrite(r_pwmz, speedZ);

    // Pastikan motor yang tidak terpakai dimatikan
    analogWrite(l_pwmx, 0);
    analogWrite(r_pwmy, 0);
    analogWrite(l_pwmz, 0);

    // Tampilkan data di Serial Monitor
    // Serial.print("angleZ_Mpu: "); Serial.print(angleZ_Mpu);
    // Serial.print(" | Error: "); Serial.print(mpu_error);
    // Serial.print(" | PID Output: "); Serial.print(mpu_pidOutput);
    // Serial.print(" | SpeedX: "); Serial.print(speedX);
    // Serial.print(" | SpeedZ: "); Serial.println(speedZ);

    delay(50); // Delay untuk stabilitas PID
}

void kiri_mpu() {
    // Hitung error dan normalisasi agar dalam rentang -180° sampai 180°
    int mpu = loop_mpu();
    mpu_error = mpu - 0;

    // Hitung PID
    mpu_integral += mpu_error;
    mpu_derivative = mpu_error - mpu_lastError;
    mpu_pidOutput = (mpu_Kp * mpu_error) + (mpu_Ki * mpu_integral) + (mpu_Kd * mpu_derivative);
    mpu_lastError = mpu_error;

    int lateralBaseSpeedKiri = 60;
    int lateralBaseSpeedBelakang = 100;
    int rearWheelSpeed = 50;  // Ubah nilai ini sesuai kebutuhan
    
    
    // Sesuaikan kecepatan motor berdasarkan PID
    int speedZ = lateralBaseSpeedBelakang + mpu_pidOutput; 
    int speedY = lateralBaseSpeedKiri - mpu_pidOutput; // Roda kanan: bergerak mundur, dikurangi koreksi PID

    // Pastikan nilai PWM dalam rentang 0 - 255
    speedY = constrain(speedY, 0, 170);
    speedZ = constrain(speedZ, 0, 170);

    // Set kecepatan motor
    analogWrite(l_pwmx, rearWheelSpeed); // Roda kiri mundur (misalnya dikontrol oleh l_pwmy sesuai pola mundur_compas)
    analogWrite(r_pwmy, speedY);// Roda kanan bergerak ke kanan (misalnya dikontrol oleh l_pwmz)
    analogWrite(l_pwmz, speedZ);

    // Pastikan motor yang tidak terpakai dimatikan
    analogWrite(r_pwmx, 0);
    analogWrite(l_pwmy, 0);
    analogWrite(r_pwmz, 0);

    // Tampilkan data di Serial Monitor
    // Serial.print("angleZ_Mpu: "); Serial.print(angleZ_Mpu);
    // Serial.print(" | Error: "); Serial.print(mpu_error);
    // Serial.print(" | PID Output: "); Serial.print(mpu_pidOutput);
    // Serial.print(" | Speedy: "); Serial.print(speedY);
    // Serial.print(" | SpeedZ: "); Serial.println(speedZ);

    delay(50); // Delay untuk stabilitas PID
}

