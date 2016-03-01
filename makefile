exe:	main.o editorial.o libro.o
		g++ main.o editorial.o libro.o -o exe

main.o:	main.cpp
		g++ -c main.cpp

editorial.o:	editorial.cpp
		g++ -c editorial.cpp

libro.o:	libro.cpp
		g++ -c libro.cpp

clean:
		rm *.o
		rm exe