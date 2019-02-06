 # -*- coding: utf-8 -*-

#######################################################
### Please ignore the following lines of code.
### It loads the contents of a CSV file for you.
### The file's name should be a2_input.csv.
### You do NOT need to know how it works.
#######################################################

import csv

contents = []
with open("a2_input.csv") as input_file:
    for row in csv.reader(input_file):
        contents = contents + [row]

#######################################################
### Do your data processing below.
### The below code gives some examples
### of how to access the data.
### Print your results using the print function.
#######################################################

#HTML Formalities#
print('<!DOCTYPE html>\n<html>\n  <head>\n    <meta charset="utf-8">\n    <title>Assignment 2 Step 3</title>\n  </head>')

#HTML Body#
print('<body>\n')

#####STEP 4 ####
print("<h1>Here's my data:</h1>")
print('<table style="border:dotted">')
for i in contents:
	print('<tr>')
	for j in i:
		print('<td style="border:solid">'+j+"</td>")
	print("</tr>")
print("</table>")

##Countif
CarCounter=0
for i in range(3,len(contents)):
	if contents[i][7]=='x':
		CarCounter+=1


print("<h1>Here some info about my data file:</h1>")

#####STEP 3 ####
print("<h2>Source of the data(First Row):</h2>")
print("<p>")
print(contents[0])
print("</p>")
print("<h2>First cell (Again source of the data):</h2>")
print("<p>")
print(contents[0][0])
print("</p>")
print("<h2>"+contents[1][1]+" of the first mesarument:"+"</h2>")
print("<p>")
print(contents[3][1])
print("</p>")
print("<h2> Type of the "+contents[1][2]+" for first mesarument:"+"</h2>")
print("<p>")
if type(contents[3][2]) is str
	print("String")
else:
	print("It's definetly not string")
print("</p>")
sumOfMem=0
counter=0
for i in range(3,len(contents)):
#contents is the list of rows
	temp=contents[i][5]
	if temp != '':
		counter+=1
		sumOfMem+=int(temp)
print("<h2>Summary of mem start:</h2>")
print("<p>")
print(sumOfMem)
print("</p>")
averageOfMem=sumOfMem/counter
print("<h2>Count of mem start:</h2>")
print("<p>")
print(counter)
print("</p>")
print("<h2>Avarage of mem start:</h2>")
print("<p>")
print(averageOfMem)
print("</p>")
print("<h2>Date and coordinate of first mesarument</h2>")
print("<p>")
dateCoordinate=contents[3][1]+' '+contents[3][2]
print(dateCoordinate)
print("</p>")
print("<h2>Number of mesarument in car:</h2>")
print("<p>")
print(CarCounter)
print("</p>")
#print(contents[c][c]) name error
#dateCoordinate+averageOfMem type error
print("<h2>And 3 times of the same date and coordinate, because we need 3 times of the same thing...</h2>")
print("<p>")
print(3*dateCoordinate)
print("</p>")
#dateCoordinate.help() Attribute Error
#averageOfMem.help() Attribute Error
print("<h2> Maybe a little help about date and coordinate</h2>")
print("<p>")
help(dateCoordinate) #no documents found
print("\n oops! looks like we are not getting any help! </p>")
##Body end
print("\n </body>")
#HTML Formalities#
print("\n </html>")