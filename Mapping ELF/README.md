ELF Parsing
===========
In this chapter we’ll extract the structure of a 32bit ELF file.  
Write a program which gets same command-line arguments, ELF-format files :  
	examine INFILE’s  
All input files is read/written data using the mmap system call.  
  
Notes
1. The program should include elf.h, which contains all the typedefs and constant definitions for handling ELF files.  
2. Check correctness of data using "readelf".  
  
Task 1 : Header
---------------
Prints the following information from the header (all addresses should be in hexadecimal, unless stated otherwise) :
1. Magic number (in ASCII). Henceforth, you should check that the number is consistent with an ELF file. and refuse to continue if a non-ELF file is invoked, your program should print an error message, and exit.  
2. Type  
3. Entry point (in hexadecimal)  
4. e_shstrndx  
5. The number of section header entries  
6. The number of program header entries  
7. The file offset in which the section header table resides.  
8. Is this a 64bit or 32bit ELF file.  
  
Task 2 : Sections
-----------------
Prints all the Section names in an 32 bit ELF file (like readelf -S).
Your program should exit if invoked on a non 32 bit ELF file.
Your program should go over all sections in the sections table, and for each one print its name, index, type and size in bytes.
The format of each record should be :  
[index] section_name section_type section_size  
  
Verify your output is correct by comparing it to the output of readelf.
You can test your code on the following file: [cat](http://www.cs.bgu.ac.il/~caspl122/wiki.files/lab8/cat).  
Hints: Global information about the ELF file is in the ELF header, including location and size of important tables. The size and name of the sections appear in the section header table.
Recall that the actual name strings are stored in an appropriate section (shstrtab for section names), and not in the section header !  
  
Task 3 : Symbols
----------------
Using your program from previous task as a starting point. You should now write a program which prints all the symbol names in a 32 bit ELF file. For each symbol, print its index number, its name and the name of the section in which it is defined. (similar to readelf -s).  
The format of each record should be : [index] symbol_name section_name  
  
Verify your output is correct by comparing it to the output of readelf.  
Your program should exit if invoked on a non 32 bit ELF file.  
Hints: Symbols are listed in the .symtab section. The section in which a symbol is defined (if it is defined) is the index of the symbol, which is an index into the section header table, referring to the section header of the appropriate section, and from there the section name can be retrieved as above. Symbol name is an attribute of the symbol structure, but recall again that the actual name string is stored in a string table, a separate section (.strtab).  
  
Task 4 : Can the files be linked ?
----------------------------------
Before the linker (ld) tries to link object files, it verifies that all the information it needs is available in the files. In this task, you will implement this functionality of the linker.
Write a program can_link getting as arguments 2 32 bit object files :  
	can_link file1 file2  
  
Each of the following tasks will add a check to your program.  
If all checks pass, your program should exit with 0 return code.  
If a check failed, you should print the reason for the failure and exit with a -1 return code.  
If one of the files is not a 32 bit object file, your program should print an error message and exit with an exit code of -2.  
Simplifying assumptions : you may use an array for symbols, and may assume that the number of symbols is less than 10000.  
Extra : handle any number of files and unbounded number of symbols.  
  
Task 4a : main function
-----------------------
At least one of the linked files should contain a symbol for the main function. If such a symbol exists, your program should write : main check: PASSED.  
Otherwise, it should write : main check: FAILED and exit with a code of -1.  
To test your program, you can use the following object files: hasmain.o, nomain.o.  
The first should pass the test, and the second should not.  
  
Task 4b : duplicate symbols
---------------------------
Each symbol should be defined only once in all the files. Add this check to your program.  
If the same symbol is defined in more than one object file, your program should print :  
duplicate check: FAILED (symbolname)and exit with a code of -1.  
otherwise (no duplicate symbols), your program should print :  
duplicate check: PASSED  
Think : which piece of code from previous labs can help you in this task ?  
You can test your program with the following files : b1.o, b2.o, b3.o  
	can_link b1.o b3.o  
	can_link b1.o b2.o  

Task 4c : undefined symbols
---------------------------
If a symbol is needed (in the symbol table, but "undefined") in one of the object files, it should be present in one of the others. Your program should verify that.  
For each undefined symbol appearing in one of the object files, you should verify that it is defined in one of the object files. Otherwise, this symbol is considered missing (undefined).  
If you find a missing symbol, your program should print :  
no missing symbols: FAILED (symbolname)and exit with a code of -1.  
otherwise (no duplicate symbols), your program should print :  
no missing symbols: PASSED  
  
You can test your program with the following files : c1.o, c2.o  
	can_link c1.o c2.o  
	can_link b1.o b2.o  

