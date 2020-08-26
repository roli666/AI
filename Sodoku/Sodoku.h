#pragma once
class Sodoku {
public:
	Sodoku();
	Sodoku(int table[9][9]);
	void printTable();
	bool isValid();
	void putNumber(int row,int col,int number);
private:
	int sodokuTable[9][9] = {
		{0,0,1,0,3,0,0,0,0},
		{3,4,0,0,0,0,0,7,8},
		{0,8,0,0,0,6,1,2,3},
		{0,2,0,5,4,8,0,0,9},
		{0,0,6,0,9,0,0,0,0},
		{0,9,0,2,6,3,0,0,5},
		{0,0,0,0,0,0,8,0,0},
		{6,0,0,9,0,0,0,0,7},
		{0,0,4,0,0,0,2,0,0}
	};
};