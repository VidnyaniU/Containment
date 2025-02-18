#include <bits/stdc++.h>
#include <NTL/ZZ.h>
#include <NTL/matrix.h>
#include <NTL/mat_ZZ.h>
#include <NTL/ZZ_p.h>

using namespace std;
using namespace NTL;
class solveMatrix
{

public:
    solveMatrix();
    ZZ fact(int z);
    // vector<vector<int>> combo(vector<int> &arr, int n, int r);
    vector<int> get_next(vector<int> combo, int n, int r);
    // vector<int> getNext(vector<vector<int>> indicesCombination, int row, int indicesSize);
    // void extractMinorDet(mat_ZZ_p mat, vector<vector<int>> indicesCombination, long nCr, int indicesSize, string fileName);
    vector<int> get_kth_combination(int n, int r, int _index);
    mat_ZZ_p extractMinor(mat_ZZ_p matrix, vector<int> tempRow, vector<int> tempCol);
    // void extractMinorDet(mat_ZZ_p matrix, int k, long nCr, int n, int order_of_minor, int quota);
    void extractMinorDet(mat_ZZ_p matrix, int n, int world_rank, int np);

    // for augmentation part
    vector<int> setDiff(vector<int> combo, int order_of_mat);
    vector<int> get_next_indices(vector<int> set_diff_vec, vector<int> combo, vector<int> prev_combo_row, int dev, int order_of_mat);
    // mat_ZZ_p extractMinor(mat_ZZ_p matrix, vector<int> tempRow, vector<int> tempCol);
    void get_contained_matrix(mat_ZZ_p matrix, int processID);
};
