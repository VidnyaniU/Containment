#include <bits/stdc++.h>
#include "containment.hpp"
using namespace std;

int main()
{
    vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    // for (int i = 0; i < orderOfMatrix; i++)
    // {
    //     arr.push_back(i);
    // }
    int n = arr.size();
    // cout<<n<<endl;
    int r;
    cout << "Enter the order of the minor :: ";
    cin >> r;
    cout << endl;
    solveMatrix m1;

    ifstream file("inputMatrix.txt");
    // ofstream file1("output.txt");
    mat_ZZ_p matrix;
    // Read the matrix from the file
    file >> matrix;
    // file1 << mat;

    // cout << determinant(matrix) << endl;

    // Close the file
    file.close();

    long nCr = m1.fact(n) / (m1.fact(r) * m1.fact(n - r));
    // cout << nCr << endl;
    vector<vector<int>> combinations = m1.combo(arr, n, r);
    // for (int i = 0; i < nCr; i++)
    // {
    //     cout << endl
    //          << "Combo No." << i << endl;
    //     for (int j = 0; j < r; j++)
    //     {
    //         cout << combinations[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    string fileName_2 = "output_2.txt"; // file for 2 by 2 output
    // string fileName_3 = "output_3.txt"; // file for 3 by 3 output

    m1.extractMinorDet(matrix, combinations, nCr, r, fileName_2);
    return 0;
}