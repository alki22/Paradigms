# -*- coding: utf-8 -*-

import settings

from flask import Flask
from playhouse.flask_utils import FlaskDB
from flask.ext.login import LoginManager

app = Flask(__name__)
app.config.from_object(settings)

flask_db = FlaskDB(app)
database = flask_db.database

login_manager = LoginManager()
login_manager.init_app(app)
