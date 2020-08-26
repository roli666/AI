#include "BreadthFirst.h"

int main()
{
	int startState[3] = { 5,0,0 };
	int endState[3] = { 4,1,0 };
	BreadthFirst bf = BreadthFirst(startState,endState,2);
	bf.FindSolution();
	return 0;
}