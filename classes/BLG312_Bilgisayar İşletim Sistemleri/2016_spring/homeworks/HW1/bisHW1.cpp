#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

main()
 {
 int i = 1;
 int sonuc = 0;
 for (i = 1; i <= 2; i++)
 {
 sonuc = fork();
 if (sonuc == 0)
 {
 printf("Cocuk proses (i=%d,pid=%d). \n",i,getpid());
 }
 else
 {
 printf("Anne proses (i=%d,pid=%d). \n",i,getpid());
 }
 }
 }