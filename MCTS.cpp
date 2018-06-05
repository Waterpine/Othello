#include "MCTS.h"

MCTSnode::MCTSnode(chess state, char turn) : father(NULL), total(1), win(0), state()
{
	this->state.set_turn(turn);
}

MCTSnode::MCTSnode(MCTSnode *father, struct position pos) : father(father), pos(pos), total(1), win(0)
{
	this->father = father;
	this->state.put(pos);
}

int MCTSnode::selection()
{
	double UCT_value;
	double max;
	for (unsigned int i = 0; i < this->children.size(); i++)
	{
		UCT_value = UCT(this->total, this->children[i]->win, this->children[i]->total);
		if (max < UCT_value)
		{
			index = i;
			max = UCT_value;
		}
	}
	return index;
}

double MCTSnode::UCT(int total, int win_child, int total_child);
{
	int C = 1; //³£Êý 
	return (win_child / total_child) +  sqrt(C * log(total) / total_child);
}

void MCTSnode::Simulation(chess state, char turn);
{
	
}

