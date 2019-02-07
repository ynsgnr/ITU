###Greet unknown people

    http :8080/greeting?name=ahmet
    
###Create new Person
    
    http POST :8080/people < ./resources/dursun.json

###Greet known people from db

    http :8080/greetingKnownPeople?id=1