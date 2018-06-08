#include "MCTS.h"

MCTSnode::MCTSnode()
{

}


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
	return (win_child / total_child) +  sqrt(C * log(total) / total_child);
}

int MCTSnode::Simulation()
{
	chess tmp_state(state);
	//cout << "init state" << endl;
  	//tmp_state.print();
	//cout << "init turn: " << (int)this->state.get_turn() << endl;
	std::vector<struct position> r;
	r = tmp_state.findall();
	
	/*
	cout << "all posible pos" << endl;
	for (unsigned int i = 0; i < r.size(); i++)
	{
		std::cout << (int)r[i].row << " " << (int)r[i].col << " " << (int)r[i].num << std::endl;
	}
	*/
	struct position nextPos;
	vector<struct position> nextValidPos;
	char root_turn = state.get_turn();
	random_device rd;
    mt19937 gen(rd());
	int num_valid_pos;
	int flag = 0;
	int count = 0;
	while(true){
    	//printf("count: %d\n", count++);
		nextValidPos = tmp_state.findall();
		if(flag == 1 && nextValidPos.size() == 0)
		{
			break;
		}
		else if(nextValidPos.size() == 0)
		{
			flag = 1;
			//printf("No valid step.\n");
			position empty_pos;
			tmp_state.put(empty_pos);
			continue;
		}
		else
		{
			flag = 0;
			num_valid_pos = nextValidPos.size();
			/*
      		printf("num_valid_pos: %d\n", num_valid_pos);
      		for(int i = 0; i< num_valid_pos; i++){
        		printf("the ith: %d, row: %d, col: %d\n", i, nextValidPos[i].row, nextValidPos[i].col);
      		}
			*/
			
        	uniform_int_distribution<> dis(0, num_valid_pos - 1);
			int index = dis(gen);
      		//printf("choose index: %d\n", index);
			nextPos = nextValidPos[index];
			tmp_state.put(nextPos);
      		//tmp_state.print();
		}
	}
	//cout << "end of simulation" << endl;
	char nb_white = tmp_state.get_white();
	char nb_black = tmp_state.get_black();
 	

	if(root_turn == 1)
	{
		//black
		if(nb_black > nb_white) return 1;
		else if(nb_black == nb_white) return 0;
		else return -1;
	}
	else
	{
		//white
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
	root->set_father(nullptr);
	timer T;
	T.start();
	int index;
	int count = 0;
	int win;
	MCTSnode* pnew_child;
	while(T.get_time() < t)
	{
		count++;
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
		vector<struct position> pos = tmp->get_state().findall();
		//change turn
		if (pos.size() == 0)
		{
			//put an empty chessman and it will change turn
			tmp->state.put(position());
			pos = tmp->get_state().findall();
			//if no place to put, game over and propagate
			if (pos.size() == 0)
			{
				cout << "game over" << endl;
				char white = tmp->state.get_black();
				char black = tmp->state.get_white();
				int win;
				if (root->state.get_turn() == 1)
				{
					if (black > white)
						win = 1;
					else if (black == white)
						win = 0;
					else
						win = -1;
				}
				else
				{
					if (white > black)
						win = 1;
					else if (black == white)
						win = 0;
					else
						win = -1;
				}
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
			pnew_child->children.clear();
			tmp->add_child(pnew_child);
		}
		win = pnew_child->Simulation();
		MCTSbackpropagation(pnew_child, root, win);
	}
	//choose which place to put chessman
	vector<MCTSnode*> root_children = root->get_children();
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
	MCTSnode *p = node;
	int factor = 0;
	char turn = node->get_state().get_turn();
	while(p != nullptr)
	{
		p->set_total();
		if(turn == p->get_state().get_turn() && win==1)
		{
			p->set_win();
		}
		p = p->get_father();
	}
}