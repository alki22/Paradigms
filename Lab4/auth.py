# -*- coding: utf-8 -*-

from flask import Flask, redirect, url_for, session, request, jsonify
from flask_oauthlib.client import OAuth
from app import app, login_manager
from models import *
from flask.ext.login import login_user, logout_user, current_user, login_required

oauth = OAuth(app)

logged_user = None

## Flask-Login

@login_manager.user_loader
def load_user(uid):
    try:
        return User.get(User.id == uid)
    except User.DoesNotExist:
        session.clear()
        return AnonymousUser()


## OAuth Github
# usa la aplicación registrada a nombre de Ignacio
github = oauth.remote_app(
    'github',
    consumer_key='6a39f5c1520738d60f5d',
    consumer_secret='12429b0eeb2c3a53e17e9129e8fead61a9237c75',
    request_token_params={'scope': 'user:email'},
    base_url='https://api.github.com/',
    request_token_url=None,
    access_token_method='POST',
    access_token_url='https://github.com/login/oauth/access_token',
    authorize_url='https://github.com/login/oauth/authorize'
)

@github.tokengetter
def get_github_token(token=None):
    return session.get('github_token')

def login_github():
    return github.authorize(callback=url_for('authorized', _external=True))

@app.route('/login/authorized')
def authorized():
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
        user = User.create(nickname = me.data['name'], social_id = me.data['login'])
    else:
        user = user[0]

    login_user(user, True)

    return redirect(url_for('index'))
