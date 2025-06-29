import argparse
import time
from collections import deque
import cv2
import imutils
import numpy as np
from imutils.video import VideoStream
import serial
import struct
import keyboard
from simple_pid import PID  # <-- Menggunakan library simple-pid

# Argument parser
ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video", help="Path to the (optional) video file")
ap.add_argument("-b", "--buffer", default=64, type=int, help="max buffer size")
args = vars(ap.parse_args())
# ============================================================================================
# Inisialisasi koneksi serial dengan Arduino Mega
arduino_baudrate = 9600  # Sesuaikan baudrate
try:
    mega_port = 'COM7'  # Sesuaikan dengan port Arduino
    mega = serial.Serial(mega_port, arduino_baudrate, timeout=0)
    print(f"Port Mega {mega_port} terbuka")
    time.sleep(0.5)  # Tunggu koneksi serial siap
except Exception as e:
    print(f"Error: {e}")
    print(f"Eror: Port Mega {mega_port} tidak terbuka")
    mega = None

try:
    nano_port = 'COM9'  # Sesuaikan dengan port Arduino
    nano = serial.Serial(nano_port, arduino_baudrate, timeout=0)
    print(f"Port Nano {nano_port} terbuka")
    time.sleep(0.5)  # Tunggu koneksi serial siap
except Exception as e:
    print(f"Error: {e}")
    print(f"Eror: Port Nano {nano_port} tidak terbuka")
    nano = None
# ============================================================================================
# PID Controller (Kelas PID kustom sudah dihapus)

# Target agar bola berada di tengah frame (x = 400)
target_x = 400

# --- PERUBAHAN UTAMA: Inisialisasi PID menggunakan simple-pid ---
pid_x = PID(Kp=0.3, Ki=0.0, Kd=0.1, setpoint=target_x)
# Atur batas output agar sesuai dengan kebutuhan kecepatan motor
# Misalkan, rentang koreksi yang wajar adalah -85 hingga 85
pid_x.output_limits = (-85, 85) 
pid_x.sample_time = 0.01 # Atur waktu sampling untuk konsistensi


def PROSES_PID(sumbuX, sumbuY):
    global mega, port_baru

    # --- PERUBAHAN UTAMA: Hitung koreksi menggunakan simple-pid ---
    # Cukup panggil objek pid dengan nilai saat ini
    koreksi = pid_x(sumbuX)

    # Kecepatan dasar
    base_speed = 85

    # Koreksi untuk motor kiri dan kanan
    # Tanda minus pada koreksi mungkin perlu disesuaikan tergantung wiring motor
    roda_kiri = int(base_speed - koreksi) 
    roda_kanan = int(base_speed + koreksi)

    # Batasi nilai PWM agar tetap dalam 0-255
    roda_kiri = max(0, min(255, roda_kiri))
    roda_kanan = max(0, min(255, roda_kanan))

    try:
        mega.write(struct.pack('>hh', roda_kanan, roda_kiri))
        print(f"PWM dikirim: Kanan={roda_kanan}, Kiri={roda_kiri} | Koreksi: {koreksi:.2f}")
    except Exception as e:
        print(f"Error kirim PWM: {e}")
        port_baru = True

# ============================================================================================
# Buffer untuk menyimpan titik lintasan bola
pts = deque(maxlen=args["buffer"])
print("Mengambil gambar dari kamera...")
vs = VideoStream(src=0).start()
print("kamera sudah siap")

time.sleep(2.0)

# ============================================================================================
# State terakhir yang dikirim
last_x_state, last_y_state = 0, 0

port_baru = False

def get_zone(x):
    if 0 < x <= 200:
        return "far_left"
    elif 200 < x < 365:
        return "left"
    elif 365 <= x <= 435:
        return "center"
    elif 435 < x < 600:
        return "right"
    elif 600 <= x <= 800:
        return "far_right"
    else:
        return "out"

def PROSES(sumbuX, sumbuY):
    global last_x_state, mega, port_baru

    if last_x_state is None:
        last_x_state = get_zone(sumbuX)
        return  # Jangan kirim dulu, hanya inisialisasi

    current_zone = get_zone(sumbuX)

    if current_zone != last_x_state:
        try:
            mega.write(struct.pack('>hh', sumbuX, sumbuY))
            print(f"Data dikirim: {sumbuX},{sumbuY} (Zona: {current_zone})")
            last_x_state = current_zone  # Simpan zona terakhir
        except Exception as e:
            print(f"Error: {e}")
            port_baru = True


# Buat jendela untuk trackbar
cv2.namedWindow("Trackbars")

# Fungsi kosong untuk trackbar
def nothing(x):
    pass

# Inisialisasi trackbar untuk HSV
cv2.createTrackbar("H_min", "Trackbars", 0, 255, nothing)
cv2.createTrackbar("H_max", "Trackbars", 100, 255, nothing)
cv2.createTrackbar("S_min", "Trackbars", 150, 255, nothing)
cv2.createTrackbar("S_max", "Trackbars", 255, 255, nothing)
cv2.createTrackbar("V_min", "Trackbars", 100, 255, nothing)
cv2.createTrackbar("V_max", "Trackbars", 255, 255, nothing)

a = False
aa = True
b = True
nano_bool = True

while True:
    frame = vs.read()
    frame = frame[1] if args.get("video", False) else frame
    if frame is None:
        break

    frame = imutils.resize(frame, width=800, height=600)  # Contoh dengan height = 600
    blurred = cv2.GaussianBlur(frame, (11, 11), 0)
    hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

    # Deteksi bola berdasarkan warna
    H_min = cv2.getTrackbarPos("H_min", "Trackbars")
    H_max = cv2.getTrackbarPos("H_max", "Trackbars")
    S_min = cv2.getTrackbarPos("S_min", "Trackbars")
    S_max = cv2.getTrackbarPos("S_max", "Trackbars")
    V_min = cv2.getTrackbarPos("V_min", "Trackbars")
    V_max = cv2.getTrackbarPos("V_max", "Trackbars")

    # Gunakan nilai trackbar untuk thresholding warna
    orangeLower = (H_min, S_min, V_min)
    orangeUpper = (H_max, S_max, V_max)

    # Masking warna
    mask = cv2.inRange(hsv, orangeLower, orangeUpper)

    mask = cv2.erode(mask, None, iterations=2)
    mask = cv2.dilate(mask, None, iterations=2)

    cnts = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    cnts = imutils.grab_contours(cnts)

    center = None

    if len(cnts) > 0:
        c = max(cnts, key=cv2.contourArea)
        ((x, y), radius) = cv2.minEnclosingCircle(c)
        M = cv2.moments(c)
        center = (int(M['m10'] / M['m00']), int(M['m01'] / M['m00']))

        if radius > 10:
            cv2.circle(frame, (int(x), int(y)), int(radius), (0, 255, 255), 2)
            cv2.circle(frame, center, 5, (0, 0, 255), -1)
            cv2.putText(frame, "BOLA", (center[0] + 10, center[1]), cv2.FONT_HERSHEY_SIMPLEX, 0.4, (255, 0, 0), 1)
            cv2.putText(frame, f"({center[0]},{center[1]})", (center[0] + 10, center[1] + 15),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.4, (0, 0, 255), 1)


    try:
        if keyboard.is_pressed('a'):
            a = True
            print("Serial lanjut")
        if keyboard.is_pressed('b'):
            a = False
            b = True
            print("Serial berhenti sejenak")
            aa = True
            b = True
            nano_bool = True
        if b:
            data = mega.readline().decode().strip()
            if data == "Start":
                print(data)
                b = False
        if nano_bool and not b:
            data_nano = nano.readline().decode().strip()
            if data_nano == "Ganti":
                print(data_nano)
                nano_bool = False

    except Exception as e:
        print(f"Error: {e}")
        
    
    # Jika serial terbuka, kirim koordinat
    if center is not None:
        if not b and nano_bool:
            PROSES_PID(center[0], center[1])
            aa = True
            b = False
        if not nano_bool:
            PROSES(center[0], center[1])
            aa = True
            b = False

    elif center is None and aa:
        pid_x.reset()  # Reset integral PID saat bola hilang
        try:    
            mega.write(struct.pack('>hh', 0, 0))
            print("Data dikirim: 0,0 (Tidak ada bola)")
        except Exception as e:
            print("Data dikirim: 0,0 (Tidak ada bola)")
        aa = False
    
    if port_baru:
        MEGA_port = input("Masukkan port MEGA baru: ")
        try:
            mega = serial.Serial(MEGA_port, 9600, timeout=1)
            time.sleep(1)
            print(f"Port {MEGA_port} terbuka")
            port_baru = False
        except Exception as e:
            print(f"Error: {e}")
            print(f"Error: Port {MEGA_port} tidak terbuka")
            port_baru = True
        

    # Gambar garis tengah horizontal dan vertikal
    cv2.line(frame, (0, frame.shape[0] // 2), (frame.shape[1], frame.shape[0] // 2), (0, 0, 255), 1)
    cv2.line(frame, (frame.shape[1] // 2, 0), (frame.shape[1] // 2, frame.shape[0]), (255, 255, 255), 1)

    pts.append(center)

    cv2.imshow("Frame", frame)
    cv2.imshow("Mask", mask)
    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        break
    
if not args.get("video", False):
    vs.stop()
else:
    vs.release()

cv2.destroyAllWindows()
