# Antes de la instalacion
---------------------------
cat /etc/os-release
lspci -nnk | grep -A3 -E 'VGA|3D|Display'
glxinfo -B
dpkg -l libxkbcommon-x11-0 libxcb-icccm4 libxcb-keysyms1 libxcb-render-util0

# Para instalacion roboDK

curl -s https://cdn.robodk.com/downloads/Install-RoboDK.tar.gz | tar -xz
ls -ld ~/Install-RoboDK*
~/Install-RoboDK --help
~/Install-RoboDK install --platform minimal --verbose --accept-licenses --confirm-command --accept-messages
~/RoboDK/RoboDK-Start.sh
