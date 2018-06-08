#include "MCTS.h"

MCTSnode::MCTSnode(chess state, char turn) : father(NULL), total(0), win(0), state(state)
{
	this->state.set_turn(turn);
}

MCTSnode::MCTSnode(MCTSnode *father, chess state, struct position pos) : father(father), pos(pos), total(0), win(0)
{
	this->father = father;
	this->state = state;
	this->state.put(pos);
}

int MCTSnode::selection()
{
	double UCT_value;
	double max = -99999999;
	int index = -1;
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

double MCTSnode::UCT(int total, int win_child, int total_child)
{
	int C = 1; //常数
	if (total_child == 0)
		return 1e100;
	return (win_child / total_child) +  C * sqrt(log(total) / total_child);
}

int MCTSnode::Simulation()
{
	chess tmp_state(state);
	std::vector<struct position> r;
	r = tmp_state.findall();
	struct position nextPos;
	std::vector<struct position> nextValidPos;
	char root_turn = state.get_turn();
	std::random_device rd;
    std::mt19937 gen(rd());
	int num_valid_pos;
	int flag = 0;
	while(true){
		nextValidPos = tmp_state.findall();
		if(flag == 1 && nextValidPos.size() == 0)
		{
			break;
		}
		else if(nextValidPos.size() == 0)
		{
			flag = 1;
			position empty_pos;
			tmp_state.put(empty_pos);
			continue;
		}
		else
		{
			flag = 0;
			num_valid_pos = nextValidPos.size();
        	std::uniform_int_distribution<> dis(0, num_valid_pos - 1);
			int index = dis(gen);
			nextPos = nextValidPos[index];
			tmp_state.put(nextPos);
		}
	}
	char nb_white = tmp_state.get_white();
	char nb_black = tmp_state.get_black();
	//black win
	if (nb_black > nb_white)
		return 1;
	else if (nb_black < nb_white)
		return 2;
	else
		return 0;
}

MCTStree::MCTStree(chess state, char turn):turn(turn)
{
	this->root = new MCTSnode(state, turn);
}

bool MCTStree::MCTSsearch(double t, struct position &best_pos)
{
	root->set_father(nullptr);
	timer T;
	T.start();
	int index;
	int win;
	MCTSnode* pnew_child;
	while(T.get_time() < t)
	{
		MCTSnode *tmp = root;
		while(true)
		{
			index = tmp->selection();
			if (index == -1)
			{
				//find leaf node
				break;
			}
			tmp = tmp->get_children()[index];
		}
		std::vector<struct position> pos = tmp->get_state().findall();
		//change turn
		if (pos.size() == 0)
		{
			//put an empty chessman and it will change turn
			tmp->state.put(position());
			pos = tmp->get_state().findall();
			//if no place to put, game over and propagate
			if (pos.size() == 0)
			{
				char white = tmp->state.get_black();
				char black = tmp->state.get_white();
				int win;
				if (black > white)
					win = 1;
				else if (black < white)
					win = 2;
				else
					win = 0;
				MCTSbackpropagation(tmp, root, win);
				continue;
			}
		}

		//expand
		for (unsigned int i = 0; i < pos.size(); i++)
		{
			struct position new_pos = pos[i];
			chess tmp_chess(tmp->get_state());
			tmp_chess.put(new_pos);
			pnew_child = new MCTSnode;
			pnew_child->father = tmp;
			pnew_child->pos = new_pos;
			pnew_child->total = 0;
			pnew_child->win = 0;
			pnew_child->state = tmp_chess;
			tmp->add_child(pnew_child);
		}
		win = pnew_child->Simulation();
		MCTSbackpropagation(pnew_child, root, win);
	}
	//choose which place to put chessman
	std::vector<MCTSnode*> root_children = root->get_children();
	if(root_children.size() == 0)
	{
		return false;
	}
	double best_score = -999999;
	double score;
	for(int i = 0; i < root_children.size(); i++)
	{
		score = (double)root_children[i]->get_win()/(double)root_children[i]->get_total();
		if(score > best_score)
		{
			best_score = score;
			best_pos = root_children[i]->getPosition();
		}
	}
	return true;
}

void MCTSbackpropagation(MCTSnode *node, MCTSnode *root, int win)
{
	int count = 0;
	char root_turn = root->state.get_turn();
	MCTSnode *p = node;
	while (p != nullptr)
	{
		p->set_total();
		if (root_turn == win && p->get_state().get_turn() != root_turn)
		{
			p->set_win();
		}
		else if (root_turn != win && p->get_state().get_turn() == root_turn)
		{
			p->set_win();
		}
		p = p->get_father();
	}
}
