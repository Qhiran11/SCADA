// mpu_sender.ino
// Tugas program ini HANYA membaca MPU6050 dan mengirim data ke Laptop.


#include <Wire.h>
#include <MPU6050_tockn.h>
MPU6050 mpu6050(Wire);


void setup() {
  Serial.begin(115200);
  // setup_Ultra();
  // set_push();
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true); 
}


// Variabel untuk menampung data mentah dari sensor
int angleX;
int angleY; 
int angleZ;

void loop() {
  mpu6050.update();
  // Baca data akselerasi dan giroskop mentah
  angleX = mpu6050.getAngleX();
  angleY = mpu6050.getAngleY();
  angleZ = mpu6050.getAngleZ();

  // Kirim HANYA data giroskop Z (gz) ke laptop.
  // println secara otomatis menambahkan karakter newline ('\n') di akhir.
  Serial.println(angleZ);
  
  // Beri jeda agar tidak membanjiri port serial
  delay(50); // Kirim data sekitar 10 kali per detik
}
