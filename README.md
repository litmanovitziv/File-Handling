hexedit tool
============
In this task we will write our own version of hexedit for working with binary files.
Write a program hexeditplus which receives a single command-line argument :
./hexeditplus filename
The argument filename is the file get used for various operations, defined below.

First, define a menu for the user with a number of predefined functions, to which we will add functions as we go.

For example, the command line ./hexeditplus abc Will print :
File: <file name>, choose action:
1-Display
2-Display(ascii)
3-Modify
4-Copy from mem
5-Copy from file
6-Quit
Use an array with the above menu names and pointers to a functions.
Each function described below should get filename as a parameter
If filename cannot be opened for reading and writing print an error message and exit.

Name


User Arguments
Display
Display in hexadecimal list of bytes from the given file starting from given position
Desired file and two decimal numbers : length of list and starting location
Display(ascii)
Display in ASCII format list of bytes from the given file starting from given position
Desired file and two decimal numbers : length of list and starting location
Modify
Replace the byte at given location in the given file with the byte given value.
Desired file, location and value (in hexadecimal)
Copy from mem
Replace bytes at given location of targeted file with bytes from main memory of the current program at given location
target file and desired location (in hexadecimal), 
desired memory address (in hexadecimal), number of bytes to copy
Copy from file
Replace bytes at given location of targeted file with bytes from the source file at given location
source file and desired location (in hexadecimal), target file and desired location (in hexadecimal), number of bytes to copy

