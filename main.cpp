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

int main()
{

	class chess c;
	MCTStree* Tree = new MCTStree(c, c.get_turn());
	cout << "game start!\n";
	struct position pos;
	char turn = c.get_turn();
	while (!c.is_gameover())
	{
		if (turn == c.get_turn())
		{
			cout << "this is ai turn: " << (int)c.get_turn() << endl;
			c.print();
			if (Tree->MCTSsearch(10, pos))
			{
				cout <<"ai pos: "<< (int)pos.row << ", " << (int)pos.col << endl;
				c.put(pos);
			}
			else
			{
				cout << "PASS" << endl;
				c.put(position());
			}
			cout << "AI done.\n\n";
			destroy_tree(Tree);
		}
		else
		{
			printf("this is human turn:\n");
			c.print();
			vector<struct position> posvec = c.findall();
			if (posvec.size() == 0)
			{
				c.put(position());
				continue;
			}
			//random
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<> dis(0, posvec.size() - 1);
			int index = dis(gen);
			struct position humanpos = posvec[index];
			//local maximum
			//struct position humanpos = c.find_max(posvec);
			printf("human pos: %d, %d\n", (int)humanpos.row, (int)humanpos.col);
			c.put(humanpos);
			printf("human done!\n\n");
		}
		Tree = new MCTStree(c, c.get_turn());
	}
	cout << "black is " << (int)c.get_black() << ". white is " << (int)c.get_white() << endl;
}