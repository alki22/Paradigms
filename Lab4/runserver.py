# -*- coding: utf-8 -*-

import feedparser
from flask import render_template, request, redirect, url_for, session, flash
from flask.ext.login import logout_user, current_user, \
    login_required, login_user

from app import app, database
from auth import login_github, github, login_google, google, login_facebook, facebook
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
    elif provider == 'facebook':
        return login_facebook()
    return render_template('login.html')


@app.route('/login/authorized/<provider>')
def authorized(provider):
    if provider == 'github':
        resp = github.authorized_response()
    elif provider == 'google':
        resp = google.authorized_response()
    elif provider == 'facebook':
        resp = facebook.authorized_response()

    if resp is None:
        flash('Sign in denied.')
        return redirect(url_for('login'))

    access_token = resp['access_token']
    session['oauth_token'] = (access_token, '')

    if provider == 'github':
        user_info = github.get('/user')
        user_email = github.get('/user/emails').data[0]['email']
        user_id = user_info.data['login']
        user_name = user_info.data['name']
    elif provider == 'google':
        user_info = google.get('userinfo')
        user_email = user_info.data['email']
        user_id = user_info.data['email']
        user_name = user_info.data['name']
    elif provider == 'facebook':
        user_info = facebook.get('me?fields=id,email,name')
        user_email = user_info.data['email']
        user_id = user_info.data['id']
        user_name = user_info.data['name']

    # Check if user already exists, if it doesn't, create it.
    user = User.select().where(User.social_id == user_id)
    if len(user) == 0:
        user = User.create(nickname=user_name,
                           social_id=user_id,
                           email=user_email)
    else:
        user = user[0]

    login_user(user, True)

    return redirect(url_for('index'))


@app.route("/logout")
def logout():
    if current_user.is_authenticated:
        logout_user()
    return redirect(url_for('login'))


@app.route("/new_feed", methods=['GET', 'POST'])
@login_required
def new_feed():
    if request.method == 'POST':
        url = request.form['feed_url']
        d = feedparser.parse(url)

        feeds = Feed.select().where(Feed.user == current_user.id)
        has_feed = False
        for feed in feeds:
            if feed.url == url:
                has_feed = True

        if not has_feed:
            title = d['feed']['title']
            description = d['feed']['description']
            if description == '':
                description = d['feed']['subtitle']

            Feed.create(url=url, title=d['feed']['title'],
                        description=d['feed']['description'],
                        user=current_user.id)
            return redirect(url_for('index'))
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
