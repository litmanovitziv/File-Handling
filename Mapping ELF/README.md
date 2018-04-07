ELF Reader
==========
This Reader extracts the structure of a 32bit ELF file.  
The reader gets at least one command-line argument, ELF-format file :  
	examine INFILE’s  

*****Implamentation Notes*****  
1. The reader makes use of elf.h file, which contains all the typedefs and constant definitions for handling ELF files.  
2. All input files is read/write data using the mmap system call.  

Header (readelf -h)
-------------------
Displays the information contained in the ELF header at the start of the file.
Prints the following information from the header (all addresses should be in hexadecimal, unless stated otherwise) :  
1. Magic number (in ASCII). Henceforth, you should check that the number is consistent with an ELF file. and refuse to continue if a non-ELF file is invoked, your program should print an error message, and exit.  
2. Type  
3. Entry point (in hexadecimal)  
4. e_shstrndx  
5. The number of section header entries  
6. The number of program header entries  
7. The file offset in which the section header table resides.  
8. Is this a 64bit or 32bit ELF file.  

Sections (readelf -t)
------------------
Displays information contained in the file's section headers.  
For each section, display its name, its index, its type and its size in bytes.  

Global information about the ELF file is in the ELF header, including location and size of important tables. The size and name of the sections appear in the section header table. Notice, The actual name strings are stored in an appropriate section (shstrtab for section names).  

Symbols (readelf -s)
--------------------
Displays all the symbol names in the file.  
For each symbol, display its index number, its name and the name of the section in which it is defined.  

Symbols are listed in the .symtab section. The section in which a symbol is defined (if it is defined) is the index of the symbol, which is an index into the section header table, referring to the section header of the appropriate section, and from there the section name can be retrieved as above. Symbol name is an attribute of the symbol structure. Notice, the actual name string is stored in a string table, a separate section (.strtab).  
