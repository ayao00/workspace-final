all: driver.o
	gcc play.c board.c driver.c -o driver

driver.o: driver.c
	gcc -c -g driver.c

board.o: board.c board.h
	gcc -c -g board.c

play.o: play.c play.h
	gcc -c -g play.c

run:
	./driver

clean:
		rm *.out
		rm *~
