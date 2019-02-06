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

print("This assignment (assignment 2) hasn't been finished.")
print("All it can do is print out the contents of a couple of cells of the file a2_input.csv:")
print("Cell at index 0,0:")
print(contents[0][0])
print("Cell at index 0,1:")
print(contents[0][1])
print("Cell at index 1,0:")
print(contents[1][0])
