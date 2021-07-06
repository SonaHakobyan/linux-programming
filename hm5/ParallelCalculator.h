#ifndef PARALLEL_CALCULATOR_H
#define PARALLEL_CALCULATOR_H

#define READ_END 0
#define WRITE_END 1

#include <unistd.h> 

class ParallelCalculator
{
    private:
        int arrayCapacity;
        int workersCount;

        int* array;
        pid_t* workers;

        int (*parentChildFileDes)[2];
        int (*childParentFileDes)[2];

    public:
        ParallelCalculator(int arrayCapacity, int workersCount);
        ~ParallelCalculator();
        void sum();
};

#endif


