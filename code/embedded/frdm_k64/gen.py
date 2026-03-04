#!/usr/bin/env python3
import sys

num_args = len(sys.argv)

def generate_cmds():
    if num_args > 1:
        prjname = sys.argv[1]
        print("-----copia/pega esto:-----")
        print(f"mkdir {prjname}")
        print(f"cp -r ./template/. ./{prjname}")


def main():
    print(f"Script: {sys.argv[0]}")
    print(f"Número de argumentos: {len(sys.argv) - 1}")
    
    for i, arg in enumerate(sys.argv[1:], 1):
        print(f"Argumento {i}: {arg}")

if __name__ == "__main__":
    main()
    generate_cmds()



