#include <bits/stdc++.h>
#include "containment.hpp"
using namespace std;

int main()
{
    // int orderOfMatrix = 20;
    vector<int> arr = {0, 1, 2, 3, 4};
    // for (int i = 0; i < orderOfMatrix; i++)
    // {
    //     arr.push_back(i);
    // }
    int n = arr.size();
    // cout<<n<<endl;
    int r = 2;
    solveMatrix m1;

    ifstream file("inputMatrix.txt");
    // ofstream file1("output.txt");
    Mat<ZZ> matrix;
    // Read the matrix from the file
    file >> matrix;
    // file1 << mat;

    cout << determinant(matrix) << endl;

    // Close the file
    file.close();
    // file1.close();
    int mat[5][5] = {
        {18, 24, 39, 4, 35},
        {6, 27, 8, 8, 89},
        {11, 2, 14, 14, 13},
        {19, 17, 18, 12, 12},
        {23, 65, 34, 12, 12}};

    int nCr = m1.fact(n) / (m1.fact(r) * m1.fact(n - r));
    // cout << nCr << endl;
    vector<vector<int>> combinations = m1.combo(arr, n, r);
    // for (int i = 0; i < nCr; i++)
    // {
    //     for (int j = 0; j < r; j++)
    //     {
    //         cout << combinations[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // m1.extractMinorDet(mat, combinations, nCr, r);
    return 0;
}