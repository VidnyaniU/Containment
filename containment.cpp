#include <bits/stdc++.h>
#include <NTL/ZZ.h>
#include <NTL/matrix.h>
#include <NTL/mat_ZZ.h>
#include <NTL/ZZ_p.h>
#include "containment.hpp"
using namespace std;
using namespace NTL;

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

// function to get next combination from the combination vector

vector<int> solveMatrix::get_next(vector<int> combo, int n, int r)
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

vector<int> solveMatrix::get_kth_combination(int n, int r, int _index)
{
    if (r < 0 || r > n)
    {
        cerr << "\n get_kth_combination :: Value error : invalid value of r :: " << r << endl;
        return vector<int>();
    }

    ZZ index = conv<ZZ>(_index);
    vector<int> result_vec(r);

    // Initialize the first combination: [0, 1, ..., r-1]
    for (int i = 0; i < r; ++i)
    {
        result_vec[i] = i;
    }

    for (int i = 1; i < _index; ++i)
    {
        int j = r - 1;
        while (result_vec[j] == n - r + j)
        {
            --j;
        }

        ++result_vec[j];
        for (int k = j + 1; k < r; ++k)
        {
            result_vec[k] = result_vec[k - 1] + 1;
        }
    }

    return result_vec;
}

mat_ZZ_p solveMatrix::extractMinor(mat_ZZ_p matrix, vector<int> tempRow, vector<int> tempCol)
{
    int order_of_minor = tempRow.size();
    mat_ZZ_p minor_matrix;
    minor_matrix.SetDims(order_of_minor, order_of_minor);
    for (int matRow = 0; matRow < order_of_minor; matRow++)
    {
        for (int matCol = 0; matCol < order_of_minor; matCol++)
        {
            minor_matrix[matRow][matCol] = matrix[tempRow[matRow]][tempCol[matCol]];
            // cout << minor_matrix[matRow][matCol] << " ";
        }
        // cout << endl;
    }

    return minor_matrix;
}
// this function will extract a minor and find its determinant

/*
int cnt = 0;
void solveMatrix::extractMinorDet(mat_ZZ_p matrix, int k, long nCr, int n, int order_of_minor, int quota)
{
    int row, col;
    vector<int> combo = get_kth_combination(n, order_of_minor, k);
    vector<int> tempRow = combo; // first row indices
    for (row = 1; row < quota; ++row)
    {
        vector<int> tempCol = get_kth_combination(n, order_of_minor, 0); // first col indices

        for (col = 1; col < nCr; ++col)
        {
            cnt++;
            cout << "======= MATRIX NO. " << row * col << "======== " << endl;
            ZZ_p det = determinant(extractMinor(matrix, tempRow, tempCol));
            cout << "Determinant :: " << det << endl;
            cout << "===========================" << cnt << endl;
            tempCol = get_next(tempCol, n, order_of_minor);
        }
        tempRow = get_next(tempRow, n, order_of_minor);
    }

    // cout << "Final matrix count :: " << (row - 1) * (col - 1) << endl;
}*/

ofstream p0_out("p0_indices_2.txt");
ofstream p1_out("p1_indices_2.txt");
ofstream p2_out("p2_indices_2.txt");
ofstream p3_out("p3_indices_2.txt");

// ofstream col_out("col_indices_2.txt");

void solveMatrix::extractMinorDet(mat_ZZ_p matrix, int n, int processID)
{
    // int n =  matrix.NumRows();
    // cout << "Processor :: " << processID << endl;

    int order_of_minor = 2;
    long nCr = fact(n) / (fact(order_of_minor) * fact(n - order_of_minor));
    int np = 4; // num of processors
    int quota = nCr / np;
    int k = processID * quota;

    int row, col;
    vector<int> combo = get_kth_combination(n, order_of_minor, k);
    vector<int> tempRow = combo; // first row indices
    for (row = 1; row <= quota; ++row)
    {
        vector<int> tempCol = get_kth_combination(n, order_of_minor, 0); // first col indices

        for (col = 1; col < nCr; ++col)
        {
            // cout << "======= MATRIX NO. " << row * col << "======== " << endl;
            // fout << "Processor :: " << processID << endl;
            // fout << "======= MATRIX NO. " << row * col << "======== " << endl;

            ZZ_p det = determinant(extractMinor(matrix, tempRow, tempCol));
            // cout << "Determinant :: " << det << endl;
            if (det == 0)
            {
                // row_out << endl;
                // col_out << endl;
                switch (processID)
                {
                case 0:
                {
                    for (int index = 0; index < order_of_minor; index++)
                    {
                        p0_out << tempRow[index] << " ";
                        // fout << endl;
                        p0_out << tempCol[index] << " ";
                    }
                    p0_out << endl
                           << "==========" << endl;
                }
                break;
                case 1:
                {
                    for (int index = 0; index < order_of_minor; index++)
                    {
                        p1_out << tempRow[index] << " ";
                        // fout << endl;
                        p1_out << tempCol[index] << " ";
                    }
                    p1_out << endl
                           << "==========" << endl;
                }
                break;
                case 2:
                {
                    for (int index = 0; index < order_of_minor; index++)
                    {
                        p2_out << tempRow[index] << " ";
                        // fout << endl;
                        p2_out << tempCol[index] << " ";
                    }
                    p2_out << endl
                           << "==========" << endl;
                }
                break;
                case 3:
                {
                    for (int index = 0; index < order_of_minor; index++)
                    {
                        p3_out << tempRow[index] << " ";
                        // fout << endl;
                        p3_out << tempCol[index] << " ";
                    }
                    p3_out << endl
                           << "==========" << endl;
                }
                break;
                default:
                    cout << "Lmao !!" << endl;
                }
                /*
                for (int index = 0; index < order_of_minor; index++)
                {
                    row_out << tempRow[index] << " ";
                    // fout << endl;
                    row_out << tempCol[index] << " ";
                }
                row_out << endl
                        << "==========" << endl;*/

                // col_out << endl
                // << "==========" << endl;
            }

            // fout << "Determinant :: " << det << endl;

            // cout << "===========================" << endl;
            // fout << "===========================" << endl;

            tempCol = get_next(tempCol, n, order_of_minor);
        }
        tempRow = get_next(tempRow, n, order_of_minor);
    }
    // cout << "Final matrix count :: " << (row - 1) * (col - 1) << endl;
}
// fout.close();