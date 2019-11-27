#Author: Josh Chisholm (100770668)
OBJ = main.o fileobj.o log.o dal.o sqlite3.o sharedFunctions.o database.o

jtunes:	$(OBJ)
	g++ -o jtunes $(OBJ) -lpthread -ldl

main.o:	main.cpp
	g++ -c main.cpp

fileobj.o: fileobj.cpp fileobj.h
	g++ -c fileobj.cpp

log.o: log.cpp log.h
		g++ -c log.cpp

dal.o: dal.cpp dal.h
		g++ -c dal.cpp

sqlite3.o: sqlite3.c sqlite3.h
		gcc -c sqlite3.c

sharedFunctions.o: sharedFunctions.cpp sharedFunctions.h
		g++ -c sharedFunctions.cpp

database.o: database.cpp database.h
		g++ -c database.cpp

clean:
	rm -f $(OBJ) jtunes
