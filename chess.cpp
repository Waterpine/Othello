#include"chess.h"


void chess::print()
{
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			std::cout << (int)board[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


struct position chess::check(int row, int col)
{
	struct position r;
	if (board[row][col] != 0)
		return r;
	char enemy = 3 - turn;
	r.row = row;
	r.col = col;
	char cnt = 0;
	// check left
	if (board[row][col - 1] == enemy)
	{
		for (int i = col - 1; i >= 1; i--)
		{
			if (board[row][i] == 0)
				break;
			else if (board[row][i] == turn)
			{
				r.left = cnt;
				r.num += cnt;
				break;
			}
			cnt++;
		}
	}
	//check right
	if (board[row][col + 1] == enemy)
	{
		cnt = 0;
		for (int i = col + 1; i <= 8; i++)
		{
			if (board[row][i] == 0)
				break;
			else if (board[row][i] == turn)
			{
				r.right = cnt;
				r.num += cnt;
				break;
			}
			cnt++;
		}
	}
	//check up
	if (board[row - 1][col] == enemy)
	{
		cnt = 0;
		for (int i = row - 1; i >= 1; i--)
		{
			if (board[i][col] == 0)
				break;
			else if (board[i][col] == turn)
			{
				r.up = cnt;
				r.num += cnt;
				break;
			}
			cnt++;
		}
	}
	//check down
	if(board[row + 1][col] == enemy)
	{
		cnt = 0;
		for (int i = row + 1; i <= 8; i++)
		{
			if (board[i][col] == 0)
				break;
			else if (board[i][col] == turn)
			{
				r.down = cnt;
				r.num += cnt;
				break;
			}
			cnt++;
		}
	}
	//check left up
	if (board[row - 1][col - 1] == enemy)
	{
		cnt = 0;
		for (int i = row - 1, j = col - 1; i >= 1 && j >= 1; i--, j--)
		{
			if (board[i][j] == 0)
				break;
			else if (board[i][j] == turn)
			{
				r.leftup = cnt;
				r.num += cnt;
				break;
			}
			cnt++;
		}
	}
	//check left down
	if (board[row + 1][col - 1] == enemy)
	{
		cnt = 0;
		for (int i = row + 1, j = col - 1; i <= 8 && j >= 1; i++, j--)
		{
			if (board[i][j] == 0)
				break;
			else if (board[i][j] == turn)
			{
				r.leftdown = cnt;
				r.num += cnt;
				break;
			}
			cnt++;
		}
	}
	//check right up
	if (board[row - 1][col + 1] == enemy)
	{
		cnt = 0;
		for (int i = row - 1, j = col + 1; i >= 1 && j <= 8; i--, j++)
		{
			if (board[i][j] == 0)
				break;
			else if (board[i][j] == turn)
			{
				r.rightup = cnt;
				r.num += cnt;
				break;
			}
			cnt++;
		}
	}
	//check right down
	if (board[row + 1][col + 1] == enemy)
	{
		cnt = 0;
		for (int i = row + 1, j = col + 1; i <= 8 && j <= 8; i++, j++)
		{
			if (board[i][j] == 0)
				break;
			else if (board[i][j] == turn)
			{
				r.rightdown = cnt;
				r.num += cnt;
				break;
			}
			cnt++;
		}
	}
	return r;
}


std::vector<struct position> chess::findall()
{
	std::vector<struct position> vec;
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			struct position pos = check(i, j);
			if (pos.num != 0)
			{
				vec.push_back(pos);
			}
		}
	}
	return vec;
}


void chess::put(struct position &pos)
{
	//if no change, change the turn
	if (pos.num == 0)
	{
		turn = 3 - turn;
		return;
	}
	//left
	for (int i = pos.col - 1; i >= pos.col - pos.left; i--)
	{
		board[pos.row][i] = turn;
	}
	//right
	for (int i = pos.col + 1; i <= pos.col + pos.right; i++)
	{
		board[pos.row][i] = turn;
	}
	//up
	for (int i = pos.row - 1; i >= pos.row - pos.up; i--)
	{
		board[i][pos.col] = turn;
	}
	//down
	for (int i = pos.row + 1; i <= pos.row + pos.down; i++)
	{
		board[i][pos.col] = turn;
	}
	//leftup
	for (int i = pos.col - 1, j = pos.row - 1; i >= pos.col - pos.leftup; i--, j--)
	{
		board[j][i] = turn;
	}
	//leftdown
	for (int i = pos.col - 1, j = pos.row + 1; i >= pos.col - pos.leftdown; i--, j++)
	{
		board[j][i] = turn;
	}
	//rightup
	for (int i = pos.col + 1, j = pos.row - 1; i <= pos.col + pos.rightup; i++, j--)
	{
		board[j][i] = turn;
	}
	//rightdown
	for (int i = pos.col + 1, j = pos.row + 1; i <= pos.col + pos.rightdown; i++, j++)
	{
		board[j][i] = turn;
	}
	//put the chess
	board[pos.row][pos.col] = turn;
	//change the black number and white number
	if (turn == 1)
	{
		white -= pos.num;
		black += pos.num + 1;
	}
	else
	{
		black -= pos.num;
		white += pos.num + 1;
	}
	turn = 3 - turn;
	num++;
}


struct position chess::find_max(std::vector<struct position> pos)
{
	if (pos.size() == 0)
		return position();
	char num = pos[0].num;
	for (unsigned int i = 1; i < pos.size(); i++)
	{
		if (pos[i].num > num)
			num = i;
	}
	return pos[num];
}
