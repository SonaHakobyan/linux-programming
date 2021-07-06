#include "ParallelCalculator.h"
#include <iostream>

int main()
{
    ParallelCalculator* calculator = new ParallelCalculator(10, 2);

    calculator->sum();

    return 0;
}
