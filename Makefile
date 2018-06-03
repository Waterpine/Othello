chess:main.o chess.o MTCS.o
	cc -o chess main.o chess.o MTCS.o -lstdc++
chess.o:chess.h chess.cpp
	cc -c chess.cpp
main.o:main.cpp chess.h
	cc -c main.cpp
MTCS.o:chess.h MTCS.h MTCS.cpp timer.h
	cc -c MTCS.cpp
