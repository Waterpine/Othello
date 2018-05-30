chess:main.o chess.o
	cc -o chess main.o chess.o -lstdc++
chess.o:chess.h chess.cpp
	cc -c chess.cpp
main.o:main.cpp chess.h
	cc -c main.cpp

