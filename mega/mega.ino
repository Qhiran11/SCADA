#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD.
// Ganti alamat 0x27 jika LCD Anda menggunakan alamat yang berbeda (misal: 0x3F).
// Format: LiquidCrystal_I2C(alamat_i2c, kolom, baris)
LiquidCrystal_I2C lcd(0x27, 16, 2);
// data_receiver.ino
// Tugas program ini HANYA menerima data dari Laptop dan berkedip.

// Pin untuk LED bawaan di board Mega (biasanya pin 13)
int LED_PIN = 53;
int hasilAngka = 1;

void setup() {

  // Mulai komunikasi Serial dengan baudrate yang sama seperti di Python
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
   lcd.init();
  // Nyalakan backlight LCD
  lcd.backlight();
  
  // Tampilkan pesan startup di LCD
  lcd.setCursor(0, 0); // Pindah ke kolom 0, baris 0
  lcd.print("Robot Aktif!");
  lcd.setCursor(0, 1); // Pindah ke kolom 0, baris 1
  lcd.print("Menunggu data...");// Tunggu koneksi Seria
  
  
}

void loop() { 
  // Periksa apakah ada data yang masuk dari Laptop
  if (Serial.available() > 0) {
    // Baca seluruh baris data sampai menemukan karakter newline
    String receivedData = Serial.readStringUntil('\n');

    hasilAngka = receivedData.toInt();
    
    // // Tampilkan data yang diterima ke Serial Monitor milik Mega untuk verifikasi
    // Serial.print("Data diterima dari Laptop: ");
    // Serial.println(hasilAngka);
    updateLcdDisplay(receivedData);
    
   
  }
   if (hasilAngka == 0){
      // Berikan feedback visual: kedipkan LED
      digitalWrite(LED_PIN, HIGH); // Nyalakan LED
      // delay(200);                  // Tunggu sebentar
      // digitalWrite(LED_PIN, LOW);  // Matikan LED
      // delay(200);   
    }
    else{
      digitalWrite(LED_PIN, LOW); // Nyalakan LED
    }
}


void updateLcdDisplay(String dataToShow) {
  // Bersihkan layar terlebih dahulu.
  // Catatan: lcd.clear() sedikit lambat. Untuk optimasi tingkat lanjut, 
  // Anda bisa hanya menimpa karakter lama, tapi ini sudah cukup baik.
  lcd.clear();
  
  // Tampilkan label di baris pertama
  lcd.setCursor(0, 0);
  lcd.print("Data GZ:");
  
  // Tampilkan nilai data yang diterima di baris kedua
  lcd.setCursor(0, 1);
  lcd.print(dataToShow);
}
