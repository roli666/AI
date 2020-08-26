#include "Climber.h"

int main()
{
	int startState[3] = { 5,0,0 };
	int endState[3] = { 4,1,0 };
	Climber c = Climber(startState,endState);
	c.FindSolution();
	return 0;
}