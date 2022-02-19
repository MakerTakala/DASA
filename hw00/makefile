SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	gcc hw0001.o -o hw0001
	gcc hw0003a.o -o hw0003a
	gcc hw0003b.o -o hw0003b
	gcc hw0003c.o -o hw0003c
	gcc hw0003d.o -o hw0003d
	make clean

.PHONY : new zip clean cleanexe

new:
	cp ../template.c hw0.c
	code hw0.c

clean:
	@-rm *.o

cleanexe:
	@-rm hw000?