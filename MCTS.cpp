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
 printf("33\n");
 printf("this->children.size(): %d\n", this->children.size());
	for (unsigned int i = 0; i < this->children.size(); i++)
	{
 printf("i: %d\n", i);
 printf("%d, %d, %d\n", this->total, this->children[i]->win, this->children[i]->total);
		UCT_value = UCT(this->total, this->children[i]->win, this->children[i]->total);
 printf("UCT_value: %f\n", UCT_value);
		if (max < UCT_value)
		{
			index = i;
			max = UCT_value;
		}
	}
 printf("44\n");
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
  	tmp_state.print();
	std::vector<struct position> r;
	r = tmp_state.findall();
	for (unsigned int i = 0; i < r.size(); i++)
	{
		std::cout << (int)r[i].row << " " << (int)r[i].col << " " << (int)r[i].num << std::endl;
	}
	struct position nextPos;
	vector<struct position> nextValidPos;
	char root_turn = state.get_turn();
	random_device rd;
    mt19937 gen(rd());
	int num_valid_pos;
	int flag = 0;
	int count = 0;
	while(true){
    	printf("count: %d\n", count++);
		nextValidPos = tmp_state.findall();
    	printf("turn: %d\n", tmp_state.get_turn());
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
      		printf("num_valid_pos: %d\n", num_valid_pos);
      		for(int i = 0; i< num_valid_pos; i++){
        		printf("%d: %d, %d\n", i, nextValidPos[i].row, nextValidPos[i].col);
      		}
        	uniform_int_distribution<> dis(0, num_valid_pos - 1);
			int index = dis(gen);
      		printf("index: %d\n", index);
			nextPos = nextValidPos[index];
			tmp_state.put(nextPos);
      		tmp_state.print();
		}
	}
 	printf("11\n");
	char nb_white = tmp_state.get_white();
	char nb_black = tmp_state.get_black();
 	printf("22\n");

	if(root_turn == 1){//black
		if(nb_black > nb_white) printf("1\n");
		else if(nb_black == nb_white) printf("0\n");
		else printf("-1\n");
	}
	else{//white
		if(nb_black < nb_white) printf("1\n");
		else if(nb_black == nb_white) printf("0\n");
		else printf("-1\n");
	}


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
  	root->set_father(nullptr);
	timer T;
  	T.start();
	int index;
  	int count = 0;
  	int win;
	MCTSnode* pnew_child;
	while(T.get_time() < t)
	{
    	printf("get_time: %d\n", T.get_time());
    	count++;
    	printf("%d\n", count);
		MCTSnode *tmp = root;
		while(true){
      		printf("1%d\n", count);
			index = tmp->selection();
     		printf("2%d\n", count);
      		printf("index: %d\n", index);
			if(index == -1){  // find leaf node
				break;
			}
			tmp = tmp->get_children()[index];
		}
		vector<struct position> pos = tmp->get_state().findall();
		random_device rd;
    	mt19937 gen(rd());
		int num_pos = pos.size();
   		printf("num_pos: %d\n", num_pos);
        uniform_int_distribution<> dis(0, num_pos - 1);
		int new_index = dis(gen);
   		printf("new_index: %d\n", new_index);
		struct position new_pos = pos[new_index];
		chess tmp_chess(tmp->get_state());
    	printf("begin\n");
    	tmp_chess.print();
    	printf("\n");
		tmp_chess.put(new_pos);
		pnew_child = new MCTSnode;
		//pnew_child = (MCTSnode*)malloc(sizeof(MCTSnode*));	
		pnew_child->father = tmp;
		pnew_child->pos = new_pos;
		pnew_child->total = 0;
		pnew_child->win = 0;
		pnew_child->state = tmp_chess;
		pnew_child->children.clear();

    	pnew_child->get_state().print();
    	printf("\n");

    	pnew_child->get_father()->get_state().print();
    	printf("\n");

		if(pnew_child->get_father() == tmp){
			printf("yes\n");
		}
		else{
			printf("no\n");
		}

		printf("%d\n", tmp->get_children().size());

    	pnew_child->get_state().print();
    	printf("\n");

    	pnew_child->get_father()->get_state().print();
    	printf("\n");

		printf("%d\n", tmp->get_children().size());

		tmp->add_child(pnew_child);
    	pnew_child->get_state().print();
    	printf("\n");
		win = pnew_child->Simulation();
   		printf("win: %d\n",win);
		MCTSbackpropagation(pnew_child, root, win);
	}
  	printf("count: %d\n", count);
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

void MCTSbackpropagation(MCTSnode *node, MCTSnode * root, int win)
{
  	int count = 0;
	MCTSnode *p = node;
	int factor = 0;
	char turn = node->get_state().get_turn();
 	printf("0\n");
	if(p == root)
	printf("p is root");

	if(p->get_father() == root)
	printf("p father is root");
 	printf("0\n");
	while(p != nullptr)
	{
 		printf("%d\n", count++);
		p->set_total();
		if(turn == p->get_state().get_turn() && win==1)
		{
			p->set_win();
		}
		p = p->get_father();
	}
}