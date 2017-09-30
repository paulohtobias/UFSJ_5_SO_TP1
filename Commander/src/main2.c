#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_BUFF 1

int main(int argc, char *argv[]){
	int fd = open("/tmp/input",O_RDONLY);
	char buf;
	while(buf!='T'){
		read(fd,&buf,MAX_BUFF);
		printf("%c\n",buf);
	}
	close(fd);
	//unlink("/tmp/input");

	return 0;
}