#pragma once
#include<iostream>
#include<vector>
#include<cstdlib>
#include<memory.h>
#define LL unsigned long long
#define Board unsigned long long

using namespace std;

struct position
{
	char row, col;
	char left, right, up, down, leftup, leftdown, rightup, rightdown;
	char num;
	position() :row(0), col(0), left(0), right(0), up(0), down(0), leftup(0), leftdown(0), rightup(0), rightdown(0), num(0) {};
};

class chess
{
//private:
public:
	unsigned long long board[2];
	char turn;
	char num;
	char white, black;
	chess():turn(0),num(4),white(2), black(2)
	{
		board[0]=0x0000001008000000;
		board[1]=0x0000000810000000;

	}
	chess(const chess & a)
	{
		this->turn = a.turn;
		this->num = a.num;
		this->white = a.white;
		this->black = a.black;
		this->board[0]=a.board[0];
		this->board[1]=a.board[1];
	}

	inline int popcount(Board x)
	{
	#ifdef _MSC_VER
		return __popcnt64(x);
	#else
		return __builtin_popcountll(x);
	#endif
	}

	inline int countBlackPieces()
	{
		return popcount(board[0]);
	}

	inline int countWhitePieces()
	{
		return popcount(board[1]);
	}

	//receive turn
	void set_turn(char turn);
	// get num
	char get_num();
	//get turn
	char get_turn();
	//print the chess board
	void print();
	//get the black chessman number
	char get_black();
	//get the white chessman number
	char get_white();
	//check if this position can be put 
	struct position check(int row, int col);
	//find all possible position that you can put
	std::vector<struct position> findall();
	//put a chessman, this function will change turn automatically
	void put(struct position &pos);
	//find the position with max num
	struct position find_max(std::vector<struct position> r);
  bool is_gameover();
};

inline char chess::get_num()
{
	return num;
}

inline char chess::get_black()
{
	return countBlackPieces();
}

inline char chess::get_white()
{
	return countWhitePieces();
}



inline char chess::get_turn()
{
	return turn;
}
