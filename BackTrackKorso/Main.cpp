#include "BackTrack.h"

int main()
{
	int startState[3] = { 5,0,0 };
	int endState[3] = { 4,1,0 };
	BackTrack bt = BackTrack(startState,endState,2);
	bt.FindSolution();
	return 0;
}