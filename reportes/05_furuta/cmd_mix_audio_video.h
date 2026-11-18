ffmpeg -i PenduloSimple.mp4 -i audio2.mp3   -map 0:v:0 -map 1:a:0   -c:v copy -c:a aac -b:a 192k   -shortest PenduloSimple_con_audio.mp4



