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
	area = params["area"]
	city = params["city"]
	environ["TZ"] = area + "/" + city
	current_time = localtime()
	content = "<p>The current time in " + city + " is: " + \
	    asctime(current_time) + "</p>"
	return htmlify(content)

def get_time_in_zone(area, city):
	if "TZ" in environ:
		original_tz = environ["TZ"]
		



def home_page():
	content = """
	<p>Show me the time in:</p>\n
	<form action="/time" method="GET">
	  Area:
	  <select name="area">
	    <option value="Africa">Africa</option>
	    <option value="America" selected="selected">America</option>
	    <option value="Europe">Europe</option>  
	  </select>
	  city: <input type="text" name="city" placeholder="Enter City" /><br />
	  <input type="submit" value="Show" />
	</form>
	"""
	return htmlify(content)

debug(True)
route("/time", "GET", time_page)
route("/", "GET", home_page)
run(port=8080)
	
