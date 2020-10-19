// Name: Ex3.cpp
// Author: cdrisko
// Date: 05/06/2020-09:55:58
// Description: Forcing an order to printing using a barrier

#include <iostream>

#include <mpi.h>

int main(int argc, char** argv)
{
    int worldRank {}, index {}, result {}, numberToRecieve {}, numberToSend {2};
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);

    if (worldRank == 0)
        for (index = 1; index < 2; ++index)
            MPI_Send(&numberToSend, 1, MPI_INT, index, 10, MPI_COMM_WORLD);
    else
    {
        MPI_Recv(&numberToRecieve, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        result = numberToRecieve * worldRank;
    }

    for (index = 1; index < 2; ++index)
    {
        MPI_Barrier(MPI_COMM_WORLD);

        if (index == worldRank)
            std::cout << "PE " << worldRank << "'s result is " << result << std::endl;
    }

    if (worldRank == 0)
    {
        for (index = 1; index < 2; ++index)
        {
            MPI_Recv(&numberToRecieve, 1, MPI_INT, index, 10, MPI_COMM_WORLD, &status);
            result += numberToRecieve;
        }

        std::cout << "Total is " << result << std::endl;
    }
    else
        MPI_Send(&result, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);

    MPI_Finalize();
}
