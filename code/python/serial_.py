# -*- coding: utf-8 -*-
#!/usr/bin/python
"""
tested wih python 2.7.11 on a windows machine
(win7 professional)
pyserial module needed
history:
    initial edition: 01 Mar 2017
this script is to automate testing for Alphamos  project
one thread is in charge of readading serial port, a second
thread of writing (over serial port ).
"""
import threading
import time
import sys
import serial
global ser
global quit_flag
global filename
cmd = 'n'
baudrate = 115200

test_str ="11/28/2016 11:34:47 AM;5;0.0;0.0;40940000;409400000;40940000;409400000;40940000;409400000;40940000;409400000;40940000;409400000;40940000;409400000;40940000;409400000;40940000;409400000;40940000;409400000;40940000;409400000;40940000;409400000;40940000;409400000;40940000;409400000;40940000;409400000;0.0;0.0;0.0;0.0;0.0;4029;\r"

def print_menu():
    print("** menu ** ")
    print("   1) start")
    print("   q) quit")
    print("**press ENTER to see this menu again...")


def read_serial():
    """
    global quit_flag
    while True:
        if quit_flag is True:
            break
        data = ser.read(9999)
        datalen = len(data)
        if  datalen > 0:
            #print data.encode('hex')
            bytes_read = list(bytearray(data))
            #print bytes_read
            parser.parse(bytes_read)
    """

def write_serial():
    global cmd
    global quit_flag
    while True:
        if quit_flag is True:
            break
        time.sleep(1)
        if cmd == '1':
            ser.write(test_str)
            cmd = 0

def read_keyboard():
    global cmd
    global quit_flag
    while True:
        if quit_flag is True:
            break
        print_menu()
        user_input = raw_input(" cmd? ")
        if user_input == "":
            continue
        cmd = user_input[0]
        print cmd
        if cmd == 'q':
            quit_flag = True


class Thread(threading.Thread):
    def __init__(self, t, *args):
        threading.Thread.__init__(self, target=t, args=args)
        self.start()


###############################
# Open serial port
###############################
portname = "COM1"
print(("Connecting to port " + portname))
#timeout = 0: non-blocking mode, return immediately in any case,
#returning zero or more, up to the requested number of bytes
ser = serial.Serial(portname, baudrate, timeout=0)

if(ser.isOpen()):
    quit_flag = False
    cmd = 0
    print("port is open")
else:
    print("error opening port")
    sys.exit()
###############################
thread = Thread(read_keyboard)
#thread = Thread(read_serial)
thread = Thread(write_serial)

