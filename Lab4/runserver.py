# -*- coding: utf-8 -*-

from app import app
from app import database
from flask import render_template, request
from models import *
from playhouse.flask_utils import get_object_or_404

@app.route("/")
def hello():
    return "Hello, World!"

@app.route("/login")
def login():
    provider = request.args.get("provider")
    if provider == 'google':
        return "Hello, Google!"
    return render_template('login.html')

#@app.route("/login")
#@app.route("/login?provider=<provider>")
#def login(provider = None):
#    if provider == 'google':
#        return "Hello, Google!"
#    return render_template('login.html')

@app.route("/create/<nickname>-<social_id>")
def create(nickname, social_id):
    user = User.create(nickname=nickname,social_id=social_id)
    return "<h1>{}</h1>".format(user.nickname)

@app.route("/read/<social_id>")
def read(social_id):
    user = get_object_or_404(User.select(), User.social_id==social_id)
    return "<h1>{}</h1>".format(user.nickname)

def main():
    database.create_tables([User, Feed], safe=True)
    app.run()

if __name__ == "__main__":
    main()