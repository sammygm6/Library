exe:	main.o recordFile.o Field.o Record.o  Menu.o Node.o index.o
		g++ Menu.o main.o recordFile.o Record.o Field.o Node.o index.o -o exe -lncurses
main.o:	main.cpp Menu.cpp recordFile.cpp Field.cpp index.cpp
		g++ -c main.cpp Menu.cpp recordFile.cpp Field.cpp index.cpp
Menu.o:	Menu.cpp 
		g++ -c Menu.cpp
recordFile.o:	recordFile.cpp Record.cpp Field.cpp index.cpp
		g++ -c recordFile.cpp Record.cpp Field.cpp index.cpp
Field.o:	Field.cpp
		g++ -c Field.cpp		
Record.o:	Record.cpp Field.cpp
		g++ -c Record.cpp Field.cpp
Node.o:	Node.cpp index.cpp
			g++ -c Node.cpp index.cpp
index.o:	index.cpp
			g++ -c index.cpp			
