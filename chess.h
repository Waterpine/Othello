#pragma once
#include<iostream>
#include<vector>
#include<cstdlib>
#include<memory.h>
#define LL unsigned long long
#define Board unsigned long long

using namespace std;

const int BOARD_WIDTH = 8;
const int BOARD_SIZE = 64;

const int VALUE[BOARD_SIZE] = {
	20, -3, 11,  8,  8, 11, -3, 20,
	-3, -7, -4,  1,  1, -4, -7, -3,
	11, -4,  2,  2,  2,  2, -4, 11,
	8,  1,  2, -3, -3,  2,  1,  8,
	8,  1,  2, -3, -3,  2,  1,  8,
	11, -4,  2,  2,  2,  2, -4, 11,
	-3, -7, -4,  1,  1, -4, -7, -3,
	20, -3, 11,  8,  8, 11, -3, 20,
};

inline int toSquare(int x, int y)
{
	return x * BOARD_WIDTH + y;
}

inline int getSquareX(int sq)
{
	return sq / BOARD_WIDTH;
}

inline int getSquareY(int sq)
{
	return sq % BOARD_WIDTH;
}

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
	int turn;
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

	bool equal(const chess & a){
		if(this->turn == a.turn;
		this->num == a.num;
		this->white == a.white;
		this->black == a.black;
		this->board[0]==a.board[0];
		this->board[1]==a.board[1];)
			return true;
		else return false;
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
	int getEval(int step = -1) const;
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

inline bool reversiEnv::isBlackPlayer() const
{
	return turn == 0;
}

inline bool reversiEnv::isWhitePlayer() const
{
	return turn == 1;
}

inline bool reversiEnv::isEmpty(int sq) const
{
	return !(board[0] >> sq & 1) && !(board[1] >> sq & 1);
}

inline bool reversiEnv::isMyPiece(int sq) const
{
	return board[turn] >> sq & 1;
}

inline bool reversiEnv::isOppPiece(int sq) const
{
	return board[turn ^ 1] >> sq & 1;
}

inline bool reversiEnv::isBlackPiece(int sq) const
{
	return board[0] >> sq & 1;
}

inline bool reversiEnv::isWhitePiece(int sq) const
{
	return board[1] >> sq & 1;
}

inline int reversiEnv::countAllPieces() const
{
	return popcount(board[0] | board[1]);
}

inline int reversiEnv::countBlackPieces() const
{
	return popcount(board[0]);
}

inline int reversiEnv::countWhitePieces() const
{
	return popcount(board[1]);
}

inline int reversiEnv::countMyPieces() const
{
	return popcount(board[turn]);
}

inline int reversiEnv::countOppPieces() const
{
	return popcount(board[turn ^ 1]);
}
