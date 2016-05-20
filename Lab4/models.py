# -*- coding: utf-8 -*-

from flask_login import UserMixin, AnonymousUserMixin
from peewee import *

from app import flask_db


class AnonymousUser(AnonymousUserMixin):
    pass


class User(flask_db.Model, UserMixin):
    id = PrimaryKeyField()
    social_id = CharField(null=False, unique=True)
    nickname = CharField(null=False)
    email = CharField(null=True)

    def is_authenticated(self):
        return True


class Feed(flask_db.Model):
    id = PrimaryKeyField()
    user = ForeignKeyField(User, related_name='feeds')
    title = CharField()
    url = CharField()
    description = CharField()


