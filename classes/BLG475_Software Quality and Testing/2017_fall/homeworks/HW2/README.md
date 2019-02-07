##Amaç
Bu uygulama basit bir bankacılık sistemine hizmet veren rest api'dir. Bu uygulama ile yapılan işlemler aşağıdaki gibidir;
    
    - İsimden hesap sorgulama
    - Müşteri hesabına para yatırma
    - Müşteri hesabından para çekme
    
Uygulamanın geliştirmesi tamamlanmıştır fakat hiçbir unit testi bulunmamaktadır. %100 unit test coverage'a ihtiyaç vardır. 

    - Tüm fonksiyonalitelerin testini de kapsayacak şekilde code coverage sağlanmalıdır. 
    - Kodun içerisinde yer alan tüm metodların işleyişini kontrol edecek şekilde unit testler yazılmalıdır. Örneğin; deposit, withdraw metodları vs.
    - Notlandırma coverage üzerinden yapılacaktır.
    - Mock kullanılması gereken noktalarda kullanılmadan yapılan testler yokmuş gibi kabul edilecektir ve notlandırılmayacaktır. 
    - Kodda %100 coverage sağlanması gerekmektedir. Fakat %100 coverage sağlansa bile fonksiyonalite kontrolü yapılmadığı durumda unit test geçersiz sayılacak ve notlandırılmayacaktır. 
	- Örneğin; %100 coverage sağlandığında not 100, %30 coverage sağlandığında not 30 olacaktır.
    - Coverage hesabı statement yöntemine göre yapılacaktır.
	
##Ödevin Teslim Edilmesi
Projenin bir bütün olarak teslim edilmesi gerekmektedir. Source kodlar ve unit testler birlikte olacak şekilde iletilmelidir.

##Uygulamayi baslatmak ve manual testler
Uygulamayi baslatmak icin `com.aric.samples.account.Application` class'indaki main methodunu calistirmaniz gerekiyor.
Run etmek için herhangi bir özel bir run configuration gerekmemektedir.

##Uygulamayi baslattiktan sonra asagidaki httpie(https://httpie.org/docs) komutu ile ornek bir kayit olusturulabilir.

    http POST :8080/account < ./src/main/resources/accounts.json

###sonrasinda

    http GET :8080/query name==Mehmet 
###komutu ile account bilgilerine erisilip

    http GET :8080/deposit id==1 amount==13403 
###komutu ile para yatirilip
 
    http GET :8080/eft senderId=1 receiverId=2 amount=100
###komutu ile de para gönderimi yapılır. 
