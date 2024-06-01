#include <bits/stdc++.h>
#include <mpi.h>
#include "containment.hpp"
using namespace std;
using namespace NTL;
int main(int argc, char **argv)
{
    solveMatrix m1;

    // int orderOfMat = 20;
    // int orderOfMinor;
    // cout << "Enter the order of the minor :: ";
    // cin >> orderOfMinor;
    // cout << endl;

    ifstream file("inputMatrix.txt");
    // ifstream file("kernel_78.txt");

    // ofstream file1("output.txt");
    mat_ZZ_p matrix;
    // cout << "Order of matrix :: " << n << endl;
    // Read the matrix from the file
    file >> matrix;
    int orderOfMat = matrix.NumRows();
    // file1 << mat;

    // Close the file
    file.close();

    /*long nCr = m1.fact(orderOfMat) / (m1.fact(orderOfMinor) * m1.fact(orderOfMat - orderOfMinor));

    int np = 4;           // num of processors
    int quota = nCr / np; // quota of each processor quota * nCr minors
    int k = 0;
    for (int i = 0; i < np; i++)
    {
        k = i * quota;

        cout << "\n========================== i :: " << i << "\t k :: " << k << "\t quota :: =======================" << quota << endl;
        // m1.extractMinorDet(matrix, k, nCr, orderOfMat, orderOfMinor, quota);
        cout << "======whooooo check point!!======== i :: " << i << endl;
    }
    ulong extraLeftRowInd = nCr - quota * np;

    cout << "extraLeftRowInd:: " << extraLeftRowInd << endl;
    // cout << "k:: " << k + 1 << endl;

    // m1.extractMinorDet(matrix, 188, nCr, orderOfMat, orderOfMinor, quota);
    // m1.extractMinorDet(matrix, k + 1, nCr, orderOfMat, orderOfMinor, quota);
    */

    // MPI implementation
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // m1.extractMinorDet(matrix, orderOfMat, world_rank, world_size);

    m1.get_contained_matrix(matrix, world_rank);
    MPI_Barrier(MPI_COMM_WORLD); // Synchronize all processes

    if (world_rank == 0)
    {
        cout << "Successfully executed!!" << endl;
    }
    MPI_Finalize();
    // string filename = "final_output_2by2.txt";

    return 0;
}

// command for compile and run
// mpic++ containment.cpp augmentation.cpp main.cpp -o au -lntl -lgmp -pthread
// time mpirun -n 4 ./au