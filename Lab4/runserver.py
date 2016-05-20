# -*- coding: utf-8 -*-

from app import app, database, login_manager
from auth import *
from flask import render_template, request, session
from models import *
from playhouse.flask_utils import get_object_or_404
from flask.ext.login import login_user, logout_user, current_user, login_required


@app.route("/")
def hello():
    return "Hello, World!"

# Capaz(?)
@app.route("/logout")
@login_required
def logout():
    logout_user()
    return redirect(url_for('login'))

@app.route("/login")
def login():
    provider = request.args.get("provider")
    if provider == 'google':
        return 'Hello, Google!'
    elif provider == 'github':
        return login_github()
    return render_template('login.html')

@app.route("/new_feed")
@login_required
def new_feed():
    return render_template('newfeed.html')

@app.route("/index")
@login_required
def index():
    # index uses current_user.
    return render_template('index.html')

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