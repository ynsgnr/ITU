from bottle import route, run
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

def european_time_page(city):
	environ["TZ"] = "Europe/" + city
	current_time = localtime()
	content = "<p>The current time is: " + \
	    asctime(current_time) + "</p>"
	return htmlify(content)	

def world_time_page():
	params = request.POST
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

def time_page():
	current_time = localtime()
	content = '<p>The current time is: ' + city + "is":
		
		asctime(current_time) + "</p>"
	return htmlify(content)
	
def home_page():
	"""
	"<p>Show me the time in:</p>\n"
	<form action="/time" method="POST">
	  Area: <input type="text" name="area" placeholder="Enter Value" /><br />
	  city: <input type="text" name="city" /><br />
	  ABC: <input type="number" name="ABC" value="0" /><br />
	  <input type="submit" value="Show" />
	</form>
	"""
	return htmlify(content)
	
	 	
	
route("/time", "POST", time_page)
route("/european_time/<city>", "GET", european_time_page)
route("/world_time/", "POST", world_time_page)
route("/", "POST", home_page)
run(port=8080)
	
