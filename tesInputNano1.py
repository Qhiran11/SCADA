# data_parser.py
# Menerima satu baris data dari Arduino dan memisahkannya kembali
# menjadi variabel-variabel yang bisa digunakan.

import serial
import time

# --- KONFIGURASI ---
# Sesuaikan port dengan port Arduino Nano Anda
NANO_PORT = 'COM13'
BAUD_RATE = 115200

# Fungsi untuk memproses satu baris data
def parse_and_use_data(data_line):
    """Memisahkan string CSV dan mengonversi ke tipe data yang benar."""
    try:
        # 1. Pisahkan string berdasarkan koma menjadi sebuah list
        #    Contoh: "2000,2000,90,0,1" -> ['2000', '2000', '90', '0', '1']
        parts = data_line.strip().split(',')
        
        # 2. Periksa apakah kita menerima jumlah data yang benar
        if len(parts) == 5:
            # 3. Konversi setiap string ke tipe data yang sesuai
            encoder1_val = int(parts[0])
            encoder2_val = int(parts[1])
            angleZ_val = int(parts[2])
            proximity_val = int(parts[3])
            # Konversi '0' atau '1' kembali menjadi boolean (False/True)
            tombol_val = bool(int(parts[4])) 
            
            # 4. Sekarang Anda bisa menggunakan variabel-variabel ini
            print(f"Data Diterima -> E1: {encoder1_val}, E2: {encoder2_val}, Z: {angleZ_val}, Prox: {proximity_val}, Tombol: {tombol_val}")
            
            # Di sini Anda akan memasukkan logika robot Anda,
            # misalnya mengirim perintah ke Arduino Mega berdasarkan data ini.

        else:
            print(f"[Peringatan] Data tidak lengkap diterima: {data_line}")
            
    except ValueError:
        # Terjadi jika salah satu `int()` gagal, misal menerima teks "abc"
        print(f"[Error] Gagal mengonversi data: {data_line}")
    except Exception as e:
        print(f"Error tak terduga saat parsing: {e}")

# --- LOOP UTAMA ---
try:
    print(f"Mencoba terhubung ke {NANO_PORT}...")
    ser_nano = serial.Serial(NANO_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)
    print("Terhubung. Menunggu data...")

    while True:
        if ser_nano.in_waiting > 0:
            # Baca satu baris data lengkap (sampai ada '\n')
            line = ser_nano.readline().decode('utf-8')
            parse_and_use_data(line)

except serial.SerialException as e:
    print(f"[FATAL] Gagal terhubung ke port serial: {e}")
except KeyboardInterrupt:
    print("\nProgram dihentikan.")
finally:
    if 'ser_nano' in locals() and ser_nano.is_open:
        ser_nano.close()
        print("Koneksi serial ditutup.")
