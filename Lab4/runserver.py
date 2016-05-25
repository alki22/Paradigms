# -*- coding: utf-8 -*-

import feedparser
from flask import render_template, request, redirect, url_for, session
from flask.ext.login import logout_user, current_user, \
    login_required, login_user

from app import app, database
from auth import login_github, github, login_google, google
from models import *


@app.route("/")
def root():
    if current_user.is_authenticated:
        return redirect(url_for('index'))
    else:
        return redirect(url_for('login'))


@app.route("/delete_feed")
@login_required
def delete_feed():
    feed_id = request.args.get('feed')
    feed = Feed.get(Feed.id == feed_id)
    feed.delete_instance()
    return redirect(url_for('index'))


@app.route("/index")
@login_required
def index():
    return render_template('index.html')


@app.route("/login")
def login():
    provider = request.args.get('provider')
    if provider == 'google':
        return login_google()
    elif provider == 'github':
        return login_github()
    return render_template('login.html')


@app.route('/login/authorized_github')
def authorized_github():
    resp = github.authorized_response()
    if resp is None:
        return 'Access denied: reason=%s error=%s' % (
            request.args['error'],
            request.args['error_description']
        )
    session['github_token'] = (resp['access_token'], '')
    me = github.get('user')

    # Check if user already exists, if it doesn't, create it.
    user = User.select().where(User.social_id == me.data['login'])
    if len(user) == 0:
        user = User.create(nickname=me.data['name'],
                           social_id=me.data['login'])
    else:
        user = user[0]

    login_user(user, True)

    return redirect(url_for('index'))

@app.route('/login/authorized_google')
def authorized_google():
    resp = google.authorized_response()
    if resp is None:
        return 'Access denied: reason=%s error=%s' % (
            request.args['error'],
            request.args['error_description']
        )
    session['google_token'] = (resp['access_token'], '')
    me = google.get('userinfo')
    
    
    user = User.select().where(User.social_id == me.data['email'])
    if len(user) == 0:
        user = User.create(nickname=me.data['name'],
                           social_id=me.data['email'])
    else:
        user = user[0]

    login_user(user, True)

    return redirect(url_for('index'))

@app.route("/logout")
@login_required
def logout():
    logout_user()
    return redirect(url_for('login'))


@app.route("/new_feed", methods=['GET', 'POST'])
@login_required
def new_feed():
    if request.method == 'POST':
        url = request.form['feed_url']
        d = feedparser.parse(url)
        feed = Feed.select().where(Feed.url == url)
        if len(feed) == 0:
            Feed.create(url=url, title=d['feed']['title'],
                        description=d['feed']['description'],
                        user=current_user.id)
            return render_template('index.html')
        else:
            return render_template('newfeed.html',
                                   error_message='Feed is already present!')
    else:
        return render_template('newfeed.html')


@app.route("/rss")
@login_required
def rss():
    feed_id = request.args.get('feed')
    feed = Feed.get(Feed.id == feed_id)
    d = feedparser.parse(feed.url)
    return render_template('rss.html', entries=d.entries, feed=feed)


def main():
    database.create_tables([User, Feed], safe=True)
    app.run()


if __name__ == "__main__":
    main()
