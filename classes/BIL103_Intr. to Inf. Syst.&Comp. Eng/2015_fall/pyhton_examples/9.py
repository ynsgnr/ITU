from bottle import debug, route, run, request
from time import localtime, asctime
from os import environ

def htmlify(content):
	page = """
	 <!DOCTYPE html>
	 <html>
	   <head>
	     <title>Hello</title>
	     <meta charset="utf-8" />
	   </head>
	   <body>
	""" + content + """
	  </body>
	</html>
"""
	return page
	
def time_page():
	params = request.GET
	zones = params.getall("zones")
	content = ""
	for zone in zones:
		environ["TZ"] = zones
		current_time = localtime()
		content = content + "<p>The current time in " + zones + " is: " +
            asctime(current_time) + "</p>\n"
	content = content + "<hr />\n"
	return htmlify(content)

def get_time_in_zone(area, city):
	if "TZ" in environ:
		original_tz = environ["TZ"]
		



def home_page():
	content = """
	<p>Show me the time in:</p>\n
	<form action="/time" method="GET">
	  <select name="zones" multiple size="6">
	    <option value="Europe/Istanbul">Istanbul</option>
	    <option value="Europe/London">London</option>
	    <option value="America/New York">New York</option>
	  <input type="submit" value="Show" />
	</form>
	"""
	return htmlify(content)

debug(True)
route("/time", "GET", time_page)
route("/", "GET", home_page)
run(port=8080)
	
