# -*- coding: utf-8 -*-

import feedparser

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

@app.route("/delete_feed")
def delete_feed():
    return "Miameee"

@app.route("/new_feed", methods=['GET', 'POST'])
@login_required
def new_feed():
    import ipdb; ipdb.set_trace()
    if request.method == 'POST':
        url = request.form['feed_url']
        d = feedparser.parse(url)
        feed = Feed.select().where(Feed.url == url)
        if len(feed) == 0:
            feed = Feed.create(url = url, title = d['feed']['title'], description = d['feed']['subtitle'], user = current_user.id)
            return render_template('index.html')

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

@app.route("/rss")
def rss():
    return "Miameee"

def main():
    database.create_tables([User, Feed], safe=True)
    app.run()

if __name__ == "__main__":
    main()