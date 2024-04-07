#include <iostream>
#include <vector>
using namespace std;
long fact(int z)
{
    long f = 1;
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
vector<int> get_next(vector<int> &combo, int n, int r)
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

int main()
{
    int n = 4, r = 2;
    vector<int> combo(r);
    int nCr = fact(n) / (fact(r) * fact(n - r));
    // first combination
    for (int i = 0; i < r; i++)
    {
        combo[i] = i;
        cout << combo[i];
    }
    cout << endl;

    for (int i = 2; i <= nCr; i++)
    {
        combo = get_next(combo, n, r);

        for (int i = 0; i < r; i++)
        {
            cout << combo[i];
        }
        cout << endl;
    }

    return 0;
}