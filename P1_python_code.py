import socket
import threading
import tkinter as tk

# Replace with your Arduino IP
ARDUINO_IP = "192.168.41.47"
PORT = 5000

class LEDControllerApp:
    def __init__(self, master):
        self.master = master
        master.title("Arduino LED Control")
        master.geometry("160x160")
        

        # przyciski

            # przycisk 1
        self.button1 = tk.Button(master, text="↑", font=("Arial", 14), bg="gray", fg="white")
        self.button1.place(x = 60, y = 10, width=40, height=40)

        self.button1.bind("<ButtonPress-1>", self.press_button1)
        self.button1.bind("<ButtonRelease-1>", self.release_button1)

            # przycisk 2
        self.button2 = tk.Button(master, text="↓", font=("Arial", 14), bg="gray", fg="white")
        self.button2.place(x = 60, y = 110, width=40, height=40)

        self.button2.bind("<ButtonPress-1>", self.press_button2)
        self.button2.bind("<ButtonRelease-1>", self.release_button2)

            # przycisk 3
        self.button3 = tk.Button(master, text="←", font=("Arial", 14), bg="gray", fg="white")
        self.button3.place(x = 10, y = 60, width=40, height=40)

        self.button3.bind("<ButtonPress-1>", self.press_button3)
        self.button3.bind("<ButtonRelease-1>", self.release_button3)

            # przycisk 4
        self.button4 = tk.Button(master, text="→", font=("Arial", 14), bg="gray", fg="white")
        self.button4.place(x = 110, y = 60, width=40, height=40)

        self.button4.bind("<ButtonPress-1>", self.press_button4)
        self.button4.bind("<ButtonRelease-1>", self.release_button4)

        

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((ARDUINO_IP, PORT))

        threading.Thread(target=self.receive_messages, daemon=True).start()


    # funkcje wysyłające sygnał do arduino

        # przycisk 1
    def press_button1(self, event):
        self.send_command("1")  # gdy button1 jest wciśnięty -> dron jedzie do przodu
        
    def release_button1(self, event):
        self.send_command("2")  # gdy button1 nie jest wciśnięty -> dron przestaje jechać do przodu

        # przycisk 2
    def press_button2(self, event):
        self.send_command("3")  # gdy button2 jest wciśnięty -> dron jedzie do tyłu

    def release_button2(self, event):
        self.send_command("4")  # gdy button2 nie jest wciśnięty -> dron przestaje jechać do tyłu

        # przycisk 3
    def press_button3(self, event):
        self.send_command("5")  # gdy button3 jest wciśnięty -> dron obraca się w lewo

    def release_button3(self, event):
        self.send_command("6")  # gdy button3 nie jest wciśnięty -> dron przestaje obracać się w lewo

        # przycisk 4
    def press_button4(self, event):
        self.send_command("7")  # gdy button4 jest wciśnięty -> dron obraca się w prawo

    def release_button4(self, event):
        self.send_command("8")  # gdy button4 nie jest wciśnięty -> dron przestaje obracać się w prawo



    def send_command(self, cmd):
        try:
            self.sock.sendall((cmd + "\n").encode('utf-8'))
        except:
            self.status_label.config(text="Status: Connection Lost")

    def receive_messages(self):
        while True:
            try:
                data = self.sock.recv(1024).decode('utf-8')
                if data:
                    status = data.strip().replace("STATUS ", "")
                    self.status_label.config(text=f"Status: {status}")
            except:
                break

if __name__ == "__main__":
    root = tk.Tk()
    app = LEDControllerApp(root)
    root.mainloop()
