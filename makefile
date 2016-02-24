exe:	editorial.o libro.o
		g++ editorial.o libro.o -o exe

editorial.o:	editorial.cpp
		g++ -c editorial.cpp

libro.o:		libro.cpp
		g++ -c libro.cpp

clean:
		rm *.o 
