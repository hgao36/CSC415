Name  : Arnold Jiadong Yu
Date  : 10-07-2017
Class : csc415-02

Compile Instructions:
run the following command on terminal in the right directory.

gcc myshell.c

Run Instructions:
run the following command on terminal in the right directory.

./a.out

Project Description:
This program is a simple shell program that works similar as bash. It takes the input and splits into tokens. This program
support redirect output and input, as well as background and pipe command. Below are the input and output that programs does:

MyShell> ls
415_HW3.pdf	LICENSE		README.md	file		readme.txt
CMakeLists.txt	Makefile	a.out		myshell.c
MyShell> ls -l
total 1120
-rw-r--r--@ 1 Arnold  staff  521904 Oct  7 17:34 415_HW3.pdf
-rw-r--r--  1 Arnold  staff     152 Oct  2 19:31 CMakeLists.txt
-rw-r--r--  1 Arnold  staff    1072 Oct  2 19:31 LICENSE
-rw-r--r--  1 Arnold  staff      74 Oct  2 19:31 Makefile
-rw-r--r--  1 Arnold  staff      11 Oct  2 19:31 README.md
-rwxr-xr-x  1 Arnold  staff   13416 Oct 14 15:52 a.out
-rw-------  1 Arnold  staff    1076 Oct 12 21:29 file
-rw-r--r--  1 Arnold  staff    5301 Oct 14 15:53 myshell.c
-rw-r--r--@ 1 Arnold  staff     609 Oct 14 16:04 readme.txt
MyShell> ls -la > myfile.txt
MyShell> cat myfile.txt
total 1144
drwxr-xr-x  15 Arnold  staff     510 Oct 14 16:04 .
drwxr-xr-x   4 Arnold  staff     136 Oct  2 19:32 ..
-rw-r--r--@  1 Arnold  staff    6148 Oct 12 19:29 .DS_Store
drwxr-xr-x  14 Arnold  staff     476 Oct 14 15:53 .git
-rw-r--r--   1 Arnold  staff     430 Oct  2 19:31 .gitignore
-rw-r--r--@  1 Arnold  staff  521904 Oct  7 17:34 415_HW3.pdf
-rw-r--r--   1 Arnold  staff     152 Oct  2 19:31 CMakeLists.txt
-rw-r--r--   1 Arnold  staff    1072 Oct  2 19:31 LICENSE
-rw-r--r--   1 Arnold  staff      74 Oct  2 19:31 Makefile
-rw-r--r--   1 Arnold  staff      11 Oct  2 19:31 README.md
-rwxr-xr-x   1 Arnold  staff   13416 Oct 14 15:52 a.out
-rw-------   1 Arnold  staff    1076 Oct 12 21:29 file
-rw-------   1 Arnold  staff       0 Oct 14 16:04 myfile.txt
-rw-r--r--   1 Arnold  staff    5301 Oct 14 15:53 myshell.c
-rw-r--r--@  1 Arnold  staff    1263 Oct 14 16:04 readme.txt
MyShell> ls -la >> myfile.txt
MyShell> cat myfile.txt
total 1144
drwxr-xr-x  15 Arnold  staff     510 Oct 14 16:04 .
drwxr-xr-x   4 Arnold  staff     136 Oct  2 19:32 ..
-rw-r--r--@  1 Arnold  staff    6148 Oct 12 19:29 .DS_Store
drwxr-xr-x  14 Arnold  staff     476 Oct 14 15:53 .git
-rw-r--r--   1 Arnold  staff     430 Oct  2 19:31 .gitignore
-rw-r--r--@  1 Arnold  staff  521904 Oct  7 17:34 415_HW3.pdf
-rw-r--r--   1 Arnold  staff     152 Oct  2 19:31 CMakeLists.txt
-rw-r--r--   1 Arnold  staff    1072 Oct  2 19:31 LICENSE
-rw-r--r--   1 Arnold  staff      74 Oct  2 19:31 Makefile
-rw-r--r--   1 Arnold  staff      11 Oct  2 19:31 README.md
-rwxr-xr-x   1 Arnold  staff   13416 Oct 14 15:52 a.out
-rw-------   1 Arnold  staff    1076 Oct 12 21:29 file
-rw-------   1 Arnold  staff       0 Oct 14 16:04 myfile.txt
-rw-r--r--   1 Arnold  staff    5301 Oct 14 15:53 myshell.c
-rw-r--r--@  1 Arnold  staff    1263 Oct 14 16:04 readme.txt
total 1152
drwxr-xr-x  15 Arnold  staff     510 Oct 14 16:05 .
drwxr-xr-x   4 Arnold  staff     136 Oct  2 19:32 ..
-rw-r--r--@  1 Arnold  staff    6148 Oct 12 19:29 .DS_Store
drwxr-xr-x  14 Arnold  staff     476 Oct 14 15:53 .git
-rw-r--r--   1 Arnold  staff     430 Oct  2 19:31 .gitignore
-rw-r--r--@  1 Arnold  staff  521904 Oct  7 17:34 415_HW3.pdf
-rw-r--r--   1 Arnold  staff     152 Oct  2 19:31 CMakeLists.txt
-rw-r--r--   1 Arnold  staff    1072 Oct  2 19:31 LICENSE
-rw-r--r--   1 Arnold  staff      74 Oct  2 19:31 Makefile
-rw-r--r--   1 Arnold  staff      11 Oct  2 19:31 README.md
-rwxr-xr-x   1 Arnold  staff   13416 Oct 14 15:52 a.out
-rw-------   1 Arnold  staff    1076 Oct 12 21:29 file
-rw-------   1 Arnold  staff     889 Oct 14 16:04 myfile.txt
-rw-r--r--   1 Arnold  staff    5301 Oct 14 15:53 myshell.c
-rw-r--r--@  1 Arnold  staff    2205 Oct 14 16:05 readme.txt
MyShell> ls -l | sort -r
total 1128
-rwxr-xr-x  1 Arnold  staff   13416 Oct 14 15:52 a.out
-rw-r--r--@ 1 Arnold  staff  521904 Oct  7 17:34 415_HW3.pdf
-rw-r--r--@ 1 Arnold  staff    4037 Oct 14 16:06 readme.txt
-rw-r--r--  1 Arnold  staff    5301 Oct 14 15:53 myshell.c
-rw-r--r--  1 Arnold  staff    1072 Oct  2 19:31 LICENSE
-rw-r--r--  1 Arnold  staff     152 Oct  2 19:31 CMakeLists.txt
-rw-r--r--  1 Arnold  staff      74 Oct  2 19:31 Makefile
-rw-r--r--  1 Arnold  staff      11 Oct  2 19:31 README.md
-rw-------  1 Arnold  staff    1778 Oct 14 16:05 myfile.txt
-rw-------  1 Arnold  staff    1076 Oct 12 21:29 file
MyShell> ls -l &
MyShell> total 1136
-rw-r--r--@ 1 Arnold  staff  521904 Oct  7 17:34 415_HW3.pdf
-rw-r--r--  1 Arnold  staff     152 Oct  2 19:31 CMakeLists.txt
-rw-r--r--  1 Arnold  staff    1072 Oct  2 19:31 LICENSE
-rw-r--r--  1 Arnold  staff      74 Oct  2 19:31 Makefile
-rw-r--r--  1 Arnold  staff      11 Oct  2 19:31 README.md
-rwxr-xr-x  1 Arnold  staff   13416 Oct 14 15:52 a.out
-rw-------  1 Arnold  staff    1076 Oct 12 21:29 file
-rw-------  1 Arnold  staff    1778 Oct 14 16:05 myfile.txt
-rw-r--r--  1 Arnold  staff    5301 Oct 14 15:53 myshell.c
-rw-r--r--@ 1 Arnold  staff    4660 Oct 14 16:06 readme.txt

MyShell>exit


Extra Credit Deescription: <if not attempted leave this here, otherwise replace>
