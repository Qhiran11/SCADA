#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int16_t r_pwmy; 
int16_t l_pwmy;

// Pin Motor Kanan (X)
int16_t r_pwmx;
int16_t l_pwmx;

// Pin Motor Belakang (Z)
int16_t r_pwmz;
int16_t l_pwmz;


int16_t servo_1;
int16_t servo_2;

int helper_pin;

void setup() {
  Serial.begin(115200);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
    // Inisialisasi I2C sebagai Master
  
  Serial.println("Arduino siap menerima paket 18-byte...");

}

void loop() {
  // PENGECEKAN YANG BENAR: Tunggu sampai ada 18 byte data
  if (Serial.available() >= 18) {
    // Logika unpacking Anda sudah benar, tidak perlu diubah
    r_pwmy = (Serial.read() << 8) | Serial.read();
    l_pwmy = (Serial.read() << 8) | Serial.read();
    
    r_pwmx = (Serial.read() << 8) | Serial.read();
    l_pwmx = (Serial.read() << 8) | Serial.read();
    
    r_pwmz = (Serial.read() << 8) | Serial.read();
    l_pwmz = (Serial.read() << 8) | Serial.read();

    servo_1 = (Serial.read() << 8) | Serial.read();
    servo_2 = (Serial.read() << 8) | Serial.read();

    helper_pin = (Serial.read() << 8) | Serial.read();

    // === KIRIM DATA KE NANO ===
    // Teruskan nilai helper_pin ke Nano melalui Serial1
    myservo.write(helper_pin);
    // printReceivedData();
  }
}


