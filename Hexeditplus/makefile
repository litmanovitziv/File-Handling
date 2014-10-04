OPERATIONS := $(patsubst %.c,%,$(wildcard Operations/*.c))

all: $(OPERATIONS) hexeditplus

%: %.c
	gcc -m32 -g -Wall -o $@ $<

hexeditplus: ../library/LineParser.o hexeditplus.c
	gcc -g -m32 -ansi -Wall -c ../library/LineParser.o hexeditplus.c -o hexeditplus.o
	gcc -m32 -Wall ../library/LineParser.o hexeditplus.o -o hexeditplus

../library/LineParser.o:
	gcc -m32 -g -ansi -Wall -c ../library/LineParser.c -o ../library/LineParser.o

is_pal: is_pal.c
	gcc -g -m32 -ansi -Wall -c is_pal.c -o is_pal.o
	gcc -g -m32 -ansi -Wall is_pal.o -o is_pal

clean:
	\rm *.o *~ hexeditplus $(OPERATIONS)
