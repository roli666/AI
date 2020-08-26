#include "BackTrack.h"
#include <iostream>
#include <algorithm>
#include <time.h>

BackTrack::BackTrack(int startState[3], int endState[3],int maximumDepth)
{
	State s = State();
	for (size_t i = 0; i < 3; i++)
	{
		s.state[i] = startState[i];
		this->endState.state[i] = endState[i];
	}
	currentNode = new Node(s, Operator(0, 0), nullptr);
	currentNode->ApplicableOperators = ApplicableOperators(*currentNode);
	maxDepth = maximumDepth;
	std::srand(time(nullptr));
}

void BackTrack::FindSolution()
{
	while (true)
	{
		if (currentNode == nullptr)
		{
			std::cout << "No solution" << std::endl;
			break;
		}
		if (currentNode->HasSolution())
		{
			std::cout << "Found solution:";
			currentNode->PrintCurrentState();
			currentNode->PrintSolution();
			break;
		}
		if (currentNode->depth >= maxDepth)
		{
			currentNode = currentNode->parent;
		}
		if (currentNode->ApplicableOperators.empty())
		{
			currentNode = currentNode->parent;
		}
		else
		{
			Operator* chosenOperator = &currentNode->ApplicableOperators.back();
			currentNode->UsedOperators.push_back(*chosenOperator);
			currentNode->ApplicableOperators.pop_back();
			Node* newNode = new Node(ApplyOperator(currentNode->state, *chosenOperator), *chosenOperator, currentNode);
			newNode->ApplicableOperators = ApplicableOperators(*newNode);
			currentNode = newNode;
		}
	}
}

State BackTrack::ApplyOperator(State state, Operator op)
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

std::vector<Operator> BackTrack::ApplicableOperators(State a)
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

std::vector<Operator> BackTrack::ApplicableOperators(Node n)
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

int BackTrack::Heuristic(State a)
{
	if (a.isSolution())
		return 0;
	else
		return 40000 - (a.state[0] > 0 ? 1 : 0) - (a.state[1] > 0 ? 1 : 0) - (a.state[2] > 0 ? 1 : 0);
}
