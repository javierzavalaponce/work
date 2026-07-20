import whisper

model = whisper.load_model("small")
result = model.transcribe("mi.mp3", language="Spanish", fp16=False)

with open("transcripcion.txt", "w", encoding="utf-8") as f:
    f.write(result["text"])

