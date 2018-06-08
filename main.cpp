
#include"MCTS.h"


int main()
{
	
	class chess c;
	MCTStree* Tree = new MCTStree(c,c.get_turn());
	Tree->root->state.print();
	struct position pos;
	char turn = c.get_turn();
	while((int)Tree->state.get_num() != 64)
	{
		if(turn == c.get_turn())
		{
			if(Tree->MCTSsearch(15, pos))
			{
				c.print();
				cout << "the turn is " << (int)c.get_turn() << endl;
				cout << (int)pos.row << ", " << (int)pos.col << endl;
				c.put(pos);
			}
			else
			{
				cout << "PASS" << endl;
			}
		}
		else
		{
			scanf("%d %d\n",&x,&y);
			struct position humanpos;
			humanpos.row = x;
			humanpos.col = y;
			c.put(humanpos);
		}
	}
}