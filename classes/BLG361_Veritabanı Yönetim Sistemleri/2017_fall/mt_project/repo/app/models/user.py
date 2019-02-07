from flask import current_app
from flask_login import UserMixin
from app.models.database import Database
from passlib.apps import custom_app_context as pwd_context
from flask_login import LoginManager, login_user

class User(UserMixin):
    def __init__(self, username):
        self.username = username
        self.active = True
        self.is_admin = False
        self.picture = 'https://www.wired.com/wp-content/uploads/2015/11/GettyImages-134367495.jpg'

    def get_id(self):
        return self.username

    @property
    def is_active(self):
        return self.active

def loginOrSignUp(form):
    db = Database()
    username=form.data['username']
    password=form.data['password']
    #get hashed pass from db
    hashedPass=db.get_user_pass(username)
    if (hashedPass):
        if(pwd_context.verify(password,hashedPass)):
            #login
            user = get_user(username)
            login_user(user)
            form.errors['username'] = 'Login succesfull'
            return True
        else:
            form.errors['password'] = 'Wrong password'
            return False
    else:
        form.errors['noUser'] = 'No user found please press sign up to add user or go back for trying again'
        if (form.data['addUser']=='true'):
            hashedPass=pwd_context.encrypt(password)
            result=db.add_user(username,hashedPass);
            #login user
            user = get_user(username)
            login_user(user)
            return True
    return False

def get_user(username):
    db = Database()
    userArray = db.get_user(username)
    user = None
    if len(userArray)==1:
        user=User(username)
        if(len(userArray[0])<=2 or userArray[0][2]==None):
            user.is_admin=True #old database, allow reset
        else:
            user.is_admin = userArray[0][2]
        if(len(userArray[0])>=4):
            user.picture = userArray[0][3]
    elif(len(userArray)<1):
        user=User('vita')
        user.is_admin=True #no user, allow reset
    return user
