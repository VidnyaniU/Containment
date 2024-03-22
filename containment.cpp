#include <bits/stdc++.h>
#include <NTL/ZZ.h>
#include <NTL/matrix.h>
#include <NTL/mat_ZZ.h>
#include <NTL/ZZ_p.h>
#include "containment.hpp"
using namespace std;
using namespace NTL;
ofstream file1("output.txt");

// constructor for initializing ZZ_p
solveMatrix::solveMatrix()
{
    ZZ p = conv<ZZ>("101");
    ZZ_p::init(p);
    // mat_ZZ_p mat;
}

// to find factorial of a number which is later on used to find number of combinations
long solveMatrix::fact(int z)
{
    long f = 1;
    int i;
    if (z == 0)
    {
        return (f);
    }
    else
    {
        for (i = 1; i <= z; i++)
        {
            f = f * i;
        }
    }
    return (f);
}

// this function returns all the combinations of the indices
vector<vector<int>> solveMatrix::combo(vector<int> &arr, int n, int r)
{
    int nCr = fact(n) / (fact(r) * fact(n - r));

    // Allocate memory for the 2D array of combinations
    vector<vector<int>> comboArr(nCr, vector<int>(r));
    int count = 0;

    int i, j, x, k = 0;
    vector<int> c_a(r); // Array to store the current combination

    // First combination
    for (i = 0; i < r; i++)
    {
        c_a[i] = i;
    }

    while (1)
    {
        // Copy the current combination to the 2D array
        for (i = 0; i < r; i++)
        {
            comboArr[count][i] = arr[c_a[i]];
        }
        count++;

        // Find the rightmost element to increment
        x = r - 1;
        while (x >= 0 && c_a[x] == n - r + x)
        {
            x--;
        }

        // Termination condition
        if (x < 0)
        {
            break;
        }

        // Increment the rightmost element and adjust subsequent elements
        c_a[x]++;
        for (j = x + 1; j < r; j++)
        {
            c_a[j] = c_a[j - 1] + 1;
        }
    }

    return comboArr;
}

// function to get next combination from the combination vector
vector<int> solveMatrix ::getNext(vector<vector<int>> indicesCombination, int row, int indicesSize)
{
    vector<int> tempIndices;
    for (int i = 0; i < indicesSize; i++)
    {
        tempIndices.push_back(indicesCombination[row][i]);
    }

    return tempIndices;
}

// this function will extract a minor and find its determinant
void solveMatrix::extractMinorDet(mat_ZZ_p matrix, vector<vector<int>> indicesCombination, long nCr, int indicesSize)
{
    mat_ZZ_p minorMatrix;
    minorMatrix.SetDims(indicesSize, indicesSize);
    int row = nCr;
    int col = indicesSize;

    for (int i = 0; i < row; ++i)
    {
        vector<int> tempRow;
        vector<int> tempCol;
        tempRow = getNext(indicesCombination, i, indicesSize);

        for (int j = 0; j < row; ++j)
        {
            cout << "======= MATRIX NO. " << i * j << "========" << endl;
            tempCol = getNext(indicesCombination, j, indicesSize);

            for (int matRow = 0; matRow < indicesSize; matRow++)
            {
                for (int matCol = 0; matCol < indicesSize; matCol++)
                {
                    minorMatrix[matRow][matCol] = matrix[tempRow[matRow]][tempCol[matCol]];
                    cout << minorMatrix[matRow][matCol] << " ";
                }
                cout << endl;
            }

            ZZ_p det = determinant(minorMatrix);
            cout << "Determinant :: " << det << endl;
            if (det == 0)
            {
            file1 << "======================" << endl;
                file1 << "Rows :: " << endl;
                for (int i = 0; i < indicesSize; i++)
                {
                    file1 << tempRow[i] << " ";
                }
                file1 << endl;
                file1 << "Cols :: " << endl;

                for (int i = 0; i < indicesSize; i++)
                {
                    file1 << tempCol[i] << " ";
                }
                file1 << endl;
            }
            cout << "================================" << endl;

            cout << endl;
        }
    }
}
// file1.close();