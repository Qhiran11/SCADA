import cv2
import mediapipe as mp
from playsound import playsound
import os
import threading  # 1. Impor modul threading
import serial
import struct
import time

# --- KONFIGURASI ---


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
except serial.SerialException as e:
    print(f"[ERROR] Gagal membuka port serial: {e}")
except KeyboardInterrupt:
    print("\nProgram dihentikan.")

file_path = r"C:\Users\YOGA\Downloads\Sound Effect\duar-kontol.mp3"  # Sesuaikan dengan path file Anda
a = False

# Fungsi ini akan dijalankan di thread terpisah
def play_audio_in_thread():
    """Memutar file audio menggunakan Playsound di thread terpisah."""
    try:
        print(f"Memutar: {file_path} dengan Playsound (di thread)")
        playsound(file_path, block=False) # playsound di sini bisa blocking, tapi karena di thread lain, tidak mengganggu main loop
    except Exception as e:
        print(f"Error playsound di thread: {e}")

# Inisialisasi MediaPipe Hands
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(static_image_mode=False,
                       max_num_hands=2,
                       min_detection_confidence=0.5,
                       min_tracking_confidence=0.5)
mp_drawing = mp.solutions.drawing_utils

# Buka webcam
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW))

# Indeks landmark untuk ujung jari
THUMB_TIP_INDEX = 4
INDEX_FINGER_TIP_INDEX = 12 # Indeks ujung jari telunjuk
INDEX_FINGER_PIP_INDEX = 9 # Sendi tengah jari telunjuk

while cap.isOpened():
    success, image = cap.read()
    if not success:
        print("Tidak dapat membaca dari webcam.")
        break

    image_rgb = cv2.cvtColor(cv2.flip(image, 1), cv2.COLOR_BGR2RGB)
    results = hands.process(image_rgb)
    image_bgr = cv2.cvtColor(image_rgb, cv2.COLOR_RGB2BGR)
    image_height, image_width, _ = image_bgr.shape

    if results.multi_hand_landmarks:
        for hand_idx, hand_landmarks in enumerate(results.multi_hand_landmarks):
            mp_drawing.draw_landmarks(
                image_bgr,
                hand_landmarks,
                mp_hands.HAND_CONNECTIONS)

            thumb_tip = hand_landmarks.landmark[THUMB_TIP_INDEX]
            index_finger_tip = hand_landmarks.landmark[INDEX_FINGER_TIP_INDEX]
            index_finger_pip = hand_landmarks.landmark[INDEX_FINGER_PIP_INDEX]

            thumb_tip_x, thumb_tip_y = int(thumb_tip.x * image_width), int(thumb_tip.y * image_height)
            index_tip_x, index_tip_y = int(index_finger_tip.x * image_width), int(index_finger_tip.y * image_height)
            index_pip_y = int(index_finger_pip.y * image_height)
            # print(f"Jari 1: ({thumb_tip_x}, {thumb_tip_y}), Jari 2: ({index_tip_x}, {index_tip_y}), Jari 2 PIP: {index_pip_y}")

            cv2.circle(image_bgr, (thumb_tip_x, thumb_tip_y), 10, (255, 0, 0), -1)
            cv2.putText(image_bgr, "Jari 1", (thumb_tip_x - 20, thumb_tip_y - 20),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2)

            cv2.circle(image_bgr, (index_tip_x, index_tip_y), 10, (0, 255, 0), -1)
            cv2.putText(image_bgr, "Jari 2", (index_tip_x - 20, index_tip_y - 20),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

            status_jari_2 = "Tidak Diketahui"
            
            if index_tip_y < index_pip_y:
                status_jari_2 = "Jari 2 Terangkat!"
                if not a:  # Hanya putar suara sekali saat jari terangkat
                    # 2. Buat dan mulai thread baru untuk memutar audio
                    # audio_player_thread = threading.Thread(target=play_audio_in_thread)
                    # audio_player_thread.start() # Mulai eksekusi fungsi di thread baru
                    a = True

            else:
                a = False  # Reset status a jika jari tidak terangkat
                status_jari_2 = "Jari 2 Tidak Terangkat"
                cv2.putText(image_bgr, status_jari_2, (index_tip_x, index_tip_y - 40),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
            
            # if results.multi_handedness:
            #     handedness = results.multi_handedness[hand_idx].classification[0].label
            #     cv2.putText(image_bgr, f"Tangan: {handedness}", (10, 30 + hand_idx * 30),
            #                 cv2.FONT_HERSHEY_SIMPLEX, 0.7, (200, 200, 0), 2)

            helper_pin = index_pip_y - index_tip_y  # Reset helper pin untuk setiap frame
            if helper_pin < 0:
                helper_pin = 0
            else :
                helper_pin = map(0, 180)
            
            data_to_send = [r_pwmy, l_pwmy, r_pwmx, l_pwmx, r_pwmz, l_pwmz, servo_1, servo_2, helper_pin]

            # Buat paket data biner
            # FORMAT YANG BENAR: 'h' adalah untuk signed short (2 byte)
            # Total 9 variabel * 2 byte = 18 byte
            packed_data = struct.pack('>hhhhhhhhh', *data_to_send)

            # Kirim paket data ke Arduino
            arduino.write(packed_data)
            
            print(f"Mengirim: {data_to_send} | Ukuran Paket: {len(packed_data)} bytes")
            # print(f"Status Jari 2: {index_pip_y - index_tip_y}")


    cv2.imshow('MediaPipe Hands - Deteksi Jari', image_bgr)

    if cv2.waitKey(5) & 0xFF == ord('q'):
        break

hands.close()
cap.release()
cv2.destroyAllWindows()