#include <deque>
#include "State.h"
#include <vector>
#include "Operator.h"
#include "Node.h"
class BackTrack {
public:
	BackTrack(int startState[3], int endState[3],int maxDepth);
	void FindSolution();
	State ApplyOperator(State state,Operator op);
	std::vector<Operator> ApplicableOperators(State a);
	std::vector<Operator> ApplicableOperators(Node n);
	int Heuristic(State a);
	int maxDepth;
private:
	int max[3] = { 5, 3, 2 };
	Node * currentNode;
	State endState;
};