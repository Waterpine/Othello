#include "MCTS.h"

MCTSnode::MCTSnode(chess state, char turn) : father(NULL), total(0), win(0), state(state)
{
	this->state.set_turn(turn);
}

MCTSnode::MCTSnode(MCTSnode *father, chess state, struct position pos, char turn) : father(father), pos(pos), total(0), win(0)
{
	this->father = father;
	this->state = state;
	this->state.put(pos);
	this->state.set_turn(turn);
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
	int C = 1; //常数
	return (win_child / total_child) +  sqrt(C * log(total) / total_child);
}

int MCTSnode::Simulation(chess state);
{
	chess tmp_state(state);
	char root_turn = turn;
	random_device rd;
    mt19937 gen(rd());
	
	flag = 0;
	while(true){
		std::vector<MCTSnode> nextValidStep = state.findall();
		if(flag == 1 && nextValidStep.size() == 0){
			break;
		}
		else if(nextValidStep.size() == 0){
			flag = 1;
			print("No valid step.\n");
			position empty_pos;
			tmp_state.put(empty_pos);
			continue;
		}
		else{
			flag = 0;
			num_valid_pos = nextValidStep.size();
        	uniform_int_distribution<> dis(0, num_valid_pos - 1);
			int index = dis(gen);
			MCTSnode nextStep = nextValidStep[index];
			tmp_state.put(nextStep.pos);
		}
	}
	char nb_white = state.white();
	char nb_black = state.black();
	if(root_turn == 1){//black
		if(nb_black > nb_white) return 1;
		else if(nb_black == nb_white) return 0;
		else return -1;
	}
	else{//white
		if(nb_black < nb_white) return 1;
		else if(nb_black == nb_white) return 0;
		else return -1;
	}
}

MCTStree::MCTStree(chess state, char turn)
{
	this->root = new MCTSnode(state, turn);
	this->turn = turn;
}

bool MCTStree::MCTSsearch(double t, struct position pos)
{
	timer T;
	while(T.get_time() < t) //仍然在允许时间内
	{

	}
}

void MCTSbackpropagation(MCTSnode *node, int win)
{
	MCTSnode *p = node;
	int factor = 0;
	char turn = node->state.turn;
	while(p)
	{
		p->set_total();
		if(turn == p->state.turn)
		{
			p->set_win();
		}
		p = p->father;
	}
}