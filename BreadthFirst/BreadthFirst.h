#include <deque>
#include "State.h"
#include <vector>
#include "Operator.h"
#include "Node.h"
class BreadthFirst {
public:
	BreadthFirst(int startState[3], int endState[3], int maxDepth);
	void FindSolution();
	void PrintOpenNodes();
private:
	void ExtendNode(Node* node);
	int FindNode(std::vector<Node*> * nodeVector,Node* node);
	State ApplyOperator(State state, Operator op);
	Node* ApplyOperator(Node* node, Operator op);
	int maxDepth;
	Node* ChoseNode();
	int max[3] = { 5, 3, 2 };
	std::vector<Node*> openNodes;
	std::vector<Node*> closedNodes;
	std::vector<Operator> ApplicableOperators(State a);
	std::vector<Operator> ApplicableOperators(Node n);
	State endState;
};