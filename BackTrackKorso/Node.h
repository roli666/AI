#pragma once
#include "State.h"
#include <vector>
#include "Operator.h"
class Node {
public:
	Node(State state, Operator op,Node * parent);
	bool HasSolution();
	void PrintCurrentState();
	void PrintSolution();
	int depth;
	Node* parent;
	std::vector<Operator> ApplicableOperators;
	std::vector<Operator> UsedOperators;
	State state;
private:
	Operator operatorUsedToMakeThisNode = Operator(0,0);
	int CalculateDepth();
};