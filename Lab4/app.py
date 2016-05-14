# -*- coding: utf-8 -*-

import settings

from flask import Flask
from playhouse.flask_utils import FlaskDB

app = Flask(__name__)
app.config.from_object(settings)

flask_db = FlaskDB(app)
database = flask_db.database
