SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	gcc kingdom.o -o kingdom
	make clean

.PHONY : clean cleanexe


clean:
	@-rm *.o

cleanexe:
	@-rm hw000?