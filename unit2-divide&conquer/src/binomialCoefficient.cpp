#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

/*
    Given a natural number n, determine whether it is a binomial coefficient of
    the form C(k,2) for some natural number k.

    That is: does there exist a natural number k such that n = k·(k−1)/2

    Examples:
    ·) 36 = C(9,2) → since 9·8/2 = 36
    ·) 499500 = C(1000,2) → since 1000·999/2 = 499500
*/

/*
    DESCRIPTIVE RECURSION:
    T(n) = T(n/2) + O(1)

    EFICIENCY: (Master Theorem)
    O(log n)
*/

// f(k) = k·(k−1)/2
// Eficiency: O(1)
long long f(long long k)
{
    return (long long)k * (k - 1) / 2;
}

// DIVIDE AND CONQUER ALGORITHM
// Idea:      binary search until the center element is n or left > right
// Input:     ·) n, the number to determine.
//            ·) left, the left edge of the search interval.
//            ·) right, the right edge of the search interval.
// Output:    ·) k, the given k such that n = C(k,2); if there is no possible k,
//              return -1.
long long divAndConq(long long n, long long left, long long right)
{

    // if there is no possible k such that n = k·(k−1)/2
    if (left > right)
        return -1;

    long long mid = left + (right - left) / 2;

    long long fMid = f(mid);

    // f is an incresing function:
    // if k is mid
    if (fMid == n)
        return mid;
    // if f(mid) < n
    else if (fMid < n)
        return divAndConq(n, mid + 1, right);
    // if f(mid) > n
    else
        return divAndConq(n, left, mid - 1);
}

int main(int argc, char const *argv[])
{

    if (argc != 2)
    {
        cerr << "Use: ./binomialCoefficient <N>" << endl;
        return 1;
    }

    long long n = 0;
    try
    {
        n = stoll(argv[1]);
    }
    catch (const invalid_argument &inv)
    {
        cout << "N must be a natural number" << endl;
    }

    cout << "N: " << n << endl;

    // the initial interval must be [1, n+1]: 1 = C(2,2), k = 2
    long long k = divAndConq(n, 1, n + 1);
    // if k exists
    if (k != -1)
    {
        cout << "N = C(" << k << ",2), " << n << " = " << k << "*" << k - 1 << "/2" << endl;
    }
    else
    {
        cout << "It is not a binomial coefficient of the form C(k,2)." << endl;
    }

    return 0;
}