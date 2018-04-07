all: readelf

readelf: ../library/linked_list.o ELFreader.o
	gcc -m32 -g -Wall -o $@ ../library/linked_list.o ELFreader.o
	bash test

ELFreader.o: ELFreader.h ELFreader.c
	gcc -m32 -g -ansi -Wall -c ELFreader.c -o $@

mapping.o:
	gcc -m32 -g -ansi -Wall -c $< -o $@

../library/linked_list.o:
	gcc -m32 -g -ansi -Wall -c ../library/linked_list.c -o ../library/linked_list.o

clean:
	\rm ../library/*.o *.o readelf
	\rm -dr Tests/Results
