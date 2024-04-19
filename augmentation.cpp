#include <bits/stdc++.h>
#include "containment.hpp"
// find set difference

using namespace std;

vector<int> setDiff(vector<int> combo, int order_of_mat)
{
    int k = 0;
    int ans_size = order_of_mat - combo.size();
    vector<int> ans(ans_size);
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
            ans[k++] = indices[i];
        }
    }

    return ans;
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

vector<int> get_next_indices(vector<int> set_diff_vec, vector<int> combo, vector<int> prev_combo, int dev, int order_of_mat)
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
        indices_list[i + 2] = set_diff_vec[prev_combo[i]];
    }

    // to find the rightmost element to increment
    x = dev - 1;
    while (x >= 0 && prev_combo[x] == n - dev + x)
    {
        x--;
    }

    // to increment the rightmost element and adjust subsequent elements
    if (x >= 0)
    {
        prev_combo[x]++;
        for (j = x + 1; j < dev; j++)
        {
            prev_combo[j] = prev_combo[j - 1] + 1;
        }
    }
    return indices_list;
}

// extract minor and determinant

int main()
{
    vector<int> combo = {0, 2};
    vector<int> ans(18);
    int order_of_mat = 20;
    int dev = 2;

    ans = setDiff(combo, 20); // combo we get from input from result file later on
   
    // later to be used in extract_minor
    vector<int> prev_combo = {0, 1}; // this will be given from get_kth_combo
    int nCr = 153;
    for (int i = 0; i < nCr; i++)

    {
        vector<int> next_indices_combo = get_next_indices(ans, combo, prev_combo, 2, order_of_mat);
        for (int i = 0; i < next_indices_combo.size(); i++)
        {
            cout << next_indices_combo[i] << " ";
        }
        cout << endl
             << "===============" << endl;
        prev_combo = get_next(prev_combo, order_of_mat - combo.size(), dev);
    }

    return 0;
}