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
