#Author: Josh Chisholm (100770668)
OBJ = main.o fileobj.o log.o

jtunes:	$(OBJ)
	g++ -o jtunes $(OBJ)

main.o:	main.cpp
	g++ -c main.cpp

fileobj.o: fileobj.cpp fileobj.h
	g++ -c fileobj.cpp

log.o: log.cpp log.h
		g++ -c log.cpp

clean:
	rm -f $(OBJ) jtunes
