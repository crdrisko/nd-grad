// Name: Ex1.cpp
// Author: cdrisko
// Date: 05/06/2020-09:30:05
// Description: Print hello from each processing element using MPI

#include <iostream>

#include <mpi.h>

int main(int argc, char** argv)
{
    int worldRank {};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);

    std::cout << "Hello from " << worldRank << std::endl;

    MPI_Finalize();
}
