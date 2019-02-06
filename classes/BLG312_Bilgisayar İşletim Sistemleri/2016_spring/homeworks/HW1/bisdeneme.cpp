#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#define COCUK_SAYISI 2
#define IPLIK_SAYISI 2
int sayac = 0;
void *altprogram(void *iplik_no) {
 sayac = sayac + 1;
 printf(" Altprogram: Proses kimlik no = %d Anne proses kimlik no = %d Iplik no = %d,
 Deger = %d \n", getpid(), getppid(), iplik_no, sayac);

}
pthread_exit(NULL);
int main(void) {
 pthread_t iplikler[IPLIK_SAYISI];
 int cocuklar[COCUK_SAYISI];
 int rc, i, j;
 int f = 1;
 printf("Ana program: Proses kimlik no = %d Anne proses kimlik no: %d\n",
 getpid(), getppid());
 for (i = 0; i < COCUK_SAYISI; i++) {
 if (f > 0)
 f = fork();
 if (f == 0)
 break;
 else
 cocuklar[i] = f;
 }
 if (f == 0) {
 printf("Cocuk: Proses kimlik no: %d Anne kimlik no: %d sayac deger:%d\n",
 getpid(), getppid(), sayac);
 for(j = 0; j < IPLIK_SAYISI; j++)
 rc = pthread_create(&iplikler[j], NULL, altprogram, (void *)j);
 }
 else {
 for (i = 0; i < COCUK_SAYISI; i++)
 printf("Ana program: Cocuk[%d] kimlik no: %d yaratildi.\n", i, cocuklar[i]);
 wait(NULL);
 }
 return 0;
} 