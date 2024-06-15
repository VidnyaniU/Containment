#include <bits/stdc++.h>
#include <mpi.h>
#include "containment.hpp"
using namespace std;
using namespace NTL;
int main(int argc, char **argv)
{
    solveMatrix m1;

    ifstream file("inputMatrix.txt");

    mat_ZZ_p matrix;

    // Read the matrix from the file
    file >> matrix;
    int orderOfMat = matrix.NumRows();

    // Close the file
    file.close();

    // MPI implementation
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // m1.extractMinorDet(matrix, orderOfMat, world_rank, world_size); // for 2 by 2

    m1.get_contained_matrix(matrix, world_rank); // for containment
    MPI_Barrier(MPI_COMM_WORLD);                 // Synchronize all processes

    if (world_rank == 0)
    {
        cout << "Successfully executed!!" << endl;
    }
    MPI_Finalize();

    return 0;
}

// command for compile and run
// to get combinations
// mpic++ containment.cpp main.cpp -o con -lntl -lgmp -pthread
// time mpirun -n 4 ./con
// to get containment
// mpic++ containment.cpp augmentation.cpp main.cpp -o au -lntl -lgmp -pthread
// time mpirun -n 4 ./au