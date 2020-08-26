#include "OptimalSearch.h"

int main()
{
	int startState[3] = { 5,0,0 };
	int endState[3] = { 4,1,0 };
	OptimalSearch os = OptimalSearch(startState,endState);
	os.FindSolution();
	return 0;
}