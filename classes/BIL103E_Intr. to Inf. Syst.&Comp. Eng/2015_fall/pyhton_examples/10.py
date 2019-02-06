from bottle import static_file, debug, route, run, request
from time import localtime, asctime
from os import environ

def htmlify(content):
	page = """
	 <!DOCTYPE html>
	 <html>
	   <head>
	     <title>Hello</title>
	     <meta charset="utf-8" />
	     <link rel="stylesheet" href="/static/custom.css" />
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
		environ["TZ"] = zone
		current_time = localtime()
		content = content + "<p>The current time in " + zone + " is: " + \
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
	    <input type="checkbox" name="zones" value="Europe/Istanbul">Istanbul<br />
	    <input type="checkbox" name="zones" value="Europe/London">London<br />
	    <input type="checkbox" name="zones" value="America/New York">New York<br />
	    <input type="checkbox" name="zones" value="Africa/Nairobi">Nairobi<br />
	    <input type="checkbox" name="zones" value="America/Chicago">Chicago<br />
	    <input type="checkbox" name="zones" value="America/Seattle">Seattle<br />
	    <input type="checkbox" name="zones" value="America/Philadelphia">Philadelphia<br />	    
	  <input type="submit" value="Show" />
	</form>
	"""
	return htmlify(content)

def server_static(path):
	return static_file(path, root="static")


debug(True)
route("/static/<path>", "GET", server_static)
route("/time", "GET", time_page)
route("/", "GET", home_page)
run(port=8080)
