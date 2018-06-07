#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<vector>
#include<random>

using namespace std;

class MCTSnode
{
public:
	MCTSnode(chess state, char turn);
	MCTSnode(MCTSnode *father, struct position pos);
	~MCTSnode() {};
	int get_win();     //获得当前赢棋数 
	void set_win();    //设置当前赢棋数 
	int get_total();   //获得当前总盘数  
	void set_total();  //设置当前总盘数  
	chess get_state(); //获得当前状态 
	void set_state();  //设置当前状态 
	int selection(); //选择节点计算 
	int Simulation(chess state);  //模拟 
	double UCT(int total, int win_child, int total_child); //UCT计算公式 
	
private:
	int win;    //胜利的盘数 
	int total;  //总盘数 
	MCTSnode* father; //父节点 
	vector<MCTSnode*> children; //儿子节点 
	chess state; //棋盘状态 
	struct position pos; //落子位置 
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




 
