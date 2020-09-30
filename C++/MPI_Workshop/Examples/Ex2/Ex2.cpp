// Name: Ex2.cpp
// Author: cdrisko
// Date: 05/06/2020-09:46:38
// Description: Send and recieve a number between two different processing elements

#include <iostream>

#include <mpi.h>

int main(int argc, char** argv)
{
    int worldRank {}, numberToRecieve {}, numberToSend {42};
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);

    if (worldRank == 0)
    {
        MPI_Recv(&numberToRecieve, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        std::cout << "Number recieved is: " << numberToRecieve << std::endl;
    }
    else
        MPI_Send(&numberToSend, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);

    MPI_Finalize();
}
