# csc415-a1

- Student Name : Arnold Jiadong Yu      


First, I used #define to define my name as global variable. Initial char buffer as 50 to store string inside.
Creat integer n to store number of bytes will be stored in buffer. Next used springf() to format output and used if statement to output write() function in order to write the buffer to console. 

In order to run the program, I used gcc hello.c. After complied the file, I used ./a.out to run it, but it showed Abort trap 6 error. After research, I found out it was the buffer cannot store all bytes. So increase to 60.

This program basically print out "CSC 415, This program written by Arnold Jiadong Yu !"
