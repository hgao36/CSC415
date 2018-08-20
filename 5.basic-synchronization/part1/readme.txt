Name  : Arnold Jiadong Yu
Date  :	Nov-11-2017
Class : CSC415-02

Compile Instructions:
type “make” on command line

Run Instructions:
type “./threadracer” on command line.

Project Description:

This project demonstrate how to use mutex lock to ensure no race condition. It is based on  assignment 4 and added mutex lock into it.


output:
Thread Program for test lock to fix the race condition -> executing.
Hello, I am thread # 1 .
Hello, I am thread # 2 .
Hello, I am thread # 4 .
Hello, I am thread # 3 .
Hello, I am thread # 5 .
Hello, I am thread # 6 .
Hello, I am thread # 7 .
Hello, I am thread # 8 .
Hello, I am thread # 9 .
Hello, I am thread # 10 .                  <-lock after this
This is thread # 1 with local value: 0.
This is thread # 1 with final local value: 10.
This is thread # 2 with local value: 10.
This is thread # 2 with final local value: 20.
This is thread # 4 with local value: 20.
This is thread # 4 with final local value: 30.
This is thread # 3 with local value: 30.
This is thread # 3 with final local value: 40.
This is thread # 5 with local value: 40.
This is thread # 5 with final local value: 50.
This is thread # 6 with local value: 50.
This is thread # 6 with final local value: 60.
This is thread # 7 with local value: 60.
This is thread # 7 with final local value: 70.
This is thread # 8 with local value: 70.
This is thread # 8 with final local value: 80.
This is thread # 9 with local value: 80.
This is thread # 9 with final local value: 90.
This is thread # 10 with local value: 90.
This is thread # 10 with final local value: 100.  <- unlock after increment 10 and write to global variable
Result is 100
