from bottle import request, route, run
from os import environ
from time import asctime, localtime


def htmlify(content):
    page = """
      <!DOCTYPE html>
      <html>
        <head>
          <title>Date and Time</title>
          <meta charset="utf-8" />
        </head>
        <body>
    """ + content + """
        </body>
      </html>
    """
    return page


def time_page():
    zones = request.POST.getall('zones')
    content = ''
    for zone in zones:
        environ['TZ'] = zone
        current_time = localtime()
        content = content + '<p>The current time in ' + zone + ' is: ' + \
                  asctime(current_time) + '</p>\n'
    content = content + '<hr />\n'
    content = content + '<p>Go to the <a href="/">home page</a>.</p>\n'
    return htmlify(content)


def home_page():
    content = """
      <p>Show me the time in:</p>
      <form action="/time" method="POST">
        <input type="checkbox" name="zones" value="Europe/Istanbul" /> Istanbul<br />
        <input type="checkbox" name="zones" value="Pacific/Auckland" /> Auckland<br />
        <input type="checkbox" name="zones" value="Europe/London" /> London<br />
        <input type="checkbox" name="zones" value="Europe/Warsaw" /> Warsaw<br />
        <input type="checkbox" name="zones" value="America/New_York" /> New York<br />
        <input type="checkbox" name="zones" value="Asia/Tokyo" /> Tokyo<br />
        <input type="submit" value="Show" />
      </form>
    """
    return htmlify(content)


route('/time', 'POST', time_page)
route('/', 'GET', home_page)

run()
