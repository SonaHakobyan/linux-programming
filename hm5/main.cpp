#include "ParallelCalculator.h"
#include <iostream>

int main()
{
    ParallelCalculator* calculator = new ParallelCalculator(100, 10);

    calculator->sum();

    return 0;
}
