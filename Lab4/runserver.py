# -*- coding: utf-8 -*-

from app import app, database
from auth import *
from flask import render_template, request
from models import *
from playhouse.flask_utils import get_object_or_404

@app.route("/")
def hello():
    return "Hello, World!"

# Capaz(?)
@app.route("/logout")
def logout():
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
def new_feed():
    return render_template('newfeed.html')

@app.route("/index")
def index():
    import ipdb; ipdb.set_trace()
    social_id = request.args.get("social_id")
    current_user = User.select().where(User.social_id == social_id).get()
    return render_template('index.html', current_user=current_user)

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