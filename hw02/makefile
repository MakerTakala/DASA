SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	gcc kingdom.o -o kingdom
	gcc stock.o -o stock
	make clean

.PHONY : clean cleanexe


clean:
	@-rm *.o

cleanexe:
	@-rm hw000?