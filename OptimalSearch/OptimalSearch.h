#include <deque>
#include "State.h"
#include <vector>
#include "Operator.h"
#include "Node.h"
class OptimalSearch {
public:
	OptimalSearch(int startState[3], int endState[3]);
	void FindSolution();
	void PrintOpenNodes();
private:
	int max[3] = { 5, 3, 2 };
	std::vector<Node*> openNodes;
	std::vector<Node*> closedNodes;
	State endState;
	void ExtendNode(Node* node);
	int FindNode(std::vector<Node*> * nodeVector,Node* node);
	State ApplyOperator(State state, Operator op);
	Node* ApplyOperator(Node* node, Operator op);
	Node* ChoseNode();
	std::vector<Operator> ApplicableOperators(State a);
	std::vector<Operator> ApplicableOperators(Node n);
};