#include"MTCS.h"


MTCNode::MTCNode(chess state, char turn)
	:father(NULL), access_time(1), reward(0),state(state)
{
	this->state.set_turn(turn);
}


MTCNode::MTCNode(MTCNode *father, struct position pos)
	:father(father),pos(pos),access_time(1),reward(0)
{
	this->state = father->get_state();
	this->state.put(pos);
}


int MTCNode::choose()
{
	double UCT_value;
	double max = 0;
	int index = -1;
	for (unsigned int i = 0; i < this->children.size(); i++)
	{
		UCT_value = 1.0 * children[i]->reward / children[i]->access_time + 0.5 * sqrt(log(this->access_time) / children[i]->access_time);
		if (max < UCT_value)
		{
			index = i;
			max = UCT_value;
		}
	}
	return index;
}

bool MTCNode::search(const clock_t t, struct position &best)
{
	timer tim;
	tim.start();
	while (tim.get_time() < t)
	{
		//do search
		return false;
	}
}

void MTCNode::fill()
{
	std::vector<struct position> vec = this->state.findall();
	MTCNode* p;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		p = new MTCNode(this, vec[i]);
		this->children.push_back(p);
	}
}

MTCNode* MTCNode::access(int index)
{
	MTCNode* next = this->children[index];
	if (next->get_access_time == 1)
		next->fill();
	next->add_access_time();
	return next;
}