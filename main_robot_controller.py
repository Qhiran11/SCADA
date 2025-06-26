# data_bridge.py
# Tugas program ini HANYA meneruskan data dari Nano ke Mega.

import serial
import time

# --- KONFIGURASI ---
# PASTIKAN port COM ini sudah benar di komputer Anda
NANO_PORT = 'COM18'
MEGA_PORT = 'COM3'
BAUD_RATE = 115200 # Kita mulai dengan baudrate standar yang stabil

# Variabel untuk menampung koneksi serial
ser_nano = None
ser_mega = None

print("Mencoba membuka koneksi serial...")

try:
    # Buka koneksi ke kedua Arduino
    ser_nano = serial.Serial(NANO_PORT, BAUD_RATE, timeout=1)
    ser_mega = serial.Serial(MEGA_PORT, BAUD_RATE, timeout=1)
    
    # Beri waktu 2 detik agar koneksi stabil setelah port dibuka
    time.sleep(2)
    print(f"Berhasil terhubung ke Nano ({NANO_PORT}) dan Mega ({MEGA_PORT})")
    print("Jembatan data aktif. Tekan Ctrl+C untuk berhenti.")

    # Loop utama untuk meneruskan data
    while True:
        # Periksa apakah ada data yang datang dari Nano
        if ser_nano.in_waiting > 0:
            # Baca satu baris data (termasuk karakter newline '\n')
            data_from_nano = ser_nano.readline()
            
            # Tampilkan di konsol laptop untuk debugging
            # .decode('utf-8').strip() mengubah bytes menjadi string yang bersih
            print(f"Meneruskan data: {data_from_nano.decode('utf-8').strip()}")
            
            # Langsung teruskan data yang sama persis ke Mega
            ser_mega.write(data_from_nano)

except serial.SerialException as e:
    print(f"[ERROR] Gagal membuka port serial: {e}")
    print("Pastikan port COM sudah benar dan tidak sedang digunakan oleh program lain (misal: Arduino IDE Serial Monitor).")
except KeyboardInterrupt:
    print("\nProgram dihentikan oleh pengguna.")
except Exception as e:
    print(f"Terjadi error tak terduga: {e}")
finally:
    # Pastikan port ditutup dengan benar saat program selesai
    if ser_nano and ser_nano.is_open:
        ser_nano.close()
        print(f"Port Nano ({NANO_PORT}) ditutup.")
    if ser_mega and ser_mega.is_open:
        ser_mega.close()
        print(f"Port Mega ({MEGA_PORT}) ditutup.")
