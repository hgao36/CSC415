#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define name "Arnold Jiadong Yu"
#define bufferSize 28
int main(){

	int input,output;
	ssize_t bytes = 0,readB,writeB; // number of bytes that copied, read, and write
	char buffer[60]; //store buffer to use to copy
	char readBuffer[bufferSize];
	char fileName1[30],fileName2[30];

	if(sprintf(buffer,"Welcome to the File Copy Program by %s!\n", name) < 0){
		perror("Failed sprintf 1.\n");
	}
	if(write(1,buffer,55) < 0){
		perror("Failed write 1.\n");
	}
	if(sprintf(buffer,"Enter the name of the file to copy from:\n") < 0){
		perror("Failed sprintf 2.\n");
	}
	if(write(1,buffer,41) < 0){
		perror("Failed write 2.\n");
	}
	//input of copy from file name
	scanf("%s", fileName1);
	input = open(fileName1,O_RDONLY);
	//input = open("test1.txt",O_RDONLY);
	if(input < 0){
		perror("Input file open error.\n");
		return -1;
	}


	if(sprintf(buffer,"Enter the name of the file to copy to:\n") < 0){
		perror("Failed sprintf 3.\n");
	}
	if(write(1,buffer,39) < 0){
		perror("Failed write 3.\n");
	}
	//input of copy to file name
	scanf("%s", fileName2);
	output = open(fileName2,O_WRONLY|O_CREAT|O_EXCL,00644);
	//output = open("testResult.txt",O_WRONLY|O_CREAT|O_EXCL,00644);

	if(output < 0){
		perror("Output file open error.\n");
		return -1;
	}

	do{
		readB = read(input,readBuffer,bufferSize-1);
		if(readB < 0){
			perror("Read Input File error.\n");
			return -1;
		}

		writeB = write(output,readBuffer,readB);
		if(writeB < 0){
			perror("Write Input File error.\n");
			return -1;
		}

		bytes = bytes + writeB;
	}while(readB != 0);

	if(sprintf(buffer,"File Copy Successful, %zi bytes copied.\n", bytes) < 0){
		perror("Failed sprintf 4.\n");
	}
	if(write(1,buffer,40) < 0){
		perror("Failed write 4.\n");
	}
	close(input);
	close(output);
}