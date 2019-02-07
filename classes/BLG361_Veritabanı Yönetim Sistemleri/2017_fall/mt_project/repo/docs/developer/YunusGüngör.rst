Yunus Güngör tarafından tamamlanan parçalar
===========================================

Uygulamada bulunan tüm tablo yapıları ve kodlar Yunus Güngör tarafından tamamlanmıştır.

Uygulamada 3 farklı varlık bulunmaktadır:

:Varlıklar:

  * Kullanıcılar (Users)
  * Mesajlar (Messages)
  * Cevaplar (answers)

Kullanıcılar (Users)
--------------------

Kullanıcılar varlığında bulunan özellikler:

* USERNAME PRIMARY KEY
  Her kullanıcıya has kullanıcı adı
* PASS
  Kullanıcıların şifresi, hash fonksiyonundan geçtikten sonra depolanır
* ISADMIN
  Kullanıcının admin kullanıcı olup olmadığını belirtir
* PICTURE
  Kullanıcı resminin adresini tutar
* BESTFRIEND
  Kullanıcının en iyi arkadaşını tutar

**Kullanıcılar (Users) varlığında kullanılan sorgular:**

* Kullanıcı ekleme
   .. code-block:: python

      query = "SELECT PASS FROM USERS WHERE USERNAME = %s"
      cursor.execute(query, (username,))
      if(cursor.fetchall()):
        return 'User already exists'
      query = "INSERT INTO USERS (USERNAME, PASS) VALUES (%s, %s)"

* Kullanıcı bilgilerini görüntüleme
   .. code-block:: sql

      SELECT * FROM USERS WHERE USERNAME = %s

* Kullanıcı şifresini getirtme
   .. code-block:: python

        query = "SELECT PASS FROM USERS WHERE USERNAME = %s"
        cursor.execute(query, (username,))
        password = cursor.fetchall()
        if password is not None and len(password)==1:
            return password[0][0]

* Kullanıcı şifresini değiştirme
   .. code-block:: python

       if form.validate_on_submit():
         hashedPass = pwd_context.encrypt(form.data['password'])
         db.update_pass(current_user.username,hashedPass)
         flash('Updated Password')

   .. code-block:: python

        query = "UPDATE USERS SET PASS=%s WHERE USERNAME=%s"
        cursor.execute(query, (password,username))

* Kullanıcı fotoğrafını değiştirme
   .. code-block:: python

        query = "UPDATE USERS SET PICTURE=%s WHERE USERNAME=%s"
        cursor.execute(query, (picture,username))
        connection.commit()

* Kullanıcıyı silme
   .. code-block:: python

        if current_user.is_admin and username!='admin':
              db=Database()
              db.del_user(username)
          return redirect(url_for('site.home_page'))

   .. code-block:: sql

        DELETE FROM USERS WHERE USERNAME=%s

* Kullanıcıyı admin kullanıcı yapma
   .. code-block:: python

       if current_user.is_admin and username!='admin':
             db=Database()
             db.adminize(username)
         return redirect(url_for('site.home_page'))

   .. code-block:: sql

        UPDATE USERS SET ISADMIN=TRUE WHERE USERNAME=%s

* Tüm kullanıcıları görüntüleme
   .. code-block:: sql

      SELECT USERNAME FROM USERS

* Kullanıcıları en iyi arkadaş olarak düzenleme
   .. code-block:: python

      query = "UPDATE USERS SET BESTFRIEND=%s WHERE USERNAME=%s "
      cursor.execute(query, (username1,username2,))
      cursor.execute(query, (username2,username1,))

* Kullanıcıların en iyi arkdaşını görüntüleme
   .. code-block:: sql

      SELECT BESTFRIEND FROM USERS WHERE USERNAME=%s

* Kullanıcıyı arkadaş olarak ekleme
   .. code-block:: python

        query = "SELECT * FROM FRIENDS WHERE USERNAME = %s AND FRIEND=%s"
        cursor.execute(query, (username1,username2,))
        f1 = cursor.fetchall()
        cursor.execute(query, (username2,username1,))
        f2 = cursor.fetchall()
        if(len(f1)<=0 or len(f2)<=0):
          #no realationship
          query = "INSERT INTO FRIENDS VALUES(%s,%s)"
          cursor.execute(query, (username1,username2,))

* Kullanıcıyı arkadaşlıktan çıkarma
   .. code-block:: python

        query = "SELECT * FROM FRIENDS WHERE USERNAME = %s AND FRIEND=%s"
        cursor.execute(query, (username1,username2,))
        f1 = cursor.fetchall()
        cursor.execute(query, (username2,username1,))
        f2 = cursor.fetchall()
        if(len(f1)>0 or len(f2)>0):
          #confirmed friendship
          query = "DELETE FROM FRIENDS WHERE USERNAME = %s AND FRIEND=%s"
          cursor.execute(query, (username1,username2,))

* Kullanıcının arkadaşlarını görüntüleme
   .. code-block:: sql

        SELECT FRIEND FROM FRIENDS WHERE USERNAME = %s

Mesajlar (Messages)
--------------------

Mesajlar varlığında bulunan özellikler:

* ID PRIMARY KEY
  Her mesaja özel olan kimlik numarası
* TITLE
  Mesajın başlığı
* CONTENT
  Mesajın içeriği (gövdesi)
* USERNAME
  Mesaja sahip olan kullanıcı

**Mesajlar (Messages) varlığında kullanılan sorgular:**

* Mesaj ekleme
   .. code-block:: sql

      INSERT INTO MESSAGES (TITLE, CONTENT, USERNAME) VALUES (%s, %s, %s)

* Mesaj görüntüleme
   .. code-block:: sql

      SELECT * FROM MESSAGES WHERE ID = %s

* Mesajların tamamını görüntüleme
   .. code-block:: sql

      SELECT * FROM MESSAGES LEFT OUTER JOIN USERS ON MESSAGES.USERNAME = USERS.USERNAME

* Mesajı silme
   .. code-block:: python

      if current_user.is_admin:
            db=Database()
            db.del_message(message_id)
        return redirect(url_for('site.home_page'))

   .. code-block:: sql

      DELETE FROM MESSAGES WHERE ID=%s

* Mesajı Düzenleme
   .. code-block:: python

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

   .. code-block:: sql

      UPDATE MESSAGES SET TITLE=%s, CONTENT=%s WHERE ID=%s


Cevaplar (Answers)
--------------------

Cevaplar varlığında bulunan özellikler:

* ID PRIMARY KEY
  Her mesaja özel olan kimlik numarası
* MESSAGE_ID
  Cevabın ait olduğu mesajın kimlik numarası
* USERNAME
  Cevaba sahip olan kullanıcı
* CONTENT
  Cevabın içeriği
* VOTES
  Cevabın aldığı toplam oy sayısı

**Cevaplar (Answers) varlığında kullanılan sorgular:**

* Cevap ekleme
   .. code-block:: sql

      INSERT INTO ANSWERS (MESSAGE_ID,USERNAME,CONTENT) VALUES (%s, %s, %s)

* Cevap görüntüleme
   .. code-block:: sql

      SELECT * FROM ANSWERS INNER JOIN USERS ON ANSWERS.USERNAME=USERS.USERNAME WHERE ID = %s

* Bir mesaja ait tüm cevapları tamamını görüntüleme
   .. code-block:: python

         query = "SELECT * FROM MESSAGES"
         cursor.execute(query)
         messages = cursor.fetchall()
         answers = {}
         for message in messages:
             query = "SELECT * FROM ANSWERS LEFT OUTER JOIN USERS ON ANSWERS.USERNAME=USERS.USERNAME WHERE MESSAGE_ID=%s ORDER BY VOTES DESC"
             cursor.execute(query,(message[0],))
             answer = cursor.fetchall()
             answers[message[0]]=answer
         return answers

* Bir cevabın oy sayısını arttırma
   .. code-block:: sql

      UPDATE ANSWERS SET VOTES = VOTES + 1 WHERE ID=%s

* Cevabı silme
   .. code-block:: python

      if current_user.is_admin:
            db=Database()
            db.del_answer(message_id)
        return redirect(url_for('site.home_page'))

   .. code-block:: sql

      DELETE FROM ANSWERS WHERE ID=%s

* Cevabı Düzenleme
   .. code-block:: python

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

   .. code-block:: sql

      UPDATE ANSWERS SET CONTENT=%s WHERE ID=%s
