#pragma once
class State {
public:
	int state[3] = { 0,0,0 };
	bool isSolution();
	bool operator==(const State& b);
};