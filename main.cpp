
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
}