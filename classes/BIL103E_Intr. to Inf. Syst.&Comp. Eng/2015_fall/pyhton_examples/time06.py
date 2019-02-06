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
    area = request.POST.get('area')
    city = request.POST.get('city')
    environ['TZ'] = area + '/' + city
    current_time = localtime()
    content = '<p>The current time in ' + city + ' is: ' + \
              asctime(current_time) + '</p>\n'
    content = content + '<hr />\n'
    content = content + '<p>Go to the <a href="/">home page</a>.</p>\n'
    return htmlify(content)


def home_page():
    content = """
      <p>Show me the time in:</p>
      <form action="/time" method="POST">
        Area:
          <select name="area">
            <option value="Africa">Africa</option>
            <option value="America">America</option>
            <option value="Asia">Asia</option>
            <option value="Europe">Europe</option>
            <option value="Pacific">Pacific</option>
          </select><br />
        City: <input type="text" name="city" /><br />
        <input type="submit" value="Show" />
      </form>
    """
    return htmlify(content)


route('/time', 'POST', time_page)
route('/', 'GET', home_page)

run()
