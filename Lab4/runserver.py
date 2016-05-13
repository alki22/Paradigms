# -*- coding: utf-8 -*-

from app import app
from app import database
from models import *

@app.route("/")
def hello():
    return "Hello, World!"

@app.route("/login")
def login():
    return render_template('login.html')

@app.route("/index")
def index():
    current_user = "not"
    return render_template('index.html')

def main():
    database.create_tables([User, Feed], safe=True)
    app.run()

if __name__ == "__main__":
    main()