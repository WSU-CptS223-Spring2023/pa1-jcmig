prog: main.o linuxgame.o
	g++ -g main.o linuxgame.o -o PA1

main.o: main.cpp linuxgame.h
	g++ -c -g -Wall -std=c++11  main.cpp 

linuxgame.o: linuxgame.cpp linuxgame.h
	g++ -c -g -Wall -std=c++11 linuxgame.cpp 



clean: 
	-rm *.o

run:
	@./PA1