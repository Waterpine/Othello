
#include"MCTS.h"


int main()
{
	
	class chess c;
	std::vector<struct position> r;
	c.print();
	r = c.findall();
	c.put(r[0]);
	std::cout << (int)r[0].row << " " << (int)r[0].col << std::endl;
	std::cout << std::endl;
	c.print();
	r.clear();
	r = c.findall();
	for (unsigned int i = 0; i < r.size(); i++)
	{
		std::cout << (int)r[i].row << " " << (int)r[i].col << " " << (int)r[i].num << std::endl;
	}
  printf("turn: %d\n", c.get_turn());
	MCTStree* Tree = new MCTStree(c,c.get_turn());
  printf("%d\n", Tree->root->get_state().get_turn());
	struct position pos;
	if(Tree->MCTSsearch(15, pos))
	{
		c.put(pos);
	}
	else
	{
		cout << "PASS" << endl;
	}

}