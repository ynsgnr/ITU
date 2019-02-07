import psycopg2 as dbapi2
from flask import current_app
from passlib.apps import custom_app_context as pwd_context
from flask_login import current_user, logout_user

class adminCommands:
    def resetEverything():
        if not current_user.is_anonymous and current_user.is_admin:
            with dbapi2.connect(current_app.config['dsn']) as connection:
                cursor = connection.cursor()

                query = "DROP TABLE IF EXISTS ANSWERS"
                cursor.execute(query)

                query = "DROP TABLE IF EXISTS MESSAGES"
                cursor.execute(query)

                query = "DROP TABLE IF EXISTS FRIENDS"
                cursor.execute(query)

                query = "DROP TABLE IF EXISTS USERS"
                cursor.execute(query)

                query = "CREATE TABLE USERS (USERNAME VARCHAR(50) PRIMARY KEY,PASS VARCHAR(120), ISADMIN BOOLEAN DEFAULT FALSE, PICTURE VARCHAR(500) DEFAULT 'https://www.wired.com/wp-content/uploads/2015/11/GettyImages-134367495.jpg', BESTFRIEND VARCHAR(50) REFERENCES USERS(USERNAME) ON DELETE SET DEFAULT DEFAULT 'admin')"
                cursor.execute(query)

                query = "CREATE TABLE MESSAGES (ID SERIAL PRIMARY KEY,TITLE VARCHAR(50),CONTENT VARCHAR(500), USERNAME VARCHAR(50) REFERENCES USERS(USERNAME) ON DELETE CASCADE)"
                cursor.execute(query)

                query = "CREATE TABLE ANSWERS (ID SERIAL PRIMARY KEY, MESSAGE_ID INTEGER REFERENCES MESSAGES(ID) ON DELETE CASCADE , USERNAME VARCHAR(50) REFERENCES USERS(USERNAME) ON DELETE CASCADE, CONTENT VARCHAR(500), VOTES INTEGER DEFAULT 0)"
                cursor.execute(query)

                query = "CREATE TABLE FRIENDS (USERNAME VARCHAR(50) REFERENCES USERS(USERNAME) ON UPDATE CASCADE, FRIEND VARCHAR(50) REFERENCES USERS(USERNAME) ON UPDATE CASCADE)"
                cursor.execute(query)

                hashedPass = pwd_context.encrypt('admin')
                query = "INSERT INTO USERS (USERNAME,PASS,ISADMIN) VALUES (%s, %s, %s)"
                cursor.execute(query,('admin',hashedPass,True))

                connection.commit()
                logout_user()

    def insertDummy():
        if not current_user.is_anonymous and current_user.is_admin:
            with dbapi2.connect(current_app.config['dsn']) as connection:
                cursor = connection.cursor()

                hashedPass = pwd_context.encrypt('123456')
                query = "INSERT INTO USERS (USERNAME,PASS,ISADMIN) VALUES (%s, %s, %s)"
                cursor.execute(query,('mayk',hashedPass,False))

                hashedPass = pwd_context.encrypt('123456')
                query = "INSERT INTO USERS (USERNAME,PASS,ISADMIN, PICTURE) VALUES (%s, %s, %s, %s)"
                cursor.execute(query,('clark',hashedPass,False,'http://ishowmy.support/img/user-icon-360x360.jpg'))

                query = "INSERT INTO MESSAGES (TITLE,CONTENT,USERNAME) VALUES (%s, %s, %s)"
                cursor.execute(query,('Lorem','Lorem Ipsum Dolor Sit Amel','mayk'))

                query = "INSERT INTO MESSAGES (TITLE,CONTENT,USERNAME) VALUES (%s, %s, %s)"
                cursor.execute(query,('Tryouts','I am trying this so deal with it','admin'))

                query = "INSERT INTO ANSWERS (MESSAGE_ID,USERNAME,CONTENT,VOTES) VALUES (%s, %s, %s, %s)"
                cursor.execute(query,('2','mayk','okay dude', '5'))

                query = "INSERT INTO ANSWERS (MESSAGE_ID,USERNAME,CONTENT,VOTES) VALUES (%s, %s, %s, %s)"
                cursor.execute(query,('2','clark','okay dude', '1'))

                query = "INSERT INTO MESSAGES (TITLE,CONTENT,USERNAME) VALUES (%s, %s, %s)"
                cursor.execute(query,('Amel','Questionare del malific','clark'))

                query = "INSERT INTO ANSWERS (MESSAGE_ID,USERNAME,CONTENT,VOTES) VALUES (%s, %s, %s, %s)"
                cursor.execute(query,('3','mayk','lorem ipsum dolar', '2'))

                query = "INSERT INTO ANSWERS (MESSAGE_ID,USERNAME,CONTENT,VOTES) VALUES (%s, %s, %s, %s)"
                cursor.execute(query,('3','admin','hello buddy', '3'))

                query = "INSERT INTO ANSWERS (MESSAGE_ID,USERNAME,CONTENT,VOTES) VALUES (%s, %s, %s, %s)"
                cursor.execute(query,('3','mayk','42', '5'))

                connection.commit()
                logout_user()
