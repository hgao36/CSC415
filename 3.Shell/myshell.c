/**
 * Name         : Arnold Jiadong Yu	
 * Date         : 10-07-2017
 * File Name    : myshell.c
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

//DO NOT CHANGE THIS
#define MAX_BUFF_SIZE 256


int main() {

	pid_t c_pid; //store the pid of child process
	char input[MAX_BUFF_SIZE], *command;
	char* myargv0[MAX_BUFF_SIZE], *myargv1[MAX_BUFF_SIZE];
	int output; //store the file position.
	int redi_stdin,redi_stdout,redi_stderr; //redirect stdin, stdout, stderr, set them to 1 if condition meet.
	int myargc0, myargc1; // holds number of arguments
	int number_SC; // number of special charaters check, add one each time.
	int pipeN, pipeProcess; //pipe check, if | then set pipe to 1
	int backGround; // backGround check, if & then set backGround to 1
	char* filename1, *process2; //filename for > >> < << operators 
	int fd[2]; // use for pipe
	char* position;
	int size; // store size of the input length
	int i, j; // store position of speical character

	while(1){

		number_SC = 0; //number of special character
		pipeN = 0, pipeProcess = 0;
		myargc0 = 0, myargc1 = 0;
		redi_stdin = 0, redi_stdout = 0, redi_stderr = 0;
		output = 0;
		backGround = 0;
		position = 0;
		filename1 = 0, process2 = 0;
		size = 0, i = 0, j = 0;

		do{
			printf("MyShell> ");

			if(fgets(input, MAX_BUFF_SIZE, stdin) < 0){
				perror("Failed to get input.");
			}
		}while(strcmp(input, "\n") == 0);
		
		if(strcmp(input,"exit\n") == 0){
			return 0;
		}

		//printf("%lu",strlen(input));	
		//remove \n at the last of input, https://www.tutorialspoint.com/c_standard_library/string_h.htm 13
		/*if(strncpy(input, input, strlen(input)-1) < 0 ){
			perror("Failed to remove '\n' at last.\n");
			return 1;
		}*/
		input[strlen(input)-1] = 0;
	
		//check if the string has >
		if(strstr(input," > ")){
			position = strstr(input, " > ");
			filename1 = position + 3;
			output = open(filename1,O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); 
			if(output < 0){
				perror("Failed to create file.\n");
			}

			number_SC++;
			redi_stdout = 1;
			position = NULL;
		}
		//check if the string has >>
		if(strstr(input," >> ")){
			position = strstr(input, " >> ");
			filename1 = position + 4;
			output = open(filename1, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
			if(output < 0){
				perror("Failed to append file.\n");
			}

			number_SC++;
			redi_stdout = 1;
			position = NULL;
		}
		//check if the string has <
		if(strstr(input," < ")){
			position = strstr(input, " < ");
			filename1 = position + 3;
			output = open(filename1, O_RDONLY);
			number_SC++;
			redi_stdin = 1;
			position = NULL;
		}
		//check if the string has <<
		if(strstr(input," << ")){
			position = strstr(input, " << ");
			filename1 = position + 4;
			output = open(filename1, O_RDONLY);
			number_SC++;
			redi_stdin = 1;
			position = NULL;
		}
		//check if the string has &
		if(strstr(input,"&")){
			number_SC++;
			backGround = 1;
		}

		//check if the string has |
		if(strstr(input," | ")){
			position = strstr(input, " | ");
			process2 = position;
			
			pipe(fd);

			number_SC++;
			pipeN = 1;
			pipeProcess = 1;

			command = strtok(process2, " \t\n");
			while(command != NULL){
				myargv1[myargc1] = command;
				command = strtok(NULL, " \t\n");
				myargc1++;
			}

			i = 0;
			while(myargv1[i+1]){
				myargv1[i] = myargv1[i+1];
				i++;
			}
			myargc1--;
			myargv1[myargc1] = NULL;
			position = NULL;
			
		}

		if(number_SC > 1){
			perror("Program does not support combination of more than 1 special charater.\n");
			return 1;
		}

		command = NULL;

		size = strlen(input);
		i = 0;
		j = 0;
		while(i < size){
			
			if(input[i] == '<' || input[i] == '>' || input[i] == '&' || input[i] == '|'){
				j = i;
			}
			if(j != 0){
				input[j++] = 0;
			}
			i++;
		}

		command = strtok(input," \t\n");
		
		while(command != NULL){
			myargv0[myargc0] = command;
			command = strtok(NULL, " \t\n");
			myargc0++;
		}	


		myargv0[myargc0] = NULL;

		c_pid = fork();
		
		if (c_pid < 0){
			perror("Fork failed.\n");
			return 1;
		}
		else if(c_pid == 0){

			if(redi_stdin){
				if(dup2(output,fileno(stdin)) < 0){
					perror("Can not redirect stdin.\n");
					return 1;
				}

			}

			if(redi_stdout){
				if(dup2(output,fileno(stdout)) < 0){
					perror("Can not redirect stdout.\n");
					return 1;
				}
			}

			if(redi_stderr){
				if(dup2(output, fileno(stderr)) < 0){
					perror("Can not redirect stderr.\n");
					return 1;
				}
			}

			if(pipeN){
				if(dup2(fd[1], fileno(stdout)) < 0){
					perror("Can not pipe.\n");
					return 1;
				}
			}

			if(execvp(myargv0[0],myargv0) < 0 ){
				perror("Execvp myargv0 Error.\n");
				return 1;
			}
			if(pipeN){
				close(fd[1]);
			}

		}
		else{
			
			if(!backGround){
				waitpid(c_pid,0,0);
			}
			if(pipeN){
				close(fd[1]);
			}
		}
		
		if(pipeN){
			
			c_pid = fork();
			
			if(c_pid == 0){
				if(dup2(fd[0], fileno(stdin)) < 0){
					perror("Failed to pipe.\n");
					return 1;
				}

				if(execvp(myargv1[0],myargv1) < 0){
					perror("Execvp myargv1 Error.\n");
					return 1;
				}

			}
			else if(c_pid < 0){
				perror("Fork failed.\n");
			}
			else{
				waitpid(c_pid,0,0);
				close(fd[0]);
			}

		}

	}
	
    return 0;
}


