// data_receiver.ino
// Tugas program ini HANYA menerima data dari Laptop dan berkedip.

// Pin untuk LED bawaan di board Mega (biasanya pin 13)
int LED_PIN = 53;
int hasilAngka = 1;

void setup() {
  // Mulai komunikasi Serial dengan baudrate yang sama seperti di Python
  Serial.begin(9600);
  
  // Set pin LED sebagai output
  pinMode(LED_PIN, OUTPUT);
  
  // Beri pesan saat startup
  Serial.println("Mega siap menerima data dari Laptop...");
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
    
   
  }
   if (hasilAngka == 0){
      // Berikan feedback visual: kedipkan LED
      digitalWrite(LED_PIN, HIGH); // Nyalakan LED
      delay(200);                  // Tunggu sebentar
      digitalWrite(LED_PIN, LOW);  // Matikan LED
      delay(200);   
    }
    else{
      digitalWrite(LED_PIN, LOW); // Nyalakan LED
    }
}
