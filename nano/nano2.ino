// arduino_nano_i2c_slave.ino
// Menerima perintah dari Mega via I2C dan menggunakan Serial untuk debug.

#include <Wire.h>

// Definisikan alamat I2C untuk Nano (harus sama dengan di kode Mega)
#define NANO_I2C_ADDRESS 8

// Variabel untuk menyimpan perintah dari Mega.
// 'volatile' penting karena variabel ini diubah oleh interrupt (onReceive).
volatile int16_t commandFromMega = 0;
volatile bool newData = false;

void setup() {
  // Mulai Serial untuk debugging ke Laptop
  Serial.begin(115200); 
  
  // Mulai I2C sebagai Slave dengan alamat yang ditentukan
  Wire.begin(NANO_I2C_ADDRESS);
  
  // Daftarkan fungsi yang akan dipanggil saat data diterima
  Wire.onReceive(receiveEvent); 
  
  Serial.println("Nano (I2C Slave) siap. Buka monitor ini untuk debug.");
}

void loop() {
  // Periksa apakah ada data baru yang diterima dari Mega
  if (newData) {
    newData = false; // Reset flag
    
    // Tampilkan perintah yang baru diterima di Serial Monitor
    Serial.print("Perintah baru dari Mega: ");
    Serial.println(commandFromMega);

    // Di sini, Anda bisa menggunakan 'commandFromMega' untuk melakukan sesuatu
    // if (commandFromMega == 5) { /* lakukan aksi A */ }
    // if (commandFromMega == 10) { /* lakukan aksi B */ }
  }
}

/**
 * @brief Fungsi ini dipanggil secara otomatis (interrupt) saat
 * Mega mengirim data ke alamat I2C ini.
 * @param howMany Jumlah byte yang diterima.
 */
void receiveEvent(int howMany) {
  // Pastikan kita menerima data yang benar (2 byte untuk int16_t)
  if (howMany == 2) {
    byte highByte = Wire.read();
    byte lowByte = Wire.read();
    commandFromMega = (highByte << 8) | lowByte;
    newData = true; // Set flag bahwa ada data baru
  }
}
