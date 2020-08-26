#include <deque>
#include "State.h"
#include <vector>
#include "Operator.h"
class Climber {
public:
	Climber(int startState[3], int endState[3]);
	void FindSolution();
	State ApplyOperator(State state,Operator op);
	std::vector<Operator> ApplicableOperators(State a);
	int Heuristic(State a);
private:
	int max[3] = { 5, 3, 2 };
	State currentState;
	State endState;
	void printCurrentState();
};