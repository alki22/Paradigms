# -*- coding: utf-8 -*-

from flask import url_for, session, request
from flask_oauthlib.client import OAuth

from app import app, login_manager
from models import *

oauth = OAuth(app)

logged_user = None

## Credentials

FACEBOOK_CLIENT_ID = '1635647113427550'
FACEBOOK_CLIENT_SECRET = '2875d46f86d7f4d0334dfd268d11ed6d'
GITHUB_CLIENT_ID = '6a39f5c1520738d60f5d'
GITHUB_CLIENT_SECRET = '12429b0eeb2c3a53e17e9129e8fead61a9237c75'
GOOGLE_CLIENT_ID = '226116028155-s550d589j2ksikls2c5ogcun72ijr3g4.apps.googleusercontent.com'
GOOGLE_CLIENT_SECRET = 'sXxb7s0tsXKmPswFyfywaHJw'


## Flask-Login

@login_manager.user_loader
def load_user(uid):
    try:
        return User.get(User.id == uid)
    except User.DoesNotExist:
        session.clear()
        return AnonymousUser()


## Facebook's OAuth

facebook = oauth.remote_app(
    'facebook',
    consumer_key=FACEBOOK_CLIENT_ID,
    consumer_secret=FACEBOOK_CLIENT_SECRET,
    request_token_params={'scope': 'email'},
    base_url='https://graph.facebook.com/',
    request_token_url=None,
    access_token_method='GET',
    access_token_url='/oauth/access_token',
    authorize_url='https://www.facebook.com/dialog/oauth'
)


@facebook.tokengetter
def get_facebook_token(token=None):
    return session.get('oauth_token')


def login_facebook():
    callback = url_for(
        'authorized',
        next=request.args.get('next') or request.referrer or None,
        provider='facebook',
        _external=True
    )
    return facebook.authorize(callback=callback)


## Github's OAuth

github = oauth.remote_app(
    'github',
    consumer_key=GITHUB_CLIENT_ID,
    consumer_secret=GITHUB_CLIENT_SECRET,
    request_token_params={'scope': 'user:email'},
    base_url='https://api.github.com/',
    request_token_url=None,
    access_token_method='POST',
    access_token_url='https://github.com/login/oauth/access_token',
    authorize_url='https://github.com/login/oauth/authorize'
)


@github.tokengetter
def get_github_token(token=None):
    return session.get('oauth_token')


def login_github():
    return github.authorize(
        callback=url_for('authorized', provider='github', _external=True))


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
def get_google_token(token=None):
    return session.get('oauth_token')


def login_google():
    return google.authorize(
        callback=url_for('authorized', provider='google', _external=True))
