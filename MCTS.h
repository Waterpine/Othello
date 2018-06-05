#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<vector>

using namespace std;

class MCTSnode
{
public:
	MCTSnode(chess state, char turn);
	MCTSnode(MCTSnode *father, struct position pos);
	~MCTSnode() {};
	int get_win();     //��õ�ǰӮ���� 
	void set_win();    //���õ�ǰӮ���� 
	int get_total();   //��õ�ǰ������  
	void set_total();  //���õ�ǰ������  
	chess get_state(); //��õ�ǰ״̬ 
	void set_state();  //���õ�ǰ״̬ 
	int selection(); //ѡ��ڵ���� 
	void Simulation(chess state, char turn); //ģ�� 
	double UCT(int total, int win_child, int total_child); //UCT���㹫ʽ 
	
private:
	int win;    //ʤ�������� 
	int total;  //������ 
	MCTSnode* father; //���ڵ� 
	vector<MCTSnode*> children; //���ӽڵ� 
	chess state; //����״̬ 
	struct position pos; //����λ�� 
}

inline int MCTSnode::get_total()
{
	return total;
}

inline int MCTSnode::get_win()
{
	return win;
}

inline chess MCTSnode::get_state()
{
	return state;
}

inline void MCTSnode::set_win()
{
	win = win + 1;
}

inline void MCTSnode::set_total()
{
	total = total + 1; 
}

inline void MCTSnode::set_state()
{
	
}




 
