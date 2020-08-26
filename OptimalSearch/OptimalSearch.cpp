#include "OptimalSearch.h"
#include <iostream>
#include <algorithm>
#include <time.h>

OptimalSearch::OptimalSearch(int startState[3], int endState[3])
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
	std::srand((unsigned int)time(nullptr));
}

void OptimalSearch::FindSolution()
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

void OptimalSearch::PrintOpenNodes()
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

void OptimalSearch::ExtendNode(Node* node)
{
	std::vector<Node*> newNodes = std::vector<Node*>();
	for (Operator o : node->ApplicableOperators)
	{
		Node* newNode = ApplyOperator(node,o);
		if (FindNode(&openNodes, newNode) == -1 && FindNode(&closedNodes, newNode) == -1)
		{
			openNodes.push_back(newNode);
		}
		else if(FindNode(&openNodes, newNode) != -1)
		{
			Node * oldNode = openNodes.at(FindNode(&openNodes, newNode));
			if (newNode->cost < oldNode->cost)
			{
				oldNode = newNode;
			}
		}
	}
	openNodes.erase(openNodes.begin() + FindNode(&openNodes, node));
	closedNodes.push_back(node);
}

int OptimalSearch::FindNode(std::vector<Node*>* nodeVector, Node* node)
{
	for (size_t i = 0; i < nodeVector->size(); i++)
	{
		if (nodeVector->at(i) == node)
		{
			return i;
		}
	}
	return -1;
}

State OptimalSearch::ApplyOperator(State state, Operator op)
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

Node* OptimalSearch::ApplyOperator(Node* node, Operator op)
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

std::vector<Operator> OptimalSearch::ApplicableOperators(State a)
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

std::vector<Operator> OptimalSearch::ApplicableOperators(Node n)
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

Node* OptimalSearch::ChoseNode()
{
	int minCost = INT_MAX;
	Node* nodeReturn = nullptr;
	for (auto node : openNodes) 
	{
		if (node->cost <= minCost)
		{
			minCost = node->cost;
			nodeReturn = node;
		}
	}
	return nodeReturn;
}
