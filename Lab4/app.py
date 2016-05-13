# -*- coding: utf-8 -*-

import settings

from flask import Flask
from flask import render_template

app = Flask(__name__)
app.config.from_object(settings)

@app.route("/login")
def login():
    return render_template('login.html')

@app.route("/index")
def index():
    current_user = "not"
    return render_template('index.html')

if __name__ == "__main__":
    app.run()