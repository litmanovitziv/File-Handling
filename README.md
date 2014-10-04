hexedit tool
============
A version of hexedit for working with binary files.  
The program hexeditplus receives a single command-line argument :  
./hexeditplus filename  
The argument filename is the file get used for various operations, defined below.  
  
A menu is defined for the user :  
File: <file name>, choose action:  
1-Display  
2-Display(ascii)  
3-Modify  
4-Copy from mem  
5-Copy from file  
6-Quit  
  
Each function described below should get filename as a parameter.  
If filename cannot be opened for reading and writing, the program prints an error message and exit.  
  
<table>
<tr>
<td>Name</td>
<td></td>
<td>User Arguments</td>
</tr>
<tr>
<td>Display</td>
<td>Display in hexadecimal list of bytes from the given file starting from given position</td>
<td>Desired file and two decimal numbers : length of list and starting location</td>
</tr>
<tr>
<td>Display(ascii)</td>
<td>Display in ASCII format list of bytes from the given file starting from given position</td>
<td>Desired file and two decimal numbers : length of list and starting location</td>
</tr>
<tr>
<td>Modify</td>
<td>Replace the byte at given location in the given file with the byte given value.</td>
<td>Desired file, location and value (in hexadecimal)</td>
</tr>
<tr>
<td>Copy from mem</td>
<td>Replace bytes at given location of targeted file with bytes from main memory of the current program at given location</td>
<td>target file and desired location (in hexadecimal), desired memory address (in hexadecimal), number of bytes to copy</td>
</tr>
<tr>
<td>Copy from file</td>
<td>Replace bytes at given location of targeted file with bytes from the source file at given location</td>
<td>source file and desired location (in hexadecimal), target file and desired location (in hexadecimal), number of bytes to copy</td>
</tr>
</table>

Implementation note:  
--------------------
The program use an array with the above menu names and pointers to a functions.  
