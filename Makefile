
chess:main.o chess.o MCTS.o
	cc -o chess main.o chess.o MCTS.o -lstdc++ -lm
chess.o:chess.h chess.cpp
	cc -c -std=c++11 chess.cpp 
main.o:main.cpp chess.h
	cc -c -std=c++11 main.cpp
MCTS.o:chess.h MCTS.h MCTS.cpp timer.h
	cc -c -std=c++11 MCTS.cpp