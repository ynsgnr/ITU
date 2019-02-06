from bottle import route, run

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
	       
def hello_page():
	content = '<h1>hello, page</h1>\n'
	content = content + '<p><a href="/goodbye">Go out.</a></p>'
	return htmlify(content)
    
def goodbye_page():
	content = "<h1>Goodbye, page!</h1>"
	content = content + '<p><a href="/hello">Go back.</a></p>'
	return htmlify(content)
    
route("/hello", "GET", hello_page)
route("/goodbye", "GET", goodbye_page)
run(port=8081)
