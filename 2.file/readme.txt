# csc415-a2

- Student Name : Arnold Jiadong Yu      

- Student ID : 917269189

	The file name is file_copy.c. Type gcc file_copy.c in command line under its directory. This will compile the c file. The output file generated is called a.out. Then type ./a.out to run the program. 
	This program takes input as a input file name, and an output file name. It copies the contexts from input file to output file. If the output file already exists, it will print out error.

The input and output looks like this.

Welcome to the File Copy Program by Arnold Jiadong Yu!
Enter the name of the file to copy from:
test1.txt       
Enter the name of the file to copy to:
result2.txt
File Copy Successful, 210 bytes copied.

Welcome to the File Copy Program by Arnold Jiadong Yu!
Enter the name of the file to copy from:
test1.txt
Enter the name of the file to copy to:
result2.txt
Output file open error.: File exists

I can not figure out how dtrace work on mac. I ended up using school server to use strace.
Here is the output I get.



jyu13@thecity:~/csc415/2$ strace -c ./a.out       
Welcome to the File Copy Program by Arnold Jiadong Yu!
Enter the name of the file to copy from:
test.txt
Enter the name of the file to copy to:
result.txt
File Copy Successful, 150887 bytes copieProcess 9684 detached
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 52.78    0.000228           0      5593           read               //it takes 5593 times to load into the readBuffer
 47.22    0.000204           0      5594           write              //it write 5593 with words and last call of write writes nothing
  0.00    0.000000           0         4           open               //open calls twice on each file
  0.00    0.000000           0         4           close              //close calls twice on each file
  0.00    0.000000           0         1           execve	      //other calls I don’t really understand.	
  0.00    0.000000           0         3         3 access
  0.00    0.000000           0         1           brk
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         1           mprotect
  0.00    0.000000           0         7           mmap2
  0.00    0.000000           0         3           fstat64
  0.00    0.000000           0         1           set_thread_area
------ ----------- ----------- --------- --------- ----------------
100.00    0.000432                 11213         3 total
jyu13@thecity:~/csc415/2$ diff test.txt result.tt                              
diff: result.tt: No such file or directory
jyu13@thecity:~/csc415/2$ diff test.txt result.txt
jyu13@thecity:~/csc415/2$ 
