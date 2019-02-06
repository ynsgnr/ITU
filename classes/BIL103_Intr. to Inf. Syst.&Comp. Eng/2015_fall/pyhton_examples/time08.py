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
      <p>Show the time in:</p>
      <form action="/time" method="POST">
        <select name="zones" multiple size="6">
          <option value="Europe/Istanbul">Istanbul</option>
          <option value="Pacific/Auckland">Auckland</option>
          <option value="Europe/London">London</option>
          <option value="Europe/Warsaw">Warsaw</option>
          <option value="America/New_York">New York</option>
          <option value="Asia/Tokyo">Tokyo</option>
        </select><br />
        <input type="submit" value="Show" />
      </form>
    """
    return htmlify(content)


route('/time', 'POST', time_page)
route('/', 'GET', home_page)

run()
