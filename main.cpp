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
			}
			cout << "AI done.\n";
			destroy_tree(Tree);
		}
		else
		{
			printf("this is human turn:\n");
			c.print();
			vector<struct position> posvec = c.findall();
			struct position humanpos = c.find_max(posvec);
			printf("human pos: %d, %d\n", (int)humanpos.row, (int)humanpos.col);
			c.put(humanpos);
			c.print();
			printf("human done!\n");
		}
		Tree = new MCTStree(c, c.get_turn());
	}
}