#include <bits/stdc++.h>
#include <NTL/ZZ.h>
#include <NTL/matrix.h>
#include <NTL/mat_ZZ.h>
#include <NTL/ZZ_p.h>
#include "containment.hpp"
using namespace std;
using namespace NTL;

// constructor for initializing ZZ_p
// solveMatrix::solveMatrix()
// {
//     ZZ p = conv<ZZ>("101");
//     ZZ_p::init(p);
//     // mat_ZZ_p mat;
// }

// to find factorial of a number which is later on used to find number of combinations
long fact(int z)
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
// function to get next combination from the combination vector

vector<int> get_next(vector<int> &combo, int n, int r)
{
    // Find the rightmost element to increment
    int x = r - 1;
    while (x >= 0 && combo[x] == n - r + x)
    {
        x--;
    }

    // termination condition
    if (x < 0)
    {
        return {};
    }
    // Increment the rightmost element and adjust subsequent elements
    combo[x]++;
    for (int j = x + 1; j < r; j++)
    {
        combo[j] = combo[j - 1] + 1;
    }

    return combo;
}
// this function will extract a minor and find its determinant
void extractMinorDet(mat_ZZ matrix, vector<int> combo, long nCr, int n, int indicesSize)
{
    // ofstream file1("output.txt");
    // ofstream file1(fileName);

    mat_ZZ minorMatrix;
    minorMatrix.SetDims(indicesSize, indicesSize);
    int i, j;
    ;
    vector<int> tempRow = combo; // first row indices
    for (i = 1; i <= nCr; ++i)
    {
        vector<int> tempCol = combo; // first col indices

        for (j = 1; j <= nCr; ++j)
        {
            cout << "======= MATRIX NO. " << i * j << "========" << endl;

            for (int matRow = 0; matRow < indicesSize; matRow++)
            {
                for (int matCol = 0; matCol < indicesSize; matCol++)
                {
                    minorMatrix[matRow][matCol] = matrix[tempRow[matRow]][tempCol[matCol]];
                    cout << minorMatrix[matRow][matCol] << " ";
                }
                cout << endl;
            }

            ZZ det = determinant(minorMatrix);
            cout << "Determinant :: " << det << endl;
            cout << "===========================" << endl;
            tempCol = get_next(tempCol, n, indicesSize);
        }
        tempRow = get_next(tempRow, n, indicesSize);
    }
    cout << "Final matrix count :: " << (i - 1) * (j - 1) << endl;
}

int main()
{

    int orderOfMat = 20;
    int orderOfMinor;
    cout << "Enter the order of the minor :: ";
    cin >> orderOfMinor;
    cout << endl;

    ifstream file("inputMatrix.txt");
    // ofstream file1("output.txt");
    mat_ZZ matrix;
    // Read the matrix from the file
    file >> matrix;
    // file1 << mat;

    // Close the file
    file.close();
    // vector<vector<int>> matrix = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    long nCr = fact(orderOfMat) / (fact(orderOfMinor) * fact(orderOfMat - orderOfMinor));
    // first combination
    vector<int> combo(orderOfMinor);
    for (int i = 0; i < orderOfMinor; i++)
    {
        combo[i] = i;
        // cout << combo[i] << " ";
    }
    // cout << endl;
    extractMinorDet(matrix, combo, nCr, orderOfMat, orderOfMinor);
    return 0;
}