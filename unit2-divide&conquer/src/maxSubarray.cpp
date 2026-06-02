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
    In general, given a profit/loss vector of length n, the goal is to find
    the subvector that achieves the maximum total profit. Design an algorithm
    that performs this task as efficiently as possible.
*/

/*
    DESCRIPTIVE RECURSION:
    T(n) = 2T(n/2) + O(n)s

    EFICIENCY: (Master Theorem)
    O(n logn)
*/

struct subarrayProfit
{
    vector<int> left;
    vector<int> right;
    vector<int> currentSol;
};

int profit(const vector<int> &v)
{
    int suma = 0;
    for (int profit : v)
    {
        suma += profit;
    }
    return suma;
}

vector<int> subarray(const vector<int> &v, int start, int end)
{
    vector<int> newV;
    for (int i = start; i <= end; ++i)
        newV.push_back(v[i]);

    return newV;
}

// DIVIDE AND CONQUER ALGORITHM
// Idea:      get from every recursive call the maximum total profit starting
//            from the first or the last element of the subarray and the
//            maximum total profit current subarray.
// Input:     ·) v, the given profit/loss vector.
//            ·) start, the beginning element of the current subarray.
//            ·) end, the last element of the current subarray.
// Output:    ·) subarrayProfit, represent the left and right best profit
//               subarrays and the current best solution.
subarrayProfit maxSubarray(const vector<int> &v, int start, int end)
{

    // Base case: the current subarray has one element.
    if (start == end)
        return {{v[start]}, {v[start]}, {v[start]}};

    int mid = start + (end - start) / 2;
    subarrayProfit subarrayLeft = maxSubarray(v, start, mid);    // ~O(n)
    subarrayProfit subarrayRight = maxSubarray(v, mid + 1, end); // ~O(n)

    subarrayProfit actual;

    // calculate right profit of the current subarray.
    int rightProfitLeft = profit(subarrayLeft.right);   // ~O(n)
    int rightProfitRight = profit(subarrayRight.right); // ~O(n)

    actual.right = subarrayRight.right;
    if (rightProfitLeft >= rightProfitRight && rightProfitLeft > 0)
    {
        actual.right = subarray(v, mid + 1, end);

        actual.right.insert(actual.right.begin(),
                            subarrayLeft.right.begin(),
                            subarrayLeft.right.end());
    }

    // calculate left profit of the current subarray.
    int leftProfitLeft = profit(subarrayLeft.left);   // ~O(n)
    int leftProfitRight = profit(subarrayRight.left); // ~O(n)

    // ARREGLAR ESTO, COGE SOLAMENTE LAS PARTES
    actual.left = subarrayLeft.left;
    if (leftProfitRight >= leftProfitLeft && leftProfitRight > 0)
    {
        actual.left = subarray(v, start, mid); // ~O(n)

        actual.left.insert(actual.left.end(),
                           subarrayRight.left.begin(),
                           subarrayRight.left.end()); // ~O(n)
    }

    // calculate current maximum profit subarray.
    /// calculate the maximum of the left and right subarrays' maximums.
    actual.currentSol = subarrayLeft.currentSol;
    if (profit(subarrayRight.currentSol) > profit(subarrayLeft.currentSol))
        actual.currentSol = subarrayRight.currentSol;

    /// now, compare it with the actual left and right profit subarrays and the
    /// center cross.
    int profitCurrentSol = profit(actual.currentSol);
    int profitLeft = profit(actual.left);
    int profitRight = profit(actual.right);
    vector<int> subarrayCenter = subarrayLeft.right;
    subarrayCenter.insert(subarrayCenter.end(),
                          subarrayRight.left.begin(),
                          subarrayRight.left.end());
    int profitCenter = profit(subarrayCenter);
    if (profitLeft >= profitCurrentSol && profitLeft >= profitRight)
    {
        actual.currentSol = actual.left;
    }
    else if (profitRight >= profitCurrentSol && profitRight >= profitLeft)
    {
        actual.currentSol = actual.right;
    }

    if (profitCenter > profit(actual.currentSol))
        actual.currentSol = subarrayCenter;

    return actual;
}

vector<int> maxSubarray(const vector<int> &v)
{
    return (maxSubarray(v, 0, v.size() - 1).currentSol);
}

void printVector(const vector<int> &v)
{
    cout << "{" << v[0];
    for (int i = 1; i < v.size(); ++i)
    {
        cout << ", " << v[i];
    }
    cout << "}" << endl;
}

int main(int argc, char const *argv[])
{

    const vector<int> VECTOR = {-2, 10, 20, -5};

    printVector(maxSubarray(VECTOR));

    return 0;
}