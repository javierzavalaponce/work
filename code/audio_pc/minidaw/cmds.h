g++ mixer.cpp -o mixer -lsndfile -lportaudio
delay_wav.c -o delay_wav -lsndfile

gcc delay_wav.c -o delay_wav -lsndfile
g++ raw_input.cpp -o raw_input
