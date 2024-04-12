#include <iostream>
#include <vector>
#include <cmath>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;
ulong fact(int z)
{
    ulong f = 1;
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
vector<ulong> get_kth_combination(ulong n, ulong r, ulong _index)
{
    if (r < 0 || r > n)
    {
        cerr << "\n get_kth_combination :: Value error : invalid value of r :: " << r << endl;
        return vector<ulong>();
    }

    ZZ index = conv<ZZ>(_index);
    vector<ulong> result_vec(r);

    // Initialize the first combination: [0, 1, ..., r-1]
    for (ulong i = 0; i < r; ++i)
    {
        result_vec[i] = i;
    }

    for (ulong i = 1; i < _index; ++i)
    {
        ulong j = r - 1;
        while (result_vec[j] == n - r + j)
        {
            --j;
        }

        ++result_vec[j];
        for (ulong k = j + 1; k < r; ++k)
        {
            result_vec[k] = result_vec[k - 1] + 1;
        }
    }

    return result_vec;
}

int main()
{
    ulong n = 5;
    ulong r = 2;
    ulong nCr = fact(n) / (fact(r) * fact(n - r));
    ulong k;
    cout << "Enter k :: " << endl;
    cin >> k;

    vector<ulong> result = get_kth_combination(n, r, k);

    if (k <= nCr)
    {
        cout << "K-th Combination: ";
        for (ulong i : result)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "Only " << nCr << " combinations are possible!" << endl;
    }

    return 0;
}
