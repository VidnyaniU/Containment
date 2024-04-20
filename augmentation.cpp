#include <bits/stdc++.h>
#include "containment.hpp"
// find set difference

using namespace std;

vector<int> setDiff(vector<int> combo, int order_of_mat)
{
    int k = 0;
    int set_diff_vec_size = order_of_mat - combo.size();
    vector<int> set_diff_vec(set_diff_vec_size);
    vector<int> indices(order_of_mat); // Resize indices to the required size

    // Initialize indices
    for (int i = 0; i < order_of_mat; i++)
    {
        indices[i] = i;
    }

    for (int i = 0; i < order_of_mat; i++)
    {
        int found = 0;
        for (int j = 0; j < combo.size(); j++)
        {
            if (indices[i] == combo[j])
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            set_diff_vec[k++] = indices[i];
        }
    }

    return set_diff_vec;
}

// find those combinations >2 merge input combo and combinations one by one
vector<int> get_next(vector<int> combo, int n, int r)
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
// combo is input we get from result file

vector<int> get_next_indices(vector<int> set_diff_vec, vector<int> combo, vector<int> prev_combo_row, int dev, int order_of_mat)
{
    int i, j, x;
    int n = order_of_mat - combo.size();

    vector<int> indices_list(combo.size() + dev); // dev is deviation
    for (int l = 0; l < combo.size(); l++)

    {
        indices_list[l] = combo[l];
    }

    for (i = 0; i < dev; i++)
    {
        // c_a2[i] = set_diff_vec[c_a[i]]; // to be changed
        indices_list[i + 2] = set_diff_vec[prev_combo_row[i]];
    }

    // to find the rightmost element to increment
    x = dev - 1;
    while (x >= 0 && prev_combo_row[x] == n - dev + x)
    {
        x--;
    }

    // to increment the rightmost element and adjust subsequent elements
    if (x >= 0)
    {
        prev_combo_row[x]++;
        for (j = x + 1; j < dev; j++)
        {
            prev_combo_row[j] = prev_combo_row[j - 1] + 1;
        }
    }
    return indices_list;
}

// extract minor and determinant

int main()
{
    vector<int> combo_row = {0, 2};
    vector<int> combo_col = {5, 14};

    vector<int> set_diff_vec_row(18);
    vector<int> set_diff_vec_col(18);

    int order_of_mat = 20;
    int dev = 2;

    set_diff_vec_row = setDiff(combo_row, 20); // combo we get from input from result file later on
    set_diff_vec_col = setDiff(combo_col, 20);
    for (int i = 0; i < set_diff_vec_col.size(); i++)
    {
        cout << set_diff_vec_col[i] << " ";
    }
    cout << endl;

    // later to be used in extract_minor
    vector<int> prev_combo_row = {0, 1}; // this will be given from get_kth_combo

    int nCr = 153; // 18C2
    for (int row = 0; row < nCr; row++)

    {
        vector<int> next_indices_combo_row = get_next_indices(set_diff_vec_row, combo_row, prev_combo_row, 2, order_of_mat);
        cout << "Row::" << row + 1 << endl;
        for (int i = 0; i < next_indices_combo_row.size(); i++)
        {
            cout << next_indices_combo_row[i] << " ";
        }
        // for columns

        vector<int> prev_combo_col = {0, 1}; // this will be given from get_kth_combo or may not who knows
        for (int col = 0; col < nCr; col++)

        {
            cout << endl
                 << "Col::" << col + 1 << endl;
            vector<int> next_indices_combo_col = get_next_indices(set_diff_vec_col, combo_col, prev_combo_col, 2, order_of_mat);
            for (int i = 0; i < next_indices_combo_col.size(); i++)
            {
                cout << next_indices_combo_col[i] << " ";
            }
            cout << endl;
            prev_combo_col = get_next(prev_combo_col, order_of_mat - combo_col.size(), dev);
        }
        cout << endl
             << "===============" << endl;
        prev_combo_row = get_next(prev_combo_row, order_of_mat - combo_row.size(), dev);
    }

    return 0;
}