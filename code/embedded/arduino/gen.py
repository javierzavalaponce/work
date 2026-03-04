#!/usr/bin/env python3
import sys

num_args = len(sys.argv)

def generate_cmds():
    if num_args > 1:
        prjname = sys.argv[1]
        print("-----copia/pega esto:-----")
        print(f"mkdir {prjname}")
        print(f"cp ./template/blink.ino ./{prjname}/{prjname}.ino")
        print(f"mkdir ./{prjname}/.vscode")
        print(f"cp ./template/c_cpp_properties.json ./{prjname}/.vscode")
        print(f"cp ./template/launch.json ./{prjname}/.vscode")
        print(f"cp ./template/settings.json ./{prjname}/.vscode")
        print(f"sed -i 's/blink/{prjname}/g' ./{prjname}/.vscode/launch.json") 
        print(f"cp ./template/debug.sh ./{prjname}")
        print(f"sed -i 's/blink/{prjname}/g' ./{prjname}/debug.sh")    
        print("-----------------------")       
        print("   ")
        print("1. ->para compilar:")
        print(f"arduino-cli compile --fqbn arduino:avr:uno ./{prjname}/{prjname}.ino")
        print("2. ->para checar port:")       
        print("ls /dev/tty*")
        print("3. ->para flashear:")
        print(f"arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno ./{prjname}/{prjname}.ino")
        print("TEST MINICOM: minicom -D /dev/ttyACM0 -b 9600")
        print("-----------------------") 
        print("   ")
        print("4. ->para compilar y debuggear sobre qemu:")
        print(f"cd ./{prjname}")
        print(f"./debug.sh &")
        print("   ")
        print("4. ->para lanzar gdb:")
        print(f"avr-gdb ./build/{prjname}.ino.elf")
        print("-----------------------hint para debug en GDB:") 
        print("target remote :1234")
        print("break main")
        print("continue")
        print("step")
        print("next")



def main():
    print(f"Script: {sys.argv[0]}")
    print(f"Número de argumentos: {len(sys.argv) - 1}")
    
    for i, arg in enumerate(sys.argv[1:], 1):
        print(f"Argumento {i}: {arg}")

if __name__ == "__main__":
    main()
    generate_cmds()



