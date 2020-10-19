// Name: Exercise1.cpp
// Author: cdrisko
// Date: 05/06/2020-10:44:27
// Description: Send data to nearest neighbor in a circular shift (i.e. 0 and 7 are neighbors)

#include <iostream>

#include <mpi.h>

int main(int argc, char** argv)
{
    int worldRank {}, numberToRecieve {}, numberToSend {42};
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);

    /* Code goes here */

    MPI_Finalize();
}
