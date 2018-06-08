#pragma once
#include"chess.h"

//receive a string and return the board
char** parse_board(const std::string &src)
{
	char **board = new char* [8];
	int cnt = 0, i = 0;
	for (int i = 0; i < 8; i++)
	{
		board[i] = new char[8];
	}
	while (cnt < 64)
	{
		if (src[i] != '.' && src[i] != ';')
		{
			if (src[i] == 'W')
				board[cnt / 8][cnt % 8] = 1;
			else if (src[i] == 'B')
				board[cnt / 8][cnt % 8] = 2;
			else
				board[cnt / 8][cnt % 8] = src[i];
			cnt++;
		}
		i++;
	}
	return board;
}

char parse_turn(char turn)
{
	if (turn == 'W')
		return 2;
	else if (turn == 'B')
		return 1;
}


chess init_state(char** board, char turn)
{
	chess tmp;
	tmp.set_board(board);
	tmp.set_turn(turn);
	return tmp;
}

