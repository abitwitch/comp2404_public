#Author: Josh Chisholm (100770668)
OBJ = main.o fileobj.o log.o recording.o track.o song.o playlist.o user.o dal.o

jtunes:	$(OBJ)
	g++ -o jtunes $(OBJ)

main.o:	main.cpp
	g++ -c main.cpp

fileobj.o: fileobj.cpp fileobj.h
	g++ -c fileobj.cpp

log.o: log.cpp log.h
		g++ -c log.cpp

recording.o: recording.cpp recording.h
		g++ -c recording.cpp

track.o: track.cpp track.h
		g++ -c track.cpp

song.o: song.cpp song.h
		g++ -c song.cpp

playlist.o: playlist.cpp playlist.h
		g++ -c playlist.cpp

user.o: user.cpp user.h
		g++ -c user.cpp

dal.o: dal.cpp dal.h
				g++ -c dal.cpp

clean:
	rm -f $(OBJ) jtunes
