import threading
import time
import sys
import serial

# Global variables
ser = None
quit_flag = False
filename = ""
cmd = 'n'
baudrate = 115200

def print_menu():
    print("** menu ** ")
    print("   1) start")
    print("   q) quit")
    print("**press ENTER to see this menu again...")

def read_serial():
    """
    Simplified but robust serial reader
    """
    global quit_flag
    global ser
    
    buffer = ""
    print("[READER] Started")
    
    while not quit_flag:
        try:
            if ser and ser.is_open and ser.in_waiting:
                # Leer todo lo disponible
                data = ser.read(ser.in_waiting)
                
                if data:
                    print(data.decode(errors='ignore'), end='')
                        
            time.sleep(0.01)  # Evitar 100% CPU
            
        except serial.SerialException as e:
            print(f"[ERROR] Port error: {e}")
            time.sleep(1)
        except Exception as e:
            print(f"[ERROR] {e}")
            time.sleep(0.1)
    
    print("[READER] Stopped")



def read_keyboard():
    """
    Read user input from keyboard
    """
    global cmd
    global quit_flag
    
    while not quit_flag:
        print_menu()
        try:
            user_input = input(" cmd? ")
            if not user_input:  # Empty input
                continue
            
            cmd = user_input[0].lower()
            print(f"Command: {cmd}")
            
            if cmd == 'q':
                print("Quitting...")
                quit_flag = True
                
        except KeyboardInterrupt:
            print("\nInterrupted by user")
            quit_flag = True
            break
        except EOFError:
            break

class Thread(threading.Thread):
    def __init__(self, t, *args):
        threading.Thread.__init__(self, target=t, args=args)
        self.daemon = True  # Threads will exit when main thread exits
        self.start()

###############################
# Open serial port
###############################
portname = "/dev/ttyACM0"
print(f"Connecting to port {portname}")

try:
    # timeout=0: non-blocking mode
    ser = serial.Serial(portname, baudrate, timeout=0)
    
    if ser.is_open:
        quit_flag = False
        cmd = '0'
        print("port is open")
    else:
        print("error opening port")
        sys.exit(1)
        
except serial.SerialException as e:
    print(f"Serial port error: {e}")
    sys.exit(1)
except Exception as e:
    print(f"Unexpected error: {e}")
    sys.exit(1)

###############################
# Start threads
print("\nStarting threads...")
read_thread = Thread(read_serial)
keyboard_thread = Thread(read_keyboard)
#wite_thread = Thread(write_serial)
# Uncomment if you want to use read_serial thread


###############################
# Main loop - wait for quit
try:
    while not quit_flag:
        time.sleep(0.1)  # Small sleep to prevent high CPU usage
except KeyboardInterrupt:
    print("\nProgram interrupted by user")
    quit_flag = True
finally:
    # Clean up
    if ser and ser.is_open:
        print("Closing serial port...")
        ser.close()
    print("Program terminated")