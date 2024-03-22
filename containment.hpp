#include <bits/stdc++.h>
#include <NTL/ZZ.h>
#include <NTL/matrix.h>
#include <NTL/mat_ZZ.h>
using namespace std;
using namespace NTL;
class solveMatrix
{

public:
    solveMatrix();
    long fact(int z);
    vector<vector<int>> combo(vector<int> &arr, int n, int r);
    vector<int> getNext(vector<vector<int>> indicesCombination, int row, int indicesSize);
    void extractMinorDet(mat_ZZ_p mat, vector<vector<int>> indicesCombination, long nCr, int indicesSize);
};
