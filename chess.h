#pragma once
#include<iostream>
#include<vector>
#include<cstdlib>
#include<cstring>
using namespace std;


struct position
{
	int row, col;
	int left, right, up, down, leftup, leftdown, rightup, rightdown;
	int num;
	position() :row(0), col(0), left(0), right(0), up(0), down(0), leftup(0), leftdown(0), rightup(0), rightdown(0), num(0) {};
};

class chess
{
private:
	int board[10][10];
	int turn;
	int num;
public:
	chess():turn(1), num(4)
	{
		memset(board, 0, sizeof(int) * 100);
		board[4][4] = board[5][5] = 2;
		board[4][5] = board[5][4] = 1;
	}
	//print the chess board
	void print();
	//check if this position can be put 
	struct position check(int row, int col);
	//find all possible position that you can put
	vector<struct position> findall();
	//put a chessman, this function will change turn automatically
	void put(struct position &pos);
	//find the position with max num
	struct position find_max(vector<struct position> r);
	//find the optimal position to put down the chessman
	struct position search(vector<struct position> pos);
};
