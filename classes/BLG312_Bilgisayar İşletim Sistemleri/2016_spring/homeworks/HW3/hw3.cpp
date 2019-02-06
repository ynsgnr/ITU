#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <time.h> 
#include <string.h>
#include <thread>
#include <chrono>
#include <ctime> 

#define KEYSHM ftok(get_current_dir_name(),10)
#define KEYSEM1 ftok(get_current_dir_name(),20)
#define KEYSEM2 ftok(get_current_dir_name(),30)
#define KEYSEM3 ftok(get_current_dir_name(),40)
#define KEYSEM4 ftok(get_current_dir_name(),50)
#define KEYSEM5 ftok(get_current_dir_name(),60)

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Tested systems:
* -gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04.3)
* -(ITU SSH)
* Compiled with command of:
*g++ -std=c++11 hw3.cpp
*/

//Örnek Slaytlardan Alınan Semafor Fonksiyonları:
void semSignal(int id,int count){
	struct sembuf signal;
	signal.sem_num=0;
	signal.sem_op=count;
	signal.sem_flg=1;
	semop(id, &signal ,1);
}
void semWait(int id,int count){
	struct sembuf wait;
	wait.sem_num=0;
	wait.sem_op=-count;
	wait.sem_flg=1;
	semop(id, &wait ,1);
}

void writer(std::string, int);
void reader(std::string, int);

main()
 {
 	int f=1,waitTime;
 	std::string input="E";

 	int io=semget(KEYSEM1,1,IPC_CREAT|0700);
 	semctl(io, 0 ,SETVAL,1);
 	//G/Ç için semafor

 	int semRead=semget(KEYSEM2,1,IPC_CREAT|0700);
 	semctl(semRead, 0 ,SETVAL,5);
 	//Okuyucu için semafor

 	int semWrite=semget(KEYSEM3,1,IPC_CREAT|0700);
 	semctl(semWrite, 0 ,SETVAL,1);
 	//Yazıcı için semafor

 	int semSync=semget(KEYSEM4,1,IPC_CREAT|0700);
 	semctl(semSync, 0 ,SETVAL,0);
 	//Yazıcı okuyucu senkranizasyonu için semafor

 	int semWaitParent=semget(KEYSEM5,1,IPC_CREAT|0700);
 	semctl(semWaitParent, 0 ,SETVAL,1);
 	//Çocuk Anne senkranizasyonu için semafor (Devam eden proses olup olmadığını gösterir)

 	int shmid=shmget(KEYSHM,4*sizeof(int),IPC_CREAT | 0666);
 	//Paylaşılan hafıza isteniyor
 	//(1. eleman sistemdeki yazıcı, 2. eleman bekleyen okuyucu sayısı, 3. eleman çalışan okuyucu sayısı)
 	if(shmid==-1){
 		std::cout<<"Paylaşılan hafıza alınamadı:"<<shmid<<std::endl;
 		exit(1);
 	}


 	int* shared=(int *)shmat(shmid,NULL,0);
 	shared[0]=0;//Calisan yazici sayisi
 	shared[1]=0;//Bekleyen okuyucu sayisi
 	shared[2]=0;//Calisan okuyucu sayisi
 	shared[3]=0;//sistemdeki yazici sayisi
 	shmdt(shared);

 	//Sonsuz döngüde girdi geldikçe yeni proses oluşturuluyor:
 	while(!input.compare("E") || !input.compare("e")){
 		waitTime=0;
		input="";
		semWait(io,1);
		std::cout<<"Proses tipini ve çalışma süresini giriniz"<<std::endl;
		while(input=="" || input==" "){
			std::getline(std::cin, input);
		}
		semSignal(io,1);

		//String işleme:
		char type = *(input.substr(0, 1).c_str());
		std::string name= input.substr(0, input.find(" "));
		std::string number = input.substr(input.find(" "),input.find_last_of(" ")-1);
		waitTime=std::stoi(number,nullptr,10);

 		f=fork();
 		if(f==0){
 			if(type=='W' || type=='w'){
				writer(name,waitTime);
			}
			else if(type=='R' || type=='r'){
				reader(name,waitTime);
			}
			input="H";//Döngüyü bitir(Anne prosesde devam eder)
 		}
 		else{
			semWait(io,1);
	 		while(input!="e" && input!="E" && input!="H" && input!="h"){	
	 			std::cout<<"Devam etmek istiyor musunuz? (E/H)"<<std::endl;
	 			std::getline(std::cin, input);
	 		}
			semSignal(io,1);
 		} 		
 	}
 	if(f!=0){
 		// işletim sistemine geri iade
	 	semWait(semWaitParent,1);
	 	std::cout<<"Tüm prosesler tamamlandı!"<<std::endl;
	 	semctl(io,0,IPC_RMID,0);
	 	semctl(semRead,0,IPC_RMID,0);
	 	shmctl(shmid,IPC_RMID,0);
 	}
 }

void writer(std::string name,int workTime){

	int io=semget(KEYSEM1,1,IPC_CREAT|0700);
 	//G/Ç için semafor

 	int semRead=semget(KEYSEM2,1,IPC_CREAT|0700);
 	//Okuyucu için semafor

 	int semWrite=semget(KEYSEM3,1,IPC_CREAT|0700);
 	//Yazıcı için semafor

 	int semSync=semget(KEYSEM4,1,IPC_CREAT|0700);
 	//Çocuk anne senkranizasyonu için semafor

 	int semWaitParent=semget(KEYSEM5,1,IPC_CREAT|0700);
 	//Çocuk Anne senkranizasyonu için semafor

 	int shmid=shmget(KEYSHM,4*sizeof(int),IPC_CREAT | 0666);
 	//Paylaşılan hafıza isteniyor (1. eleman bekleyen ve sistemdeki yazıcı, 2. eleman bekleyen okuyucu sayısı, 3. eleman çalışan okuyucu sayısı)
 	if(shmid==-1){
 		std::cout<<"Paylaşılan hafıza alınamadı:"<<shmid<<std::endl;
 		exit(1);
 	}

	int* shared=(int *)shmat(shmid,NULL,0);
	semWait(io,1);
 	if(shared[2]>0){
 		std::cout<<"Sistemde "<<shared[2]<<" okuyucu var,"<<name<<" bekliyor."<<std::endl;
 	}
 	else if (shared[1]>0)
 	{
 		std::cout<<"Bekleyen "<<shared[1]<<" okuyucu var,"<<name<<" bekliyor."<<std::endl;
 	}
 	else if(shared[0]>1){
 	 	std::cout<<"Sistemde yazıcı var,"<<name<<" bekliyor."<<std::endl;
 	}
 	else if(shared[0]==0 && shared[1]==0 && shared[2]==0  && shared[3]==0){
		semWait(semWaitParent,1);//Proses var
	}
	semSignal(io,1);

	shared[3]++;
	semWait(semWrite,1);
	shared[3]--;

	shared[0]++;
 	shmdt(shared);

	semWait(io,1);
	std::cout<<name<<" çalışıyor"<<std::endl;
	semSignal(io,1);
	sleep(workTime);
	semWait(io,1);
	std::cout<<name<<" bitti"<<std::endl;
	semSignal(io,1);

	shared=(int *)shmat(shmid,NULL,0);
 	shared[0]--;

 	if(shared[0]==0 && shared[1]==0 && shared[2]==0 && shared[3]==0){
		semSignal(semWaitParent,1);//Tüm prosesler bitti
	}
 	else if(shared[0]==0){
		semWait(io,1);
 		std::cout<<"Son yazıcı sistemi terk etti. 5 okuyucuya veya 1 yaziciya izin veriliyor"<<std::endl;
		semSignal(io,1);
		semSignal(semSync,shared[1]);
 		semSignal(semRead,5);
 		semSignal(semWrite,1);
 	}

 	shmdt(shared);
}

void reader(std::string name, int workTime){

	int io=semget(KEYSEM1,1,IPC_CREAT|0700);
 	//G/Ç için semafor

 	int semRead=semget(KEYSEM2,1,IPC_CREAT|0700);
 	//Okuyucu için semafor

 	int semWrite=semget(KEYSEM3,1,IPC_CREAT|0700);
 	//Yazıcı için semafor

 	int semSync=semget(KEYSEM4,1,IPC_CREAT|0700);
 	//Yazıcı okuyucu senkranizasyonu için semafor

 	int semWaitParent=semget(KEYSEM5,1,IPC_CREAT|0700);
 	//Çocuk Anne senkranizasyonu için semafor

 	int shmid=shmget(KEYSHM,4*sizeof(int),IPC_CREAT | 0666);
 	//Paylaşılan hafıza isteniyor (1. eleman bekleyen ve sistemdeki yazıcı, 2. eleman bekleyen okuyucu sayısı, 3. eleman çalışan okuyucu sayısı)
 	if(shmid==-1){
 		std::cout<<"Paylaşılan hafıza alınamadı:"<<shmid<<std::endl;
 		exit(1);
 	}

	int* shared=(int *)shmat(shmid,NULL,0);

	if(shared[0]>0){
		semWait(io,1);
		std::cout<<"Sistemde yazıcı var, "<<name<<" bekliyor."<<std::endl;
		semSignal(io,1);
		shared[1]++;
		semWait(semSync,1);
		shared[1]--;
	}
	else if(shared[2]>=5){
		semWait(io,1);
		std::cout<<"Sistemde 5 okuyucu var "<<name<<" bekliyor."<<std::endl;
		semSignal(io,1);
	}
 	else if(shared[0]==0 && shared[1]==0 && shared[2]==0  && shared[3]==0){
		semWait(semWaitParent,1);//Proses var
	}
	shmdt(shared);

	semWait(semRead,1);

	//Çalışan okuyucu sayısına bir ekle
	shared=(int *)shmat(shmid,NULL,0);
	shared[2]++;
	if(shared[2]==1)
		semWait(semWrite,1);//Yazıcıları dışla
	shmdt(shared);

	semWait(io,1);
	std::cout<<name<<" çalışıyor"<<std::endl;
	semSignal(io,1);

	sleep(workTime);

	semWait(io,1);
	std::cout<<name<<" bitti"<<std::endl;
	semSignal(io,1);

	//Çalışan okucuyu sayısından bir çıkar
	shared=(int *)shmat(shmid,NULL,0);
	shared[2]--;

	if(shared[2]==0){
		semWait(io,1);
		std::cout<<"Son okuyucu sistemi terk ediyor"<<std::endl;
		semSignal(io,1);
		semSignal(semWrite,1);
	}

	semSignal(semRead,1);
	if(shared[0]==0 && shared[1]==0 && shared[2]==0  && shared[3]==0){
		semSignal(semWaitParent,1);//Tüm prosesler bitti
	}
	shmdt(shared);
}