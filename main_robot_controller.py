# main_robot_controller.py
import cv2
import imutils
import numpy as np
import serial
import time
import threading
import queue

# ============================================================================================
# KONFIGURASI
# ============================================================================================
NANO_PORT = 'COM9'  # Port untuk sensor (MPU, Proximity) & handler
MEGA_PORT = 'COM7'  # Port untuk kontrol gerak (omni wheels)
BAUD_RATE = 115200

FRAME_WIDTH = 800
FRAME_HEIGHT = 600
CAMERA_SRC = 0

# ============================================================================================
# KELAS & VARIABEL BERSAMA (THREAD-SAFE)
# ============================================================================================
class RobotState:
    """Satu tempat untuk menyimpan semua state robot yang diterima."""
    def __init__(self):
        self.yaw = 0.0
        self.proximity_triggered = False
        self.ball_in_handler = False # Mungkin perlu logika tambahan
        self.lock = threading.Lock()

    def update_from_nano(self, yaw, proximity):
        with self.lock:
            self.yaw = yaw
            self.proximity_triggered = (proximity == 1)

    def get_state(self):
        with self.lock:
            return self.yaw, self.proximity_triggered

# State robot global
robot_state = RobotState()
# Queue untuk mengirim perintah ke kedua Arduino
mega_command_queue = queue.Queue()
nano_command_queue = queue.Queue()

# ============================================================================================
# THREAD KOMUNIKASI
# ============================================================================================
def serial_communicator_thread(port_name, ser_instance, command_queue):
    """Satu fungsi generik untuk menangani I/O serial untuk satu port."""
    print(f"[INFO] Thread untuk {port_name} dimulai.")
    while True:
        try:
            # Mengirim perintah jika ada di queue
            if not command_queue.empty():
                command = command_queue.get_nowait()
                ser_instance.write(command.encode('utf-8'))

            # Membaca data yang masuk
            if ser_instance.in_waiting > 0:
                line = ser_instance.readline().decode('utf-8').strip()
                if port_name == "Nano" and line:
                    parts = line.split(',')
                    if len(parts) == 2:
                        yaw, prox = float(parts[0]), int(parts[1])
                        robot_state.update_from_nano(yaw, prox)
                # Bisa ditambahkan logika pembacaan dari Mega (misal: untuk debug)

        except queue.Empty:
            pass # Tidak apa-apa jika queue kosong
        except Exception as e:
            print(f"[ERROR] di thread {port_name}: {e}")
            time.sleep(1) # Beri jeda jika terjadi error

# ============================================================================================
# FUNGSI UTAMA & LOGIKA ROBOT
# ============================================================================================
def main_logic_thread(nano_q, mega_q):
    """Otak utama robot: Visi, Strategi, dan Pembuatan Perintah."""
    vs = imutils.video.VideoStream(src=CAMERA_SRC).start()
    time.sleep(2.0)
    print("[INFO] Kamera siap.")

    # ... (Kode untuk setup window & trackbar HSV bisa diletakkan di sini) ...

    while True:
        frame = vs.read()
        if frame is None: break
        frame = imutils.resize(frame, width=FRAME_WIDTH)

        # --- Proses Deteksi Bola (dari kode Anda) ---
        # ... (hsv, mask, findContours, dll) ...
        # Hasilnya adalah `center` (posisi bola) dan `radius`
        center, radius = None, 0
        # (Tempatkan kode deteksi bola Anda di sini)

        # --- Ambil State Robot Terbaru ---
        current_yaw, proximity_triggered = robot_state.get_state()

        # ===================================================================
        # STRATEGI PERMAINAN
        # ===================================================================
        # Perintah default
        vx, vy, v_omega = 0.0, 0.0, 0.0
        handler_cmd = 0 # 0=stop, 1=tangkap, 2=lepas/tendang pelan

        if center is not None:
            # BOLA TERLIHAT
            target_x = FRAME_WIDTH // 2
            error_x = target_x - center[0]

            # Atur kecepatan rotasi untuk mengarahkan robot ke bola
            v_omega = 0.4 * error_x

            # Atur kecepatan maju berdasarkan jarak (radius bola)
            # Jika bola dekat (radius besar), bergerak lebih pelan
            vx = 150 - (radius * 1.5)
            vx = max(50, min(150, vx)) # Batasi kecepatan antara 50 dan 150

            # Jika sensor proksimitas aktif, berarti bola sangat dekat
            if proximity_triggered:
                # Bola sudah di depan handler, berhenti maju dan tangkap
                vx = 0
                handler_cmd = 1 # Perintah untuk menangkap
        else:
            # BOLA TIDAK TERLIHAT
            # Berputar di tempat untuk mencari bola
            v_omega = 120 # Kecepatan rotasi konstan
            vx = 0
            handler_cmd = 0 # Pastikan handler tidak aktif

        # ===================================================================
        # KIRIM PERINTAH KE ANTRIAN (QUEUE)
        # ===================================================================
        # Perintah gerak untuk Mega
        mega_cmd_str = f"<{vx},{vy},{v_omega}>\n"
        mega_q.put(mega_cmd_str)

        # Perintah handler untuk Nano
        nano_cmd_str = f"<{handler_cmd}>\n"
        nano_q.put(nano_cmd_str)

        # ... (Kode visualisasi untuk menampilkan frame, bola, dll) ...
        cv2.imshow("Frame", frame)
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            break

    # Cleanup
    vs.stop()
    cv2.destroyAllWindows()
    mega_q.put("<0,0,0>\n") # Kirim perintah berhenti
    nano_q.put("<0>\n")

# ============================================================================================
# BLOK EKSEKUSI UTAMA
# ============================================================================================
if __name__ == "__main__":
    ser_mega, ser_nano = None, None
    try:
        ser_mega = serial.Serial(MEGA_PORT, BAUD_RATE, timeout=0.1)
        ser_nano = serial.Serial(NANO_PORT, BAUD_RATE, timeout=0.1)
        print("[INFO] Semua port serial terbuka.")
        time.sleep(2)

        # Buat dan mulai thread untuk setiap port
        mega_thread = threading.Thread(target=serial_communicator_thread, args=("Mega", ser_mega, mega_command_queue))
        nano_thread = threading.Thread(target=serial_communicator_thread, args=("Nano", ser_nano, nano_command_queue))
        mega_thread.daemon = True
        nano_thread.daemon = True
        mega_thread.start()
        nano_thread.start()

        # Jalankan logika utama
        main_logic_thread(nano_command_queue, mega_command_queue)

    except Exception as e:
        print(f"[FATAL] Gagal memulai: {e}")
    finally:
        if ser_mega and ser_mega.is_open: ser_mega.close()
        if ser_nano and ser_nano.is_open: ser_nano.close()
        print("[INFO] Selesai.")