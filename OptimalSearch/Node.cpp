#include "Node.h"
#include <algorithm>

Node::Node(State state, Operator op, Node* parent)
{
	this->state = state;
	operatorUsedToMakeThisNode = op;
	UsedOperators = std::vector<Operator>();
	this->parent = parent;
	cost = CalculateCost();
}

bool Node::HasSolution()
{
	return state.isSolution();
}

void Node::PrintCurrentState()
{
	printf("(%d,%d,%d) \n", state.state[0], state.state[1], state.state[2]);
}

void Node::PrintSolution()
{
	std::vector<Node*> nodes = std::vector<Node*>();

	Node* temp = this->parent;
	nodes.push_back(temp);
	while (temp->parent != nullptr)
	{
		temp = temp->parent;
		nodes.push_back(temp);
	}
	std::reverse(nodes.begin(), nodes.end());
	int step = 0;
	for (auto node : nodes)
	{
		step++;
		printf("Step %d:(%d,%d,%d) Cost:%d \n", step, node->state.state[0], node->state.state[1], node->state.state[2], node->CalculateCost());
	}
	step++;
	printf("Step %d:(%d,%d,%d) \n", step, state.state[0], state.state[1], state.state[2]);
}

int Node::CalculateDepth()
{
	int depth = 0;
	if (parent == nullptr)
		return depth;
	else
	{
		Node* temp = this->parent;
		depth++;
		while (temp->parent != nullptr)
		{
			temp = temp->parent;
			depth++;
		}
		return depth;
	}
}

int Node::CalculateCost()
{
	int cost = CalculateDepth();
	if (this->parent != nullptr)
	{
		cost += this->parent->cost;
		cost += OperatorCost();
	}
	return cost;
}

int Node::OperatorCost()
{
	int max[3] = { 5, 3, 2 };
	return std::min(parent->state.state[operatorUsedToMakeThisNode.from], max[operatorUsedToMakeThisNode.to] - parent->state.state[operatorUsedToMakeThisNode.to]);
}
