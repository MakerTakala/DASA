SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	gcc hw0104.o -o hw0104
	make clean

.PHONY : new zip clean cleanexe

new:
	cp ../template.c hw0.c
	code hw0.c

clean:
	@-rm *.o

cleanexe:
	@-rm hw000?