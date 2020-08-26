#include "State.h"

bool State::isSolution()
{
	for (size_t i = 0; i < 3; i++)
	{
		if (state[i] == 4)
			return true;
	}
	return false;
}

bool State::operator==(const State& b)
{
	return b.state[0] == state[0] && b.state[1] == state[1] && b.state[2] == state[2];
}


