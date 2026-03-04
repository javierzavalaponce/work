-----
para instalar esp32 sobre debian 13
sudo apt-get update
sudo apt-get install git wget flex bison gperf python3 python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0


mkdir -p ~/esp
cd ~/esp

# Clonar el repositorio
git clone --recursive https://github.com/espressif/esp-idf.git




cd ~/esp/esp-idf
./install.sh esp32




echo "alias get_idf='. \$HOME/esp/esp-idf/export.sh'" >> ~/.bashrc

# Recargar configuración
source ~/.bashrc


varfica instalacion:
# Activar entorno
get_idf

# Verificar versión
idf.py --version

---
bien hasta aqui hay dos folders impornantes
~/esp
y 
~/.espressif
yo quiero poner codigo en otra ruta
p ej:


/home/control/work/code/embedded/esp32

pregunta:
que debo hacer para mantener mi folder versionado: ~/work
, es decir esa estructura de carpetas?

