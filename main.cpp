
#include"MCTS.h"


int main()
{
	
	class chess c;
	MCTStree* Tree = new MCTStree(c,c.get_turn());
	Tree->root->state.print();
	struct position pos;
	char turn = c.get_turn();
  int x, y;
	while((int)c.get_num() != 64)
	{
		if(turn == c.get_turn())
		{
			if(Tree->MCTSsearch(10, pos))
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
      printf("this is human turn:\n");
      c.print();
      vector<struct position> posvec = c.findall();
      int size = posvec.size();
      printf("%d\n",size);
      scanf("%d",&x);
      struct position humanpos = posvec[x-1];
      printf("%d %d\n",(int)humanpos.row, (int)humanpos.col);
      getchar();
      getchar();
      getchar();
			c.put(humanpos);
      c.print();
      getchar();
      getchar();
      getchar();
      printf("human done!");
		}
    Tree = new MCTStree(c,c.get_turn());
	}
}