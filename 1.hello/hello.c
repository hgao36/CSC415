#include <stdio.h>
#include <unistd.h>

#define name "Arnold Jiadong Yu"

int main(){

	char buffer[60];  //create buffer array to hold string
	int n; // number of bytes to be used

	n = sprintf(buffer,"CSC 415, This program written by %s !\n", name);

    //creat if statement to ensure that same bytes were used, otherwise print out error message.
	if(write(1,buffer,n) != n){
		write(2,"There is an error.\n",19);
		return -1;
	}

	return(0);
}

