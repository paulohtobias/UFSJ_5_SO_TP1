#include <stdio.h>
#include <unistd.h>

int main(){
	char b;
	while(read(0, &b, 1) > 0){
		putchar(b);
	}
	return 0;
}
