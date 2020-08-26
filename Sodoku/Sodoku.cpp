#include "Sodoku.h"
#include <iostream>

Sodoku::Sodoku()
{
}

Sodoku::Sodoku(int table[9][9])
{
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			sodokuTable[i][j] = table[i][j];
		}
	}
}

void Sodoku::printTable()
{
	std::cout << std::endl;
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			std::cout << sodokuTable[i][j];
		}
		std::cout << std::endl;
	}
}

bool Sodoku::isValid()
{
	bool valid = true;
	for (size_t i = 0; i < 9; i++)
	{
		int number = sodokuTable[i][i];
		if (number == 0)
			continue;
		for (size_t k = i+1; k <= 9; k++)
		{
			if (number == sodokuTable[i][k])
			{
				valid = false;
			}
		}
		for (size_t l = i+1; l <= 9; l++)
		{
			if (number == sodokuTable[l][i])
			{
				valid = false;
			}
		}
		if (!valid)
		{
			std::cout << "Not valid on i=" << i;
			break;
		}
	}
	return valid;
}

void Sodoku::putNumber(int row, int col, int number)
{
	sodokuTable[row][col] = number;
}
