# -*- coding: utf-8 -*-

from flask import session

github = oauth.remote_app('github',...)

@github.tokengetter
def get_github_token(token=None):
    return session.get('github_token')