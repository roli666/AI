#include "Node.h"

Node::Node(State state, Operator op, Node* parent)
{
	this->state = state;
	operatorUsedToMakeThisNode = op;
	UsedOperators = std::vector<Operator>();
	this->parent = parent;
	depth = CalculateDepth();
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
		printf("Step %d:(%d,%d,%d) \n", step, node->state.state[0], node->state.state[1], node->state.state[2]);
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
		while (temp->parent != nullptr)
		{
			temp = temp->parent;
			depth++;
		}
		return depth;
	}
}
