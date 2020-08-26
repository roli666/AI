#include "BreadthFirst.h"
#include <iostream>
#include <algorithm>
#include <time.h>

BreadthFirst::BreadthFirst(int startState[3], int endState[3],int maximumDepth)
{
	State s = State();
	for (size_t i = 0; i < 3; i++)
	{
		s.state[i] = startState[i];
		this->endState.state[i] = endState[i];
	}
	openNodes = std::vector<Node*>();
	closedNodes = std::vector<Node*>();
	Node* startNode = new Node(s, Operator(0, 0), nullptr);
	startNode->ApplicableOperators = ApplicableOperators(*startNode);
	openNodes.push_back(startNode);
	maxDepth = maximumDepth;
	std::srand((unsigned int)time(nullptr));
}

void BreadthFirst::FindSolution()
{
	while (true)
	{
		if (openNodes.empty())
		{
			std::cout << "No solution" << std::endl;
			break;
		}
		Node* chosenNode = ChoseNode();
		if (chosenNode->HasSolution())
		{
			std::cout << "Found solution:";
			chosenNode->PrintCurrentState();
			chosenNode->PrintSolution();
			break;
		}
		ExtendNode(chosenNode);
	}
}

void BreadthFirst::PrintOpenNodes()
{
	for (auto n : openNodes)
	{
		for (size_t i = 0; i < n->depth; i++)
		{
			std::cout << " ";
		}
		std::cout << "+" << std::endl;
	}
}

void BreadthFirst::ExtendNode(Node* node)
{
	std::vector<Node*> newNodes = std::vector<Node*>();
	for (Operator o : node->ApplicableOperators)
	{
		Node* newNode = ApplyOperator(node,o);
		if (FindNode(&openNodes, newNode) == -1 && FindNode(&closedNodes, newNode) == -1)
		{
			openNodes.push_back(newNode);
		}
	}
	openNodes.erase(openNodes.begin() + FindNode(&openNodes, node));
	closedNodes.push_back(node);
}

int BreadthFirst::FindNode(std::vector<Node*>* nodeVector, Node* node)
{
	for (size_t i = 0; i < nodeVector->size(); i++)
	{
		if (nodeVector->at(i)->state == node->state)
		{
			return i;
		}
	}
	return -1;
}

State BreadthFirst::ApplyOperator(State state, Operator op)
{
	State retState;
	int m = std::min(state.state[op.from], max[op.to] - state.state[op.to]);
	for (size_t i = 0; i < 3; i++)
	{
		if (i == op.to)
			retState.state[i] = state.state[i] + m;
		else if (i == op.from)
			retState.state[i] = state.state[i] - m;
		else
			retState.state[i] = state.state[i];
	}
	return retState;
}

Node* BreadthFirst::ApplyOperator(Node* node, Operator op)
{
	State newState;
	int m = std::min(node->state.state[op.from], max[op.to] - node->state.state[op.to]);
	for (size_t i = 0; i < 3; i++)
	{
		if (i == op.to)
			newState.state[i] = node->state.state[i] + m;
		else if (i == op.from)
			newState.state[i] = node->state.state[i] - m;
		else
			newState.state[i] = node->state.state[i];
	}
	Node* retNode = new Node(newState, op, node);
	retNode->ApplicableOperators = ApplicableOperators(retNode->state);
	return retNode;
}

std::vector<Operator> BreadthFirst::ApplicableOperators(State a)
{
	std::vector<Operator> retVal = std::vector<Operator>();
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (i != j)
			{
				if (a.state[i] > 0 && a.state[j] < max[j])
				{
					retVal.push_back(Operator(i, j));
				}
			}
		}
	}
	return retVal;
}

std::vector<Operator> BreadthFirst::ApplicableOperators(Node n)
{
	std::vector<Operator> retVal = std::vector<Operator>();
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (i != j)
			{
				if (n.state.state[i] > 0 && n.state.state[j] < max[j])
				{
					retVal.push_back(Operator(i, j));
				}
			}
		}
	}
	return retVal;
}

Node* BreadthFirst::ChoseNode()
{
	int maxDepth = INT_MIN;
	Node* nodeReturn = nullptr;
	for (auto node : openNodes) 
	{
		if (node->depth >= maxDepth)
		{
			maxDepth = node->depth;
			nodeReturn = node;
		}
	}
	return nodeReturn;
}
