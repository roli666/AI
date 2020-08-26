#include <iostream>
#include "Sodoku.h"

int main()
{
    Sodoku* s = new Sodoku();
    s->printTable();
    s->isValid();

    s->putNumber(8, 8, 8);
    s->printTable();
    s->isValid();
}