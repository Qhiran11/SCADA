// #include <Wire.h>
// #include <MPU6050_tockn.h>
// MPU6050 mpu6050(Wire);

// // combined_sender.ino
// // Mengirim beberapa nilai sensor dalam satu baris data (format CSV).

// // Variabel sensor (seperti pada contoh Anda)
// // Nilai-nilai ini nantinya akan datang dari pembacaan sensor Anda yang sebenarnya.
// long Encoder1 = 2000;
// long Encoder2 = 2000;
// int angleZ;
// int proximity = 0;
// bool tombolStartStop = false;

// void setup() {
//   // Gunakan baud rate yang cepat dan stabil
//   Serial.begin(115200);
//   Wire.begin();
//   mpu6050.begin();
//   mpu6050.calcGyroOffsets(true); 
// }

// void loop() {
//   mpu6050.update();
//   angleZ = mpu6050.getAngleZ();
//   // Lakukan pembacaan sensor Anda di sini untuk memperbarui nilai variabel
//   // contoh:
//   // Encoder1 = readEncoder1();
//   // angleZ = readMPU();
//   // ...dan seterusnya

//   // --- MEMBANGUN STRING DATA ---
  
//   // 1. Kirim nilai Encoder1 diikuti koma
//   Serial.print(Encoder1);
//   Serial.print(",");
  
//   // 2. Kirim nilai Encoder2 diikuti koma
//   Serial.print(Encoder2);
//   Serial.print(",");

//   // 3. Kirim nilai angleZ diikuti koma
//   Serial.print(angleZ);
//   Serial.print(",");

//   // 4. Kirim nilai proximity diikuti koma
//   Serial.print(proximity);
//   Serial.print(",");

//   // 5. Kirim nilai tombolStartStop.
//   // Gunakan println() untuk variabel TERAKHIR.
//   // Ini akan mengirim nilai dan karakter newline ('\n')
//   // sebagai penanda akhir dari satu paket data.
//   Serial.println(tombolStartStop);

//   Encoder1 += 1;

//   // Atur seberapa sering data dikirim
//   delay(50); // Kirim data sekitar 20 kali per detik
// }
