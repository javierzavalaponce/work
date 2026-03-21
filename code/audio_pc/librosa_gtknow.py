import librosa
import librosa.display
import matplotlib.pyplot as plt
import numpy as np

Load Audio File
y, sr = librosa.load('path/to/audio/file.mp3')

Extract Mel Spectrogram
mel_spectrogram = librosa.feature.melspectrogram(y=y, sr=sr)

Convert to Decibels (Log Scale)
mel_spectrogram_db = librosa.power_to_db(mel_spectrogram, ref=np.max)

Plot Mel spectrogram
plt.figure(figsize=(10, 4))
librosa.display.specshow(mel_spectrogram_db, x_axis='time', y_axis='mel', sr=sr, cmap='viridis')
plt.colorbar(format='%+2.0f dB')
plt.title('Mel Spectrogram')
plt.show()
