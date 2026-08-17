ffmpeg -framerate 20 -pattern_type glob -i 'frame*.png'   -vf crop=iw:ih-1   -c:v libx264   -pix_fmt yuv420p   -movflags +faststart   animacion.mp4
