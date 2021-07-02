#include "ParallelCalculator.h"
#include <sys/wait.h>
#include <iostream> 
#include <unistd.h> 
#include <stdlib.h>
#include <cerrno>

ParallelCalculator::ParallelCalculator(int arrayCapacity, int workersCount) 
    : arrayCapacity(arrayCapacity), 
        workersCount(workersCount)
{
    this->array = new int[this->arrayCapacity];
    this->workers = new pid_t[this->workersCount];

    this->parentChildFileDes = new int*[this->workersCount];
    this->childParentFileDes = new int*[this->workersCount];

    for (int i = 0; i < this->workersCount; ++i) 
    {
        this->parentChildFileDes[i] = new int[2];
        this->childParentFileDes[i] = new int[2];
    }
    
    // fill array with random numbers
    for(int i = 0; i < this->workersCount; ++i)
    {
        this->array[i] = rand() % 2;
    }
}

void ParallelCalculator::sum()
{
    int pipeResult;

    // create two pipes for each worker
    for(int i = 0; i < this->arrayCapacity; ++i)
    {
        pipeResult = pipe(this->parentChildFileDes[i]);

        // exit on failure
        if(pipeResult == -1)
        {
            exit(errno);
        }

        pipeResult = pipe(this->childParentFileDes[i]);

        // exit on failure
        if(pipeResult == -1)
        {
            exit(errno);
        }
    }

    int fac = this->arrayCapacity / this -> workersCount;

    for(int i = 0; i < this->workersCount; ++i)
    {
       // create a process
       this->workers[i] = fork();

        // exit on failure
        if(this->workers[i] == -1)
        {
            exit(errno);
        }

        if(this->workers[i] == 0)
        {
            int pid = getpid();

            // close write end of parent to child pipe
            close(this->parentChildFileDes[pid][WRITE_END]);

            // close read end of child to parent pipe
            close(this->childParentFileDes[pid][READ_END]);

            int from, to;
            int sum = 0;
            
            // read 'from' and 'to' from parent to child pipe
            read(this->parentChildFileDes[pid][READ_END], &from, sizeof(int));
            read(this->parentChildFileDes[pid][READ_END], &to, sizeof(int));


            // calculate sum from i to j
            for(int j = from; j < to; ++j)
            {
                sum += this->array[j];
            }

            // print sum
            std::cout << "Sum from " << from << " to " << to << " is " << sum << std::endl;

            // write sum into child to parent pipe
            write(this->childParentFileDes[pid][WRITE_END], &sum, sizeof(int)); 

            exit(0);
        }
        else
        {
            // close read end of parent to child pipe
            close(this->parentChildFileDes[this->workers[i]][READ_END]);

            // close write end of child to parent pipe
            close(this->childParentFileDes[this->workers[i]][WRITE_END]);

            int from = i * fac;
            int to = (i + 1) * fac;

            // up to end for the last element
            if(i == this->workersCount - 1)
            {
                to = workersCount;
            }
            
            // write 'from' and 'to' into parent to child pipe
            write(this->parentChildFileDes[this->workers[i]][WRITE_END], &from, sizeof(int));
            write(this->parentChildFileDes[this->workers[i]][WRITE_END], &to, sizeof(int));
        }
    }

    // wait child processes
    wait(NULL);

    int total = 0;

    for(int i = 0; i < this->workersCount; ++i)
    {
        int sum = 0;

        // read 'sum' from child to parent pipe
        read(this->childParentFileDes[this->workers[i]][READ_END], &sum, sizeof(int));

        total += sum;
    }

    std::cout << "Total sum is " << total << std::endl;
}

ParallelCalculator::~ParallelCalculator()
{
    delete [] this->array;
    delete[] this->workers;

    for (int i = 0; i < this->workersCount; ++i) 
    {
        delete [] this->parentChildFileDes[i];
        delete [] this->childParentFileDes[i];
    }

    delete[] this->parentChildFileDes;
    delete[] this->childParentFileDes;
}