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

#define KEYSHM ftok(get_current_dir_name(),10)
#define KEYSEM1 ftok(get_current_dir_name(),20)
#define KEYSEM2 ftok(get_current_dir_name(),30)

#define MAKS 1000

main()
 {
 	int n,M,f,semChild,semParent,x,y,i;

 	//Girdi:
 	std::cout<<"A dizisinin eleman sayısını (n) giriniz:";
 	std::cin>>n;
 	std::cout<<std::endl;

	int shmid=shmget(KEYSHM,(2*n+5)*sizeof(int),IPC_CREAT | 0666);
 	//Paylaşılan hafıza isteniyor

 	if(shmid==-1){
 		std::cout<<"Paylaşılan hafıza alınamadı:"<<shmid<<std::endl;
 		exit(1);
 	}

 	int* shared=(int *)shmat(shmid,NULL,0);

 	shared[0]=n;
 	shared[1]=M;
 	shared[2]=-1; //x değeri
 	shared[3]=-1; //y değeri

 	srand (time(NULL));

 	for(i=0;i<n;i++){
 		//Rasgele sayı üretimi
 		shared[i+4]=rand() % MAKS;
 	}

 	std::cout<<"Oluşturulan A dizisi: A={";
 	for (i=0;i<n;i++){
 		std::cout<<shared[i+4]<<",";
 	}
 	std::cout<<"}"<<std::endl;
 	std::cout<<"A dizisinin başlangıç adresi: "<<(long long)shared+4<<"(decimal)"<<std::endl;
 	//Shared+4 A dizisinin başlangıcı adresi

 	shmdt(shared);

 	struct sembuf signal;
	signal.sem_num=0;
	signal.sem_op=1;
	signal.sem_flg=1;

	struct sembuf wait;
	wait.sem_num=0;
	wait.sem_op=-1;
	wait.sem_flg=1;


 	semChild=semget(KEYSEM1,1,IPC_CREAT|0700);
 	semctl(semChild, 0 ,SETVAL,0);
 	//Çocukların senkranizasyonu için semafor

 	semParent=semget(KEYSEM2,1,IPC_CREAT|0700);
 	semctl(semParent, 0 ,SETVAL,0);
 	//Çocuklar ile annenin senkranizasyonu için semafor

 	if(semParent<0 || semChild<0){
 		std::cout<<"Seamafor alınamadı"<<std::endl;
 		exit(1);
 	}

 	std::cout<<std::endl<<"M değerini giriniz:";
 	std::cin>>M;
 	std::cout<<std::endl;

 	for(i=0;i<2;i++){
 		f=fork();
 		if (f==-1){
 			std::cout<<"Yeni proses üretirken hata!"<<std::endl;
 			exit(1);
 		}
 		if(f==0)
 			break;
 	}

 	if(f!=0){
 		semop(semParent, &wait ,1);//Çocuk_2'yi bekle
 		int* shared=(int *)shmat(shmid,NULL,0);

 		x=shared[2];
 		y=shared[3];
 		if(x==-1 || y==-1){
 			std::cout<<"Hafıza Hatası! x:"<<x<<" y:"<<y<<std::endl;
 			exit(0);
 		} 
 		std::cout<<"Çocuk_1: “≤ M” olan eleman sayısı x="<<x<<std::endl;
 		std::cout<<"Çocuk_1: B dizisinin başlangıç adresi: "<<(long long)shared+n+4<<std::endl;
 		std::cout<<"Çocuk_1: B={";
 		for (i=n;i<(n+x);i++){
 			std::cout<<shared[i+4]<<",";
 		}
 		std::cout<<"}"<<std::endl;

 		std::cout<<"Çocuk_2: “> M” olan eleman sayısı y="<<y<<std::endl;
 		std::cout<<"Çocuk_2: C dizisinin başlangıç adresi: "<<(long long)shared+n+x+4<<std::endl;
 		std::cout<<"Çocuk_2: C={";
 		for (i;i<(n+x+y);i++){
 			std::cout<<shared[i+4]<<",";
 		}
 		std::cout<<"}";

 		//İşletim sistemine iade:
	 	shmdt(shared);
 		shmctl(shmid,IPC_RMID,0);
 		semctl(semParent,0,IPC_RMID,0);
 		semctl(semChild,0,IPC_RMID,0);
 	}
 	else{
 		if(i==1){
 			//Çocuk_2
 			semop(semChild, &wait ,1);

 			int* shared=(int *)shmat(shmid,NULL,0);

 			x=shared[2];
 			y=0;
 			for(i=0;i<n;i++){
 				if(shared[i+4]>M)
 				{
 					shared[y+x+n+4]=shared[i+4];
 					y++;
 				}
 			}
 			shared[3]=y;
 			shmdt(shared);
 			semop(semParent, &signal ,1);//Anneyi uyandır
 		}
 		else{
 			//Çocuk_1
 			int* shared=(int *)shmat(shmid,NULL,0);
 			x=0;
 			for(i=0;i<n;i++){
 				if(shared[i+4]<=M)
 				{
 					shared[x+n+4]=shared[i+4];
 					x++;
 				}
 			}
 			shared[2]=x;
 			shmdt(shared);
 			semop(semChild, &signal ,1);//Çocuk_1'i uyandır
 		}
 	}
 	return 0;
 }