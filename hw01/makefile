SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	gcc calculate.o -o calculate -lm
	gcc purple_cow.o -o purple_cow
	gcc purple_cow_nodebug.c -o purple_cow_nodebug
	make clean

.PHONY : new zip clean cleanexe

new:
	cp ../template.c hw0.c
	code hw0.c

clean:
	@-rm *.o

cleanexe:
	@-rm hw000?