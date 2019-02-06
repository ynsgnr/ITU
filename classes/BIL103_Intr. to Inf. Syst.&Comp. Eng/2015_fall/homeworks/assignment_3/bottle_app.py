
#####################################################################
### Assignment skeleton
### You can alter the below code to make your own dynamic website.
### The landing page for assignment 3 should be at /assignment3/
#####################################################################

 # -*- coding: utf-8 -*-

from bottle import route, run, default_app, debug, request

names=[]
sexes=[]
votes=[]

def remove_html(text):
    text=text.replace("<","&lt;")
    text=text.replace(">","&gt;")
    return text[:15]

def fix_tr (text):
    text=text.replace("Ä±","ı")
    text=text.replace("Ä°","İ")
    text=text.replace("Ä","ğ")
    text=text.replace("Ä","Ğ")
    text=text.replace("Ã¼","ü")
    text=text.replace("Ã","Ü")
    text=text.replace("Å","ş")
    text=text.replace("Å","Ş")
    text=text.replace("Ã§","ç")
    text=text.replace("Ã","Ç")
    text=text.replace("Ã¶","ö")
    text=text.replace("Ã","Ö")
    return text

def htmlify(title, content):
    page = """<!DOCTYPE html>
              <html>
                <head>
                    <style>
                        table, th, td {
                            border: 1px solid black;
                            border-collapse: collapse;
                        }
                        th, td {
                            padding: 3px;
                        }
                    </style>
                      <title>""" + title + """</title>
                      <meta charset=UTF-8"/>
                  <body>
                      """ + content + """
                  </body>
              </html>"""
    return page

def get_data():
    global names
    for i in range(0,len(names)):
      if not votes[i]:
        votes[i]=0
    return htmlify("Welcome to my website",'''
  <form action="vote" method="GET">
  <input type="text" name="name" Value="Name">
  <br>
  <input type="radio" name="sex" value="male" checked>Male
  <br>
  <input type="radio" name="sex" value="female">Female
  <br>
  <input type="submit" value="Add me">
  </form>
  <p><a href="/vote"> Vote without adding yourself</a></p>''')

def vote():
    global names
    global votes
    global sexes
    name=request.GET.get('name')
    if type(name) is str:
        name=remove_html(name)
        names = names+[fix_tr(name)]
        votes=votes+[0]
        sexes = sexes+[request.GET.get('sex')]
    content =''' <p> Vote for the best person: </p>
      <form action="results" method='POST'>
      '''
    for i in range(0,len(names)):
        content=content+'<input type="checkbox" name="vote" value="'
        content+=str(i)+'">'+names[i]+'|'+sexes[i]+'<br>'
    return htmlify("Your id",content+'''<input type="submit" value="Vote">
    </form>
    <p><a href=../assignment3/>Go back!</a></p>''')

def results ():
    global names
    global sexes
    vote=request.POST.getall('vote')
    for v in vote:
      votes[int(v)]+=1
    content='''<p> Thanks for voting!<p>
    <p> Results: </p>
    <table>
    <tr style="border:1px solid black">
      <td>Name</td>
      <td>Sex</td>
      <td>Votes</td>
    </tr>'''
    vote_counter=0
    i=0
    for i in range(0,len(names)):
        vote_counter+=votes[i]
        content=content+'''
      <tr>
        <td>'''+names[i]+'''</td>
        <td>'''+sexes[i]+'''</td>
        <td>'''+str(votes[i])+'''</td>
      </tr>'''
    average=vote_counter/(i+1)
    content=content+'''</table>
    <p>Average is:'''+str(average)+'</p>'
    return htmlify ("Your info",content+'''
    <p><a href=../assignment3/>Go back!</a></p>''')

def website_index():
    return htmlify('My lovely homepage',
                   """
                   <p><a href="/assignment1/">Click for my assignment 1.</a></p>
                   <p><a href="/assignment2/a2_output.html">Click for my assignment 2.</a></p>
                   <p><a href="/assignment3/">Click for my assignment 3.</a></p>
                   """)

route('/assignment3/', 'GET', get_data)
route('/assignment3', 'GET', get_data)
route('/', 'GET', website_index)
route('/assignment3/vote','GET', vote)
route('/vote','GET', vote)
route('/assignment3/results','POST', results)
route('/assignment3/results','GET', results)
route('/results','POST', results)
#####################################################################
### Don't alter the below code.
### It allows this website to be hosted on PythonAnywhere
### OR run on your computer.
#####################################################################

# This line makes bottle give nicer error messages
debug(True)
# This line is necessary for running on PythonAnywhere
application = default_app()
# The below code is necessary for running this bottle app standalone on your computer.
if __name__ == "__main__":
  run()