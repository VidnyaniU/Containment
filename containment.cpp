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
ZZ solveMatrix::fact(int z)
{
    ZZ f = conv<ZZ>("1");
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
        }
    }

    return minor_matrix;
}
// this function will extract a minor and find its determinant

void solveMatrix::extractMinorDet(mat_ZZ_p matrix, int n, int processID, int np)
{

    int order_of_minor = 2;
    ZZ comboN = fact(n) / (fact(order_of_minor) * fact(n - order_of_minor));
    long nCr = conv<long>(comboN);
    int quota = nCr / np;
    int k = processID * quota;

    int row, col;

    stringstream filenameStream;
    filenameStream << "results/result_" << processID << ".txt";
    string filename = filenameStream.str();

    ofstream fout(filename, ios::app);

    vector<int> combo = get_kth_combination(n, order_of_minor, k);
    vector<int> tempRow = combo; // first row indices
    for (row = 1; row <= quota; ++row)
    {
        vector<int> tempCol = get_kth_combination(n, order_of_minor, 0); // first col indices

        for (col = 1; col < nCr; ++col)
        {
            ZZ_p det = determinant(extractMinor(matrix, tempRow, tempCol));
            if (det == 0)
            {

                if (fout.is_open())
                {

                    for (int index = 0; index < order_of_minor; index++)
                    {
                        fout << tempRow[index] << " ";
                    }
                    // fout << "| ";
                    for (int index = 0; index < order_of_minor; index++)
                    {

                        fout << tempCol[index] << " ";
                    }
                    fout << endl;
                }
                else
                    cerr << "Unable to open the file!";
            }

            tempCol = get_next(tempCol, n, order_of_minor);
        }
        tempRow = get_next(tempRow, n, order_of_minor);
    }
    // fout.close();
}
// fout.close();