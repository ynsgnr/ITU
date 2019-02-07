#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>

#include "scull_ioctl.h"

int main(){

    int fd,err;
    int choise=0;
    char * ptr="root";
    fd = open("/dev/messagebox",O_RDWR);

    int b=50;
    printf("**********************\n");
    printf("SCULL_EXCLUDE_READ = 1\n");
    printf("SCULL_INCLUDE_READ = 2\n");
    printf("SCULL_MAX_SIZE = 3\n");
    printf("SCULL_DELETE_MESAGE = 4\n");
    printf("***********************\n");
    scanf("%d", &choise);

    switch(choise)
    {
		case 1:
		ioctl(fd,SCULL_EXCLUDE_READ);
		printf("Mode Changed to EXCLUDE_READ\n");
		break;

		case 2:
		ioctl(fd,SCULL_INCLUDE_READ);
		printf("Mode Changed INCLUDE_READ\n");
		break;

		case 3:
		printf("Please Enter New Max Message Que Size\n");
		scanf("%d", &b);
		ioctl(fd,SCULL_MAX_SIZE, &b);
		printf("Max Size setted %d\n", b);
		break;

		case 4:
		printf("Please Enter A User Name For Message Deletion\n");
		scanf("%s\n", ptr);
		ioctl(fd,SCULL_DELETE_MESAGE, &ptr);
		printf("%s 's messages deleted\n", ptr);
		break;

		default:
		break;
	}


    return 0;
}
