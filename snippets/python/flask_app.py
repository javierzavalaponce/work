
from flask import Flask

app = Flask(__name__)


@app.route("/")
def inicio():
    return "<h1>Mi laboratorio de ingeniería</h1><p>¡Mi primera página con Flask!</p>"


if __name__ == "__main__":
    app.run(debug=True)


