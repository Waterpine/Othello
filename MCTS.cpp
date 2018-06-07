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
	return (win_child / total_child) +  sqrt(C * log(total) / total_child);
}

int MCTSnode::Simulation()
{
	chess tmp_state(state);
	char root_turn = state.get_turn();
	random_device rd;
    mt19937 gen(rd());
	int num_valid_pos;
	int flag = 0;
	while(true){
		vector<struct position> nextValidPos = state.findall();
		if(flag == 1 && nextValidPos.size() == 0){
			break;
		}
		else if(nextValidPos.size() == 0){
			flag = 1;
			printf("No valid step.\n");
			position empty_pos;
			tmp_state.put(empty_pos);
			continue;
		}
		else{
			flag = 0;
			num_valid_pos = nextValidPos.size();
        	uniform_int_distribution<> dis(0, num_valid_pos - 1);
			int index = dis(gen);
			struct position nextPos = nextValidPos[index];
			tmp_state.put(nextPos);
		}
	}
	char nb_white = state.get_white();
	char nb_black = state.get_black();
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

bool MCTStree::MCTSsearch(double t, struct position &best_pos)
{
	timer T;
	int index;
	while(T.get_time() < t)
	{
		MCTSnode *tmp = root;
		while(true){
			index = tmp->selection();
			if(index == -1){  // find leaf node
				break;
			}
			tmp = tmp->get_children()[index];
		}
		vector<struct position> pos = tmp->get_state().findall();
		random_device rd;
    	mt19937 gen(rd());
		int num_pos = pos.size();
        uniform_int_distribution<> dis(0, num_pos - 1);
		int new_index = dis(gen);
		struct position new_pos = pos[new_index];
		chess tmp_chess(tmp->get_state());
		tmp_chess.put(new_pos);
		MCTSnode new_child(tmp, tmp_chess, new_pos, tmp_chess.get_turn());
    MCTSnode* pnew_child = &new_child;
		tmp->add_child(pnew_child);
		int win = new_child.Simulation();
		MCTSbackpropagation(pnew_child, win);
	}
 
  vector<MCTSnode*> root_children = root->get_children();
	if(root_children.size() == 0){
		return false;
	}
	double best_score = -999999;
	double score;
	for(int i = 0; i < root_children.size(); i++){
		score = (double)root_children[i]->get_win()/(double)root_children[i]->get_total();
		if(score > best_score){
			best_score = score;
			best_pos = root_children[i]->getPosition();
		}
	}
	return true;
}

void MCTSbackpropagation(MCTSnode *node, int win)
{
	MCTSnode *p = node;
	int factor = 0;
	char turn = node->get_state().get_turn();
	while(p)
	{
		p->set_total();
		if(turn == p->get_state().get_turn() && win==1)
		{
			p->set_win();
		}
		p = p->get_father();
	}
}