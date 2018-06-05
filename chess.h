#pragma once
#include<iostream>
#include<vector>
#include<cstdlib>


struct position
{
	char row, col;
	char left, right, up, down, leftup, leftdown, rightup, rightdown;
	char num;
	position() :row(0), col(0), left(0), right(0), up(0), down(0), leftup(0), leftdown(0), rightup(0), rightdown(0), num(0) {};
};

class chess
{
private:
	char board[10][10];
	char turn;
	char num;
	char white, black;
public:
	chess():turn(1),num(4),white(2), black(2)
	{
		memset(board, 0, sizeof(char) * 100);
		//white
		board[4][4] = board[5][5] = 2;
		//black
		board[4][5] = board[5][4] = 1;
	}
	chess(const chess & a)
	{
		this->turn = a.turn;
		this->num = a.num;
		this->white = a.white;
		this->black = a.black;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				this->board[i][j] = a.board[i][j];
			}
		}
	}
	//receive data
	void set_board(char** board);
	//receive turn
	void set_turn(char turn);
	//get turn
	char get_turn();
	//print the chess board
	void print();
	//search the board and get the number of black
	void set_black();
	//search the board and get the number of white
	void set_white();
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
};

inline void chess::set_black()
{
	char cnt = 0;
	for (int i = 1; i <= 8; i++)
		for (int j = 0; j <= 8; j++)
			if (board[i][j] == 1)
				cnt++;
	black = cnt;
}

inline void chess::set_white()
{
	char cnt = 0;
	for (int i = 1; i <= 8; i++)
		for (int j = 0; j <= 8; j++)
			if (board[i][j] == 2)
				cnt++;
	white = cnt;
}

inline char chess::get_black()
{
	return black;
}

inline char chess::get_white()
{
	return white;
}

inline void chess::set_board(char** board)
{
	memset(board, 0, sizeof(char) * 100);
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
			this->board[i][j] = board[i - 1][j - 1];
}

inline void chess::set_turn(char turn)
{
	this->turn = turn;
}

inline char chess::get_turn()
{
	return turn;
}
