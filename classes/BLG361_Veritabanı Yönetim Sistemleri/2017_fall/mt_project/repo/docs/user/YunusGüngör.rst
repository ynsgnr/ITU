Yunus Güngör tarafından tamamlanan parçalar
===========================================

Ana Sayfa
---------

Misafir Kullanıcı
^^^^^^^^^^^^^^^^^

  Misafir kullanıcı giriş yapmak için sağ üst köşede bulunan "Login" butonunu kullanabilir. Kullanıcın giriş yapması ile, misafir kullanıcı normal kullanıcı haline gelir.

  .. figure:: /pictures/homePageNoLogin.png
     :scale: 50 %
     :alt: Ana Sayfa Ekranı

     Misafir kullanıcı ana sayfada mesajları ve cevapları görüntüleyebilir veya giriş yapabilir.

  Herhangi mesaja ait cevaplar görüntülenmek istendiğinde "Answers" butonuna basılarak o mesaja ait mesajlar ve o mesajların oyları ekranda görüntülenebilir.

  .. figure:: /pictures/answersNoLogin.png
     :scale: 50 %
     :alt: Ana Sayfa Ekranı ve cevaplar

     "Answers" butonuna basıldıktan sonra cevaplar mesajın altında görüntülenebilir hale gelir.

  Cevapların sol tarafında cevabı yazan kullanıcının adı ve resmi bulunmaktadır.

  Cevap yazmak için kullanıcıların giriş yaparak normal kullanıcı olması gerekmektedir. Giriş yapmak için login sayfası kullanılabilir.

  .. figure:: /pictures/loginPage.png
     :scale: 50 %
     :alt: Giriş sayfası

     Daha önce kaydolunan kullanıcı adı ve şifre login sayfasındaki forma girilerek ve "Log in/Sign Up" butonuna basılarak giriş yapılabilir.

  Eğer misafir kullanıcı daha önce hesabını kaydetmediyse, başka bir kullanıcı tarafından kullanılmayan bir kullanıcı adı ve daha sonra hatırlayabileceği bir şifreyi login sayfasındaki forma girip, "Log in/Sign Up" tuşuna bastıktan sonra, kullanıcının şifreyi tekrar girmesi istenecektir.

  .. figure:: /pictures/signUp.png
     :scale: 50 %
     :alt: Üye olma işlemi

     Verilen ekstra mesajlar ile sistemin nasıl kullanılabileceği ile ilgili ipuçları veya geri bildirimler yapılmaktadır. Login sayfasında sistemde bulunmayan bir kullanıcı adı girildiğinde login sayfası otamatik olarak üye ekleme moduna geçer. Kullanıcının şifresini tekrar girmesi ile yeni kullanıcı sistemde oluştulabilir. Bu durumda kullanıcı adı değiştirilemez. Eğer kullanıcı yanlış kullanıcı adı girdiğini düşünüyorsa tarayıcıdaki geri tuşunu kullanarak geri dönebilir ve tekrar deneyebilir.

  Oluşturulan hesabın şifresi veya profil fotosu profil sayfasından değiştirilebilir ancak kullanıcı adının değiştirilmesine izin verilmez.

Normal Kullanıcı
^^^^^^^^^^^^^^^^

  Kullanıcı giriş yaptıktan veya sistem otamatik olarak tanıdıktan sonra ana sayfa ekranı "Profile" butonu, "Add Message" sekmesi, her mesajda "Reply" butonu ve her cevapta "Up" butonu ile birlikte görüntülenir.

  .. figure:: /pictures/homePage.png
     :scale: 50 %
     :alt: Ana Sayfa Ekranı

     Ana sayfa ekranından "Profile" butonu kullanılarak profil sayfasına erişilebilir. Kullanıcı ansayfada bulunan "Add Message" sekmesini kullanarak yeni bir mesaj ekleyebilir.

  "Add Message" sekmesine tıklandığında mesaj eklemek için gerekli olan form ekranda görünür olacaktır. Bu formda başlık ve mesaj bilgileri doldurulduktan sonra "add message" butonuna basarak yeni mesaj sisteme eklenebilir.

  .. figure:: /pictures/addMessage.png
     :scale: 50 %
     :alt: Mesaj Ekleme sekmesi

     Mesaj eklemek için doldurulması gereken form.

  Herhangi bir cevap eklemek için, cevap eklenmek istenen mesajın üstünde bulunan "Reply" tuşu kullanılabilir.

  .. figure:: /pictures/reply.png
     :scale: 50 %
     :alt: Mesaja cevap vermek için kullanılan bölüm

     "Reply" tuşuna basıldığında görüntülenen form doldurularak ve "Add New Answer to the Message" butonu kullanılarak, mesaja cevap eklenebilir. Tekrar "Reply" tuşuna basıldığında veya butona basıldığında form tekrar gizlenir.

 Herhangi bir cevaba oy vermek için oy verilmek istenen cevabın üstünde bulunan "Up" butonu kullanılabilir. Oy verildikten sonra ana sayfa yenilenir ve cevaplar oy sayısına göre tekrar sıralanır. Kullanıcıların oy verme sınırı bulunmamaktadır. Herhangi bir cevabın daha yukarda görüntülenmesi verilen oyların sayısına bağlıdır. Daha çok oy alan cevap daha yukarda görüntülenir.

 .. figure:: /pictures/up.png
    :scale: 50 %
    :alt: Cevabı oylamak için kullanılabilecek buton

    "Up" butonun görüntülenebilmesi için kullanıcının giriş yapmış olması ve herhangi bir mesaja ait olan cevapları görüntülüyor olması gerekmektedir.

Admin Kullanıcı
^^^^^^^^^^^^^^^

  Admin kullanıcılar normal kullanıcıların yapabildiği tüm işlemleri normal kullanıcı gibi yerine getirebilir. Bu işlemler: Mesaj ekleme, cevap ekleme, profil sayfasına erişebilme ve cevapları oylayabilmektir. Bu işlemlerin yanında ana sayfada mesaj ve cevapları düzenleyebilirler.

  .. figure:: /pictures/mainPageAdmin.png
     :scale: 50 %
     :alt: Admin hesabı ile görüntülenen ana sayfa

     Admin kullanıcı ana sayfada bulunan mesajların üzerindeki "Delete" ve "Edit" butonlarına erişim sağlayabilir.

  Admin kullanıcılar eklenen herhangi bir mesaj veya cevabı silebilir veya düzenleyebilir. Mesaj veya cevapların üzerinde bulunan "Delete" butonuna basıldığında o mesaj veya cevap silinir. Silinen mesaja ait olan tüm cevaplar da mesajla birlikte silinir.
  "Edit" butonuna basıldığında ise yeni bir sayfada düzenleme formu daha önce bulunan mesaj veya cevap verisiyle birlikte görüntülenir. İstenilen düzenlemeler yapıldıktan sonra "Summit Message" butonu ile yapılan değişiklikler kaydedilir.

  .. figure:: /pictures/answerEdit.png
     :scale: 50 %
     :alt: Cevap Düzenleme ekranı

     Cevap Düzenleme ekranı

  .. figure:: /pictures/messageEdit.png
    :scale: 50 %
    :alt: Mesaj Düzenleme ekranı

    Mesaj Düzenleme ekranı

Profil Sayfası
--------------

Misafir Kullanıcı
^^^^^^^^^^^^^^^^^

  Misafir kullanıcı profil sayfasına erişemez. Profil sayfasına sadece sisteme giriş yapmış olan normal kullanıcılar veya admin kullanıcılar ulaşabilir.

Normal Kullanıcı
^^^^^^^^^^^^^^^^

  Normal kullanıcı profil sayfasından hesabından çıkış yapabilir, şifresini değiştirebilir, profil resmini değiştirebilir, diğer kullanıcıları görüntüleyebilir, diğer kullanıcıları arkadaş olaral ekleyebilir veya en iyi arkadaşını değiştirebilir.

  .. figure:: /pictures/profile.png
     :scale: 50 %
     :alt: Profil Ekranı

     Profil ekranında kullanıcıyı kullanıcı ismiyle karşılayan bir mesaj bulunmaktadır.

  Sağ üstteki "Log Out" butonu ile kullanıcılar hesabından çıkış yapabilir.
  "Change Password" bölümündeki formu doldurarak, "Change Password" butonuna basarak kullanıcı şifresi değiştirilebilir.
  "Change Picture" bölümündeki formda yapılan değişiklikler, "Change Picture" butonuna basarak kaydedilebilir. Bu bölüm ("User Picture") kullanıcının profil fotosunu bulundurur. Sistemin dosya depolama yeteneği olmadığı için profil fotoğrafları başka bir site üzerinden link ile kullanılabilmektedir.
  "Best Friend" bölümünde kullanıcının en iyi arkadaşı görüntülenebilir. Bu bölümün varsayılan değeri "admin" dir. Herhangi bir en iyi arkadaş bulunamazsa sistem "admin" i en iyi arkadaş olarak görüntülemektedir.
  "Friends" bölümünde eklenen arkadaşlar görüntülenebilir. Arkadaşların üzerinde "Remove Friend" butonu kullanılarak o kullanıcı arkadaşlıktan çıkarılabilir.

  "Users" bölümünde sistemdeki tüm kullanıcılar görüntülenebilir. Her kullanıcının üzerinde bulunan "Add as a friend" butonu kullanılarak o kullanıcı arkadaş olarak eklenebilir. Eklenen arkadaşlar "Friends" bölümünde görüntülenebilir. "Add as bestfrind" butonu kullanılarak kullanıcı en iyi arkadaş olarak eklenebilir. En iyi arkadaş olarak eklenen kullanıcın en iyi arkadaşı eklemeyi yapan kullanıcı olarak düzenlenir. Yani en iyi arkadaş butonu iki kullanıcı için de en iyi arkadaşı değiştirir.

Admin Kullanıcı
^^^^^^^^^^^^^^^

  Admin kullanıcı normal kullanıcının profil sayfasında yapabildikleri dışında kullanıcıları silebilir veya başka bir kullanıcıyı admin kullanıcı yapabilir.

  .. figure:: /pictures/profileAdmin.png
     :scale: 50 %
     :alt: Profil Ekranı Admin

     Admin kullanıcı profil sayfasına giriş yaparsa, "Users" bölümünde kullanıcılara ait "Remove User" ve "Make Admin" butonlarını görebilir.

  Kullanıcıların üzerindeki "Remove User" butonuna basarak o kullanıcı sistemden silinebilir. Sistemde bulunan o kullanıcının eklediği tüm mesajlar ve cevaplar o kullanıcıyla birlikte sistemden silinir.
  Kullanıcılar üzerindeki "Make Admin" butonuna basılarak normal bir kullanıcı admin kullanıcı seviyesine getirilebilir.

  Ayrıca admin kullanıcı giriş yaptıktan sonra tarayıcı üzerinden site adresindeki "/reset" adresine girerse sistemde bulunan tüm veriler temizlenir ve yeniden kurulumu yapılır. Eğer sistemde hiçbir kullanıcı yoksa admin kullanıcı şartı aranmaz. Admin kullanıcı tarayıcı üzerinden site adresindeki "/dummy" adresine girerse sisteme daha önceden hazırlanmış verilerin girişi yapılır.
  Sistemin yeniden kurulumundan sonra sisteme tek bir kullanıcı eklenir ve bu kullanıcı admin kullanıcı olarak ayarlanır. Bu kullanıcının kullanıcı adı "admin" ve şifresi "admin" dir.
