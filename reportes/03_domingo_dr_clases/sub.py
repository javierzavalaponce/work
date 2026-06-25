import subprocess
from pathlib import Path
import os

def ff():
    """Selecciona cualquier archivo del directorio actual"""
    cmd = "find . -type f | fzf"
    return subprocess.check_output(cmd, shell=True, text=True).strip()



