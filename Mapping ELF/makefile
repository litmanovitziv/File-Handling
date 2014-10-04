all: examine

examine: ../library/linked_list.o mapping.o
	gcc -m32 -g -Wall ../library/linked_list.o mapping.o -o examine
	bash test

mapping.o:
	gcc -m32 -g -ansi -Wall -c mapping.c -o mapping.o

../library/linked_list.o:
	gcc -m32 -g -ansi -Wall -c ../library/linked_list.c -o ../library/linked_list.o

clean:
	\rm ../library/*.o *.o *~ examine