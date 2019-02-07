Geliştirici Kılavuzu
====================

Veritabanı Tasarımı
-------------------

Veritabanında 3 varlık ve 4 tablo bulunmaktadır. Tablolardan 1 tanesi varlıklar arası bağlantı kurmak için kullanılmıştır. Veritabanındaki varlıklar ve bağlantılar aşağıdaki diagramda görülebilir.
Bu varlıkların yönetimi (ekle,sil,düzenle,ara) ile ilgili fonksiyonların tümü "app/models/database.py" dosyasının içinde "Database" sınıfında bulunmaktadır.

.. figure:: /pictures/erDiagram.png
   :scale: 50 %
   :alt: Veritabanı yapısı diagramı

   Veritabanı yapısı

Kod
----

Bu uygulamada kodlar klasörlendirilmiş ve obje tabanlı bir yaklaşım izlenmiştir. Ana dizinde bulunan "app" klasörü uygulamanın kaynak kodlarını içerir. Diğer klasör ve dosyalar uygulamanın genel yapısının kurulması ve çalıştırılması ile ilgilidir.
"app" klasörü içindeki "models" klasöründe uygulamada kullanılan objeler yer almaktadır. "handlers.py" web sayfalarının adreslerinin işlenmesi ve yönlendirilmesini kontrol etmektedir ve "forms.py" uygulamada kullanılan tüm girdi formlarını bulundurmaktadır. Bunların yanında "server.py" dosyasında uygulamayı başlatmak için gerekli kodlar ve konfigürasyonlar yer almaktadır.
"templates" klasöründe ise html ve css kullanılarak yazılmış arayüz dosyaları bulunmaktadır.

Uygulama "server.py" dosyasının python ile çalıştırılması ile başlatılabilir.

**Uygulamada bazı 3. parti eklentiler ve temalar kullanılmıştır:**

Uygulama **python** kullanalarak yazılmıştır, python'ın yanında 3. parti anaçatılar ve eklentileri kullanılmıştır.

:Kullanılan anaçatı yapıları:

  * Bootstrap
  * Flask

:Eklentiler:

   * psycopg2
   * passlib
   * flask_login
   * Flask-WTF
   * wtforms_components

:Tema ve arayüz eklentileri:

  * Superhero bootstrap teması
  * UI Comments arayüzü

Tema ve arayüz eklentileriyle ilgili daha fazla bilgi kaynak koddaki "Citations and used libraries.txt" dosyasında bulunabilir.

Uygulamadaki veritabanı tabloları "/reset" linkine girilmesiyle tetiklenen "resetEverything()" fonksiyonu ile oluşturulmuştur.
Aynı zamanda uygulamadaki "/dummy" linkine girilmesi tetiklenen "insertDummy()" fonksiyonu ile sisteme belirli bir miktarda veri otamatik olarak eklenebilir.
Bu iki fonksiyon da "adminStuff.py" dosyasındaki "adminCommands" sınıfında bulunmaktadır.

 .. code-block:: python

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


 .. code-block:: python

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

Kodda bulunan current_user, dbapi2, current_app.config['dsn'], pwd_context, logout_user komutları sırasıyla flask_login, psycopg2, "server.py" konfigürasyonu, passlib, flask_login kütüphaneleri veya dosylarından elde edilmektedir.

.. toctree::

   YunusGüngör
