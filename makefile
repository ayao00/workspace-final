all: driver.o
	gcc play.c board.c driver.c -o driver

driver.o: driver.c
	gcc -c -g driver.c

board.o: board.c board.h
	gcc -c -g board.c

play.o: play.c play.h
	gcc -c -g play.c

forking: client fserver

select: sclient sserver

sserver: select_server.o networking.o
	gcc -o server select_server.o networking.o

fserver: forking_server.o networking.o
	gcc -o server forking_server.o networking.o

sclient: select_client.o networking.o
	gcc -o client select_client.o networking.o

client: client.o networking.o board.o play.o
	gcc -o client client.o networking.o board.o play.o

select_client.o: select_client.c networking.h
	gcc -c select_client.c

client.o: client.c networking.h board.h play.h
	gcc -c client.c

select_server.o: select_server.c networking.h
	gcc -c select_server.c

forking_server.o: forking_server.c networking.h
	gcc -c forking_server.c

networking.o: networking.c networking.h
	gcc -c networking.c


run:
	./driver

clean:
		rm *.out
		rm *~
