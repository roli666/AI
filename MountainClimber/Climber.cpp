#include "Climber.h"
#include <iostream>
#include <algorithm>
#include <time.h>

Climber::Climber(int startState[3], int endState[3])
{
	for (size_t i = 0; i < 3; i++)
	{
		currentState.state[i] = startState[i];
		this->endState.state[i] = endState[i];
	}
}

void Climber::FindSolution()
{
	int maxTries = 0;
	std::srand(time(nullptr));
	while (true)
	{
		if (maxTries > 100)
		{
			std::cout << "No solution" << std::endl;
			break;
		}
		std::vector<Operator> applicableOperators = ApplicableOperators(currentState);
		if (applicableOperators.empty())
		{
			std::cout << "No solution" << std::endl;
			break;
		}
		else
		{
			Operator* chosenOperator = nullptr;
			int smallestHeuristic = INT_MAX;
			for (size_t i = 0; i < applicableOperators.size(); i++)
			{
				int heuristic = Heuristic(ApplyOperator(currentState, applicableOperators[i]));
				if (smallestHeuristic >= heuristic)
				{
					smallestHeuristic = heuristic;
					chosenOperator = &applicableOperators[i];
				}
			}
			if (chosenOperator == nullptr)
			{
				int random_variable = std::rand() % applicableOperators.size();
				chosenOperator = &applicableOperators[random_variable];
			}
			currentState = ApplyOperator(currentState, *chosenOperator);
		}
		printCurrentState();
		if (currentState.isSolution())
		{
			std::cout << "Found solution:";
			printCurrentState();
			break;
		}
		maxTries++;
	}

}

State Climber::ApplyOperator(State state, Operator op)
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

std::vector<Operator> Climber::ApplicableOperators(State a)
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

int Climber::Heuristic(State a)
{
	if (a.isSolution())
		return 0;
	else
		return 40000 - (a.state[0] > 0 ? 1 : 0) - (a.state[1] > 0 ? 1 : 0) - (a.state[2] > 0 ? 1 : 0);
}

void Climber::printCurrentState()
{
	printf("(%d,%d,%d) \n", currentState.state[0], currentState.state[1], currentState.state[2]);
}
