from bottle import  debug, route, run
from random import randrange

def coins_page():
	num = randrange(1, 3)
	if num == 1:
		return "Yazı"
	else:
		return "Tura"

def dice_page():
	num = randrange(1, 7)
	return str(num)
	
def dice2_page():
	num1 = randrange(1, 7)
	num2 = randrange(1, 7)
	num3 = randrange(1, 7)
	num4 = randrange(1, 7)
	num5 = randrange(1, 7)
	return str(num1) + " " + str(num2) + " " + str(num3) + " " + str(num4) + " " + str(num5)

@route('/random')
def random_page():
	num = randrange(1, 7)
	return "Your Number is " + str(num)

route("/coins", "GET", coins_page)
route("/dice", "GET", dice_page)
route("/dice2", "GET", dice2_page)
route("/random", "GET", random_page)
run(port=9090)




	







