from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, HiddenField
from wtforms.validators import DataRequired


class AddMessageForm(FlaskForm):
    #add maximum lenght
    title = StringField('Title',validators=[
            DataRequired(),
    ])

    text = StringField('Text',validators=[
            DataRequired(),
    ])

class LoginForm(FlaskForm):

    username = StringField('User Name',validators=[
        DataRequired(),
    ])

    password = PasswordField('Password',validators=[
        DataRequired(),
    ])

    addUser = HiddenField('Add user',validators=[
        DataRequired(),
    ])

class AddAnswerForm(FlaskForm):

    text = StringField('Text',validators=[
            DataRequired(),
    ])

    messageID = HiddenField('Message ID',validators=[
        DataRequired(),
    ])

class ChangePassForm(FlaskForm):

    password = PasswordField('Password',validators=[
        DataRequired(),
    ])

class ChangePictureForm(FlaskForm):

    picture = StringField('Picture',validators=[
        DataRequired(),
    ])
