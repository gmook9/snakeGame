
worm.x:  main.o getChar.o cell.o worm.o
	g++ -ggdb -o worm.x main.o getChar.o cell.o worm.o -lcurses -ltermcap

main.o: main.cpp
	g++ -c -ggdb main.cpp -o main.o

getChar.o: getChar.cpp 
	gcc -c -ggdb getChar.cpp -o getChar.o

cell.o: cell.cpp 
	g++ -c -ggdb cell.cpp -o cell.o
	
worm.o: worm.cpp 
	g++ -c -ggdb worm.cpp -o worm.o

clean:
	/bin/rm -f worm.x main.o getChar.o cell.o worm.o *~
