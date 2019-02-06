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

def world_time_page(area, city):
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
	content = '<p>The current time is: ' + \
		asctime(current_time) + "</p>"
	return htmlify(content)
	
def home_page():
	content = "<p>Show me the time in:</p>\n"
	content = content + "<ul>"
	content = content + ' <li><a href="/world_time/America/SanFrancisco">San Francisco</a></li>'
	content = content + ' <li><a href="/world_time/Europe/Paris">Paris</a></li>'
	content = content + "</ul>"
	return htmlify(content)
	
	 	
	
route("/time", "GET", time_page)
route("/european_time/<city>", "GET", european_time_page)
route("/world_time/<area>/<city>", "GET", world_time_page)
route("/", "GET", home_page)
run(port=8080)
	
	

