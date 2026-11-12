
from flask import Flask, render_template, request
from tf2ss import tf2ss

app = Flask(__name__)


@app.route("/")
def inicio():
    return render_template("index.html")


@app.route("/herramienta", methods=["GET", "POST"])
def herramienta():
    matrices = None
    error = None

    if request.method == "POST":
        try:
            num = [
                float(x.strip())
                for x in request.form["num"].split(",")
            ]

            den = [
                float(x.strip())
                for x in request.form["den"].split(",")
            ]

            A, B, C, D = tf2ss(num, den)

            matrices = {
                "A": A.tolist(),
                "B": B.tolist(),
                "C": C.tolist(),
                "D": D.tolist(),
            }

        except (ValueError, KeyError) as e:
            error = str(e) or "Revisa los coeficientes introducidos."

    return render_template(
        "herramienta.html",
        matrices=matrices,
        error=error,
    )


if __name__ == "__main__":
    app.run(debug=True)
