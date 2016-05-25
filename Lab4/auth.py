# -*- coding: utf-8 -*-

from flask import url_for, session
from flask_oauthlib.client import OAuth

from app import app, login_manager
from models import *

oauth = OAuth(app)

logged_user = None

## Credentials

GOOGLE_CLIENT_ID='398696822913-li49jael4ks916e4rdd28jh7uir9mh71.apps.googleusercontent.com'
GOOGLE_CLIENT_SECRET='FggQmkRIkOsiZQIt0ITLiEiN'

## Flask-Login

@login_manager.user_loader
def load_user(uid):
    try:
        return User.get(User.id == uid)
    except User.DoesNotExist:
        session.clear()
        return AnonymousUser()


## Github's OAuth

github = oauth.remote_app(
    'github',
    consumer_key='6a39f5c1520738d60f5d',
    consumer_secret='12429b0eeb2c3a53e17e9129e8fead61a9237c75',
    request_token_params={'scope': 'user:email'},
    base_url ='https://api.github.com/',
    request_token_url=None,
    access_token_method='POST',
    access_token_url='https://github.com/login/oauth/access_token',
    authorize_url='https://github.com/login/oauth/authorize'
)


@github.tokengetter
def get_github_token(token=None):
    return session.get('github_token')


def login_github():
    return github.authorize(
        callback=url_for('authorized_github', _external=True))


## Google's OAuth

google = oauth.remote_app(
    'google',
    base_url='https://www.googleapis.com/oauth2/v1/',
    authorize_url='https://accounts.google.com/o/oauth2/auth',
    request_token_url=None,
    request_token_params={'scope': 'https://www.googleapis.com/auth/userinfo.email'},
    access_token_url='https://accounts.google.com/o/oauth2/token',
    access_token_method='POST',
    consumer_key=GOOGLE_CLIENT_ID,
    consumer_secret=GOOGLE_CLIENT_SECRET
)

@google.tokengetter
def get_google_token(token = None):
    return session.get('google_token')

def login_google():
    return google.authorize(
        callback = url_for('authorized_google', _external=True))

    
