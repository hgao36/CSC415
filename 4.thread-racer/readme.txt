Name  : Arnold Jiadong Yu	
Date  : Oct -28 -2017
Class : CSC 415-02

Compile Instructions:
type “make” on command line

Run Instructions:
type “./threadracer” on command line.

Project Description:

This project test create 10 threads, and give each thread a task which is to add 10. Then implement nanosleep method to create race condition. 


Thread Program for test race condition executing.
Hello, I am thread # 1 .
Hello, I am thread # 2 .
Hello, I am thread # 3 .
Hello, I am thread # 4 .
Hello, I am thread # 5 .
Hello, I am thread # 6 .
Hello, I am thread # 7 .
Hello, I am thread # 8 .
Hello, I am thread # 9 .
Hello, I am thread # 10 . <-Every thread reads zero from global since every thread was put to sleep afterwards and didn’t update the global variable. This is race condition that every thread reads from the same value.
This is thread # 2 with local value: 0.
This is thread # 3 with local value: 0.
This is thread # 4 with local value: 0.
This is thread # 5 with local value: 0.
This is thread # 1 with local value: 0.
This is thread # 6 with local value: 0.
This is thread # 7 with local value: 0.
This is thread # 9 with local value: 0.
This is thread # 8 with local value: 0.
This is thread # 10 with local value: 0.         
This is thread # 2 with final local value: 10.
This is thread # 3 with final local value: 10.
This is thread # 4 with final local value: 10.
This is thread # 5 with final local value: 10.
This is thread # 1 with final local value: 10.
This is thread # 6 with final local value: 10.
This is thread # 7 with final local value: 10.
This is thread # 9 with final local value: 10.
This is thread # 8 with final local value: 10.
This is thread # 10 with final local value: 10.<— This is the race condition happens, that every threads updates local variable by 10 and they try to put 10 in global at the same time. The global is the same data field that all 10 threads try to write at the same time. It just updates. This is a race condition. Thus the final result is just 10.
Result is 10