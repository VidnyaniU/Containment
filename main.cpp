#include <bits/stdc++.h>
#include "containment.hpp"
using namespace std;
using namespace NTL;
int main()
{
    solveMatrix m1;

    int orderOfMat = 20;
    int orderOfMinor;
    cout << "Enter the order of the minor :: ";
    cin >> orderOfMinor;
    cout << endl;

    ifstream file("inputMatrix.txt");
    // ofstream file1("output.txt");
    mat_ZZ_p matrix;
    // Read the matrix from the file
    file >> matrix;
    // file1 << mat;

    // Close the file
    file.close();
    // vector<vector<int>> matrix = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    long nCr = m1.fact(orderOfMat) / (m1.fact(orderOfMinor) * m1.fact(orderOfMat - orderOfMinor));
    // first combination
    // vector<int> combo(orderOfMinor);
    // for (int i = 0; i < orderOfMinor; i++)
    // {
    //     combo[i] = i;
    //     // cout << combo[i] << " ";
    // }
    // cout << endl;
    int k = 0;
    m1.extractMinorDet(matrix, k, nCr, orderOfMat, orderOfMinor);
    return 0;
}