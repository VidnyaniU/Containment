#include "containment.hpp"

using namespace std;
using namespace NTL;
// find set difference
vector<int> solveMatrix::setDiff(vector<int> combo, int order_of_mat)
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

// combo is input we get from result file

vector<int> solveMatrix::get_next_indices(vector<int> set_diff_vec, vector<int> combo, vector<int> prev_combo_row, int dev, int order_of_mat)
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

void solveMatrix::get_contained_matrix(mat_ZZ_p matrix, int processID)
{

    // things to change ::
    // if we take input as 3 by 3 the input of rows and cols changes
    // dev , prev_combo_row and col

    int order_of_mat = matrix.NumRows();
    int dev = 3;
    ZZ nCr = fact(order_of_mat - dev) / (fact(dev) * fact(order_of_mat - dev - dev));
    // long nCr = conv<long>(comboN);
    // cout << "nCr::" << nCr << endl;
    // input file
    string in_filename = "results/result_" + to_string(processID) + ".txt";
    ifstream infile(in_filename);

    // output file
    stringstream filenameStream;
    filenameStream << "results_30_1/con_30_1_1d" << processID << ".txt";
    string out_filename = filenameStream.str();

    ofstream fout(out_filename, ios::app);
    if (!infile.is_open())
    {
        cerr << "Error: Could not open file " << in_filename << " " << endl;
        exit(1);
    }
    int row_count = 1;
    while (infile)
    {

        int row1, row2, col1, col2;
        infile >> row1 >> row2 >> col1 >> col2;

        if (infile.eof())
        {
            break;
        }
        // fout << endl
        //  << "=======ROW :: " << row_count << " ========" << endl;
        vector<int> combo_row = {row1, row2};
        vector<int> combo_col = {col1, col2};

        vector<int> set_diff_vec_row(order_of_mat - combo_row.size());
        vector<int> set_diff_vec_col(order_of_mat - combo_row.size());

        set_diff_vec_row = setDiff(combo_row, order_of_mat); // combo we get from input from result file later on
        set_diff_vec_col = setDiff(combo_col, order_of_mat);

        vector<int> prev_combo_row = {0, 1}; // this will be given from get_kth_combo

        for (int row = 0; row < nCr; row++)

        {
            vector<int> next_indices_combo_row = get_next_indices(set_diff_vec_row, combo_row, prev_combo_row, 2, order_of_mat);
            // cout << "Row::" << row + 1 << endl
            //      << endl;
            // for (int i = 0; i < next_indices_combo_row.size(); i++)
            // {
            //     cout << next_indices_combo_row[i] << " ";
            // }
            // for columns

            vector<int> prev_combo_col = {0, 1}; // this will be given from get_kth_combo or may not who knows
            for (int col = 0; col < nCr; col++)

            {
                // cout << endl
                //      << "Col::" << col + 1 << endl;
                vector<int> next_indices_combo_col = get_next_indices(set_diff_vec_col, combo_col, prev_combo_col, 2, order_of_mat);
                // for (int i = 0; i < next_indices_combo_col.size(); i++)
                // {
                //     cout << next_indices_combo_col[i] << " ";
                // }
                // cout << endl;

                // extract minor and find determinant  here
                ZZ_p det = determinant(extractMinor(matrix, next_indices_combo_row, next_indices_combo_col));
                // cout << "det:: " << det << endl;
                if (det == 0)
                {
                    if (fout.is_open())
                    {

                        for (int index = 0; index < next_indices_combo_row.size(); index++)
                        {
                            fout << next_indices_combo_row[index] << " ";
                        }
                        // fout << "| ";
                        for (int index = 0; index < next_indices_combo_col.size(); index++)
                        {

                            fout << next_indices_combo_col[index] << " ";
                        }
                        fout << endl;
                    }
                    else
                        cerr << "Unable to open the file!" << endl;
                }

                prev_combo_col = get_next(prev_combo_col, order_of_mat - combo_col.size(), dev);
            }
            // cout << endl
            //      << "===============" << endl;
            prev_combo_row = get_next(prev_combo_row, order_of_mat - combo_row.size(), dev);
        }
        row_count++;
    }
}
// int main()
// {

//     solveMatrix m1; // creating object for constructor initialization of ZZ_p
//     ifstream file("inputMatrix.txt");
//     // ifstream file("kernel_78.txt");

//     mat_ZZ_p matrix;
//     // cout << "Order of matrix :: " << n << endl;
//     // Read the matrix from the file
//     file >> matrix;
//     int order_of_mat = matrix.NumRows();
//     // file1 << mat;

//     // Close the file
//     file.close();
//     // int order_of_mat = 20;

//     cout << "Successfully Done!" << endl;
//     return 0;
// }