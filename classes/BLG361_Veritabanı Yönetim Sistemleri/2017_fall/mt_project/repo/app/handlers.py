from flask import Blueprint, render_template, current_app, request, redirect, url_for, flash
from app.models.message import Message
from app.models.database import Database
from flask_login import UserMixin
from app.models.adminStuff import adminCommands
from app.models.user import loginOrSignUp
from flask_login import LoginManager
from flask_login import logout_user, current_user
from app.forms import AddMessageForm, LoginForm, AddAnswerForm, ChangePassForm, ChangePictureForm
from app.models.messageAnswer import MessageAnswer
from passlib.apps import custom_app_context as pwd_context

site = Blueprint('site', __name__)

@site.route('/', methods=['GET', 'POST'])
def home_page():
    db = Database()
    form = AddMessageForm()
    answerForm = AddAnswerForm()
    if form.validate_on_submit():
        title = form.data['title']
        text = form.data['text']
        message = Message(title,text)
        message.username = current_user.username
        db.add_message(message)
        flash('message added')
        return redirect(url_for('site.home_page'))
    if answerForm.validate_on_submit():
        text = answerForm.data['text']
        messageId=answerForm.data['messageID']
        db.add_message_answer(MessageAnswer(text,0,current_user.username,messageId))
        flash('answer added')
        return redirect(url_for('site.home_page'))
    messages=db.get_messages()
    messageAnswer=db.get_message_answers()
    return render_template('home.html', answers=messageAnswer, answerForm=answerForm, form=form, messages=messages)

@site.route('/reset')
def reset():
    adminCommands.resetEverything()
    return redirect(url_for('site.home_page'))

@site.route('/dummy')
def dummy():
    adminCommands.insertDummy()
    return redirect(url_for('site.home_page'))

@site.route('/logOut')
def logout():
    logout_user()
    return redirect(url_for('site.home_page'))

@site.route('/profile' , methods=['GET', 'POST'])
def profile_page():
    if current_user.is_authenticated:
        db = Database()
        users = db.get_usernames()
        bestfriend = db.get_bestFriend(current_user.username)
        friends = db.get_friends(current_user.username)
        form = ChangePassForm()
        picForm = ChangePictureForm()
        if form.validate_on_submit():
            hashedPass = pwd_context.encrypt(form.data['password'])
            db.update_pass(current_user.username,hashedPass)
            flash('Updated Password')
        if picForm.validate_on_submit():
            db.change_user_picture(current_user.username,picForm.data['picture'])
            flash('Updated Picture')
        form = ChangePassForm()
        return render_template('profile.html', users=users, form=form, bestfriend=bestfriend, friends=friends, picForm=picForm)
    return redirect(url_for('site.home_page'))

@site.route('/login', methods=['GET', 'POST'])
def login_page():
    db = Database()
    form = LoginForm()
    if form.validate_on_submit() and loginOrSignUp(form):
        flash('login succesfull')
        return redirect(url_for('site.home_page'))
    else:
        print ('fail to sign in')
        return render_template('login.html', form=form)

@site.route('/upAnswer/<int:answer_id>')
def up_answer_page(answer_id):
    if current_user.is_authenticated:
        db=Database()
        db.up_answer(answer_id)
    return redirect(url_for('site.home_page'))

@site.route('/delAnswer/<int:answer_id>')
def del_answer_page(answer_id):
    if current_user.is_admin:
        db=Database()
        db.del_answer(answer_id)
    return redirect(url_for('site.home_page'))

@site.route('/delMessage/<int:message_id>')
def del_message_page(message_id):
    if current_user.is_admin:
        db=Database()
        db.del_message(message_id)
    return redirect(url_for('site.home_page'))

@site.route('/editMessage/<int:message_id>', methods=['GET', 'POST'])
def edit_message_page(message_id):
    if current_user.is_admin:
        form = AddMessageForm()
        db=Database()
        message = db.get_message(message_id)
        if form.validate_on_submit():
            message = Message(form.data['title'], form.data['text'])
            message.id = message_id
            db.edit_message(message)
            flash('message edited')
            return redirect(url_for('site.home_page'))
        return render_template('message.html', form=form, message=message)
    return redirect(url_for('site.home_page'))

@site.route('/editAnswer/<int:answer_id>', methods=['GET', 'POST'])
def edit_answer_page(answer_id):
    if current_user.is_admin:
        form = AddAnswerForm()
        db=Database()
        answer = db.get_message_answer(answer_id)
        print(answer.text)
        if form.validate_on_submit():
            answer = MessageAnswer(form.data['text'])
            answer.id = answer_id
            db.edit_message_answer(answer)
            flash('answer edited')
            return redirect(url_for('site.home_page'))
        return render_template('answer.html', form=form, answer=answer)
    return redirect(url_for('site.home_page'))

@site.route('/delUser/<username>')
def del_user_page(username):
    if current_user.is_admin and username!='admin':
        db=Database()
        db.del_user(username)
    return redirect(url_for('site.home_page'))

@site.route('/adminize/<username>')
def adminize_page(username):
    if current_user.is_admin and username!='admin':
        db=Database()
        db.adminize(username)
    return redirect(url_for('site.home_page'))

@site.route('/addFriend/<username>')
def add_friend_page(username):
    if current_user.is_authenticated:
        db=Database()
        db.set_as_friends(current_user.username,username)
    return redirect(url_for('site.profile_page'))

@site.route('/addBestFriend/<username>')
def add_bestFriend_page(username):
    if current_user.is_authenticated:
        db=Database()
        db.set_as_bestFriends(current_user.username,username)
    return redirect(url_for('site.profile_page'))

@site.route('/removeFriend/<username>')
def remove_friend_page(username):
    if current_user.is_authenticated:
        db=Database()
        db.remove_friendship(current_user.username,username)
    return redirect(url_for('site.profile_page'))
