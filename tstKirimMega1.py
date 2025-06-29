# python_sender_6_data_mixed.py
import serial
import struct
import time

# --- KONFIGURASI ---
ARDUINO_PORT = 'COM3'
BAUD_RATE = 115200

# --- Contoh Variabel Data ---
pwm_values = [-255, 0, 255]
servo_values = [45, 135]
helper_data = 7


# Pin Motor Kiri (Y)
r_pwmy = 60
l_pwmy = 0

# Pin Motor Kanan (X)
r_pwmx = 0
l_pwmx = 60

# Pin Motor Belakang (Z)
r_pwmz = 0
l_pwmz = 0


servo_1 = 10
servo_2 = 11

helper_pin = 0

try:
    print(f"Mencoba terhubung ke {ARDUINO_PORT}...")
    arduino = serial.Serial(ARDUINO_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)
    print("Terhubung. Mulai mengirim data...")

    while True:
        # Gabungkan data untuk di-pack. Servo dan helper digabung.

        
        data_to_send = [r_pwmy, l_pwmy, r_pwmx, l_pwmx, r_pwmz, l_pwmz, servo_1, servo_2, helper_pin]

        # Buat paket data biner
        # FORMAT YANG BENAR: 'h' adalah untuk signed short (2 byte)
        # Total 9 variabel * 2 byte = 18 byte
        packed_data = struct.pack('>hhhhhhhhh', *data_to_send)

        # Kirim paket data ke Arduino
        arduino.write(packed_data)
        helper_pin += 1  # Update helper pin untuk simulasi
        
        print(f"Mengirim: {data_to_send} | Ukuran Paket: {len(packed_data)} bytes")

        # Simulasi perubahan data untuk pengujian
        pwm_values[0] = (pwm_values[0] + 10)
        if pwm_values[0] > 255:
            pwm_values[0] = -255
            
        time.sleep(0.1)

except serial.SerialException as e:
    print(f"[ERROR] Gagal membuka port serial: {e}")
except KeyboardInterrupt:
    print("\nProgram dihentikan.")
finally:
    if 'arduino' in locals() and arduino.is_open:
        arduino.close()
        print("Koneksi serial ditutup.")
