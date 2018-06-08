#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<vector>
#include<random>
#include "chess.h"
#include "timer.h"

using namespace std;

class MCTSnode
{
public:
	MCTSnode() {};
	MCTSnode(chess state, char turn);
	MCTSnode(MCTSnode *father, chess state, struct position pos);
	~MCTSnode() {};
	int get_win();     //获得当前赢棋�?
	void set_win();    //设置当前赢棋�?
	int get_total();   //获得当前总盘�? 
	void set_total();  //设置当前总盘�? 
	chess get_state(); //获得当前状�?
	void set_state();  //设置当前状�?
	int selection();   //选择节点计算 
	int Simulation();  //模拟 
	double UCT(int total, int win_child, int total_child); //UCT计算公式 
	vector<MCTSnode*> get_children(){ return children;}
	struct position getPosition(){return pos;}
	void add_child(MCTSnode* new_child){children.push_back(new_child);}
	MCTSnode* get_father(){return father;}
	void set_turn(char turn){this->state.set_turn(turn);}
	 void set_father(MCTSnode* father){this->father = father;}
	
//private:
	int win;     	  			//胜利的盘�?
	int total;  	  			//总盘�?
	MCTSnode* father; 			//父节�?
	vector<MCTSnode*> children; //儿子节点 
	chess state; 				//棋盘状�?
	struct position pos; 		//落子位置 
};

class MCTStree
{
public:
	MCTStree(chess state, char turn);
	~MCTStree() { };
    bool MCTSsearch(double t, struct position &pos);
    char get_turn(){return turn;}
    
//private:
	MCTSnode* root;
	struct position last_position;
	char turn;
};

void MCTSbackpropagation(MCTSnode *node, MCTSnode * root, int win);


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




 
