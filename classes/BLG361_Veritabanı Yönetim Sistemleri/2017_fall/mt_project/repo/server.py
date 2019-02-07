import datetime
import os
import json
import re

from flask import Flask

from app.handlers import site
from flask_login import LoginManager
from app.models.user import get_user


def get_elephantsql_dsn(vcap_services):
    """Returns the data source name for ElephantSQL."""
    parsed = json.loads(vcap_services)
    uri = parsed["elephantsql"][0]["credentials"]["uri"]
    match = re.match('postgres://(.*?):(.*?)@(.*?)(:(\d+))?/(.*)', uri)
    user, password, host, _, port, dbname = match.groups()
    dsn = """user='{}' password='{}' host='{}' port={}
             dbname='{}'""".format(user, password, host, port, dbname)
    return dsn

lm = LoginManager()

@lm.user_loader
def load_user(user_id):
    return get_user(user_id)

if __name__ == '__main__':
    #create app
    app=Flask(__name__)
    app.register_blueprint(site)

    #add database connection
    VCAP_APP_PORT = os.getenv('VCAP_APP_PORT')
    if VCAP_APP_PORT is not None:
        port, debug = int(VCAP_APP_PORT), False
    else:
        port, debug = 5000, True

    VCAP_SERVICES = os.getenv('VCAP_SERVICES')
    if VCAP_SERVICES is not None:
        app.config['dsn'] = get_elephantsql_dsn(VCAP_SERVICES)
    else:
        app.config['dsn'] = """user='vagrant' password='vagrant'
                               host='localhost' port=54321 dbname='itucsdb'"""

    app.config['SECRET_KEY'] = 'ksdgnmksjdgnmksnd'
    app.config['WTF_CSRF_ENABLED'] = True

    lm.init_app(app)
    lm.login_view = 'site.login'

    #run app
    app.run(host='0.0.0.0', port=port, debug=debug)
