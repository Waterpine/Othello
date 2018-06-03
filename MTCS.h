#pragma once
#include"chess.h"
#include"timer.h"
#include<cmath>
#include<limits>


class MTCNode
{
public:
	//init a node which is not root
	MTCNode(MTCNode *father, struct position pos);
	//init the root
	MTCNode(chess state, char turn);
	//destructor
	~MTCNode() {};
	//get access time
	int get_access_time();
	//get reward
	int get_reward();
	//add access_time
	void add_access_time();
	//add reward
	void add_reward();
	//get state
	chess get_state();
	//fill the children
	void fill();
	//search an optimal position to put down chessman
	bool search(const clock_t t, struct position &best);
	//choose which node to expand, the rule is UCT
	int choose();
	//access ith children
	MTCNode* access(int index);
private:
	MTCNode *father;
	std::vector<MTCNode*> children;
	chess state;
	struct position pos;
	int access_time;
	int reward;
};

inline void MTCNode::add_access_time()
{
	access_time++;
}

inline void MTCNode::add_reward()
{
	reward++;
}
inline int MTCNode::get_access_time()
{
	return access_time;
}

inline int MTCNode::get_reward()
{
	return reward;
}

inline chess MTCNode::get_state()
{
	return state;
}