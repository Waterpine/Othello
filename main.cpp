#include"MCTS.h"
//a function for destroy node
void destroy_node(MCTSnode *root)
{
	for (unsigned int i = 0; i < root->children.size(); i++)
	{
		destroy_node(root->children[i]);
	}
	delete root;
}

//destroy the tree
void destroy_tree(MCTStree *T)
{
	destroy_node(T->root);
	delete T;
}

//change the root of the T according to the received data from the network
MCTStree* cmp_access(MCTStree *T, chess &src)
{
	//if the state is the same, do nothing
	if (T->root->get_state().equal(src))
		return T;
	std::vector<MCTSnode*> vec = T->root->get_children();
	//if no children, delete the tree and create a new
	if (vec.size() == 0)
	{
		destroy_tree(T);
		return new MCTStree(src, src.get_turn());
	}
	int index = -1;
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i]->get_state().equal(src))
		{
			index = i;
			break;
		}
	}
	//cannot find the state, delete the tree and create a new
	if (index == -1)
	{
		/*for (int i = 0; i < vec.size(); i++)
		{
			destroy_node(vec[i]);
		}
		delete T->root;*/
		destroy_tree(T);
		return new MCTStree(src, src.get_turn());
	}
	//find the state, delete other node and access
	for (int i = 0; i < vec.size(); i++)
	{
		if(i != index)
			destroy_node(vec[i]);
	}
	delete T->root;
	T->root = vec[index];
	T->root->father = nullptr;
	return T;
}

int main()
{
	class chess c;
	MCTStree* Tree = new MCTStree(c, c.get_turn());
	std::cout << "game start!\n";
	struct position pos;
	char turn = c.get_turn();
	while (!c.is_gameover())
	{
		if (turn == c.get_turn())
		{
			Tree = cmp_access(Tree, c);
			std::cout << "this is ai turn: " << (int)c.get_turn() << std::endl;
			c.print();
			if (Tree->MCTSsearch(10, pos))
			{
				std::cout <<"ai pos: "<< (int)pos.row << ", " << (int)pos.col << std::endl;
				c.put(pos);
			}
			else
			{
				std::cout << "PASS" << std::endl;
				c.put(position());
			}
			std::cout << "AI done.\n\n";
			Tree = cmp_access(Tree, c);
			//destroy_tree(Tree);
		}
		else
		{
			printf("this is human turn:\n");
			c.print();
			std::vector<struct position> posvec = c.findall();
			if (posvec.size() == 0)
			{
				c.put(position());
				continue;
			}
			//random
			/*
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, posvec.size() - 1);
			int index = dis(gen);
			struct position humanpos = posvec[index];
			*/
			//local maximum
			struct position humanpos = c.find_max(posvec);
			printf("human pos: %d, %d\n", (int)humanpos.row, (int)humanpos.col);
			c.put(humanpos);
			printf("human done!\n\n");
		}
		Tree = new MCTStree(c, c.get_turn());
	}
	std::cout << "black is " << (int)c.get_black() << ". white is " << (int)c.get_white() << std::endl;
}
