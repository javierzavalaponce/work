ffmpeg -f alsa -i plughw:1,0 -ac 1 -acodec libmp3lame -b:a 128k mi.mp3
