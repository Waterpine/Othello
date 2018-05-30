#include"chess.h"

int main()
{
	
	class chess c;
	vector<struct position> r;
	c.print();
	r = c.findall();
	c.put(r[0]);
	cout << r[0].row << " " << r[0].col << endl;
	cout << endl;
	c.print();
	r.clear();
	r = c.findall();
	for (int i = 0; i < r.size(); i++)
	{
		cout << r[i].row << " " << r[i].col << " " << r[i].num << endl;
	}
	int a;
	cin>>a;
	return 0;
}
