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
    A company wants to buy a set of beachfront plots to build a residential
    development. To do so, after consulting the local council, it has an array
    P of size n representing the coastline of plots. For a given plot, i, P[i]
    will have a value of 0 if it is not possible to build on it, and 1 if it is
    possible to build.
    Determine the maximum number of consecutive plots on which the project is
    allowed to be built.
*/

/*
    DESCRIPTIVE RECURSION:
    T(n) = 2T(n/2) + O(1)

    EFICIENCY: (Master Theorem)
    O(n)
*/

struct plotAvailability
{
    int left;         // number of consecutive plots starting from the left hand.
    int right;        // number of consecutives plots starting from the right hand.
    int maxConsPlots; // number of maximum consecutives plots in the subarray.
};

// DIVIDE AND CONQUER ALGORITHM
// Idea:      get from every recursive call the maximum number of consecutive
//            plots and from each side in each subarray.
// Input:     ·) v, the given vector of the plots' availability.
//            ·) start, the beginning element of the current subarray.
//            ·) end, the last element of the current subarray.
// Output:    ·) plotAvailability, maximum number of consecutive plots from
//               each of the sides.
plotAvailability maxConsPlots(const vector<int> &v, int start, int end)
{

    // Base case: the current subarray has one element.
    if (start == end)
        return {v[start], v[start], v[start]};

    int mid = start + (end - start) / 2;
    plotAvailability leftSubarray = maxConsPlots(v, start, mid);
    plotAvailability rightSubarray = maxConsPlots(v, mid + 1, end);

    plotAvailability actual;

    actual.left = leftSubarray.left;
    actual.right = rightSubarray.right;
    if (leftSubarray.right == 0 || rightSubarray.left == 0)
    {
        actual.maxConsPlots = leftSubarray.maxConsPlots;
        if (rightSubarray.maxConsPlots > leftSubarray.maxConsPlots)
            actual.maxConsPlots = rightSubarray.maxConsPlots;
    }
    else
    { // leftSubarray.right == 1 && rightSubarray.left == 1

        int leftSize = mid - start + 1;
        if (leftSize == leftSubarray.left)
            actual.left = leftSubarray.left + rightSubarray.left;

        int rightSize = end - mid;
        if (rightSize == rightSubarray.right)
            actual.right = rightSubarray.right + leftSubarray.right;

        actual.maxConsPlots = actual.left;
        int maxConsPlotsCenter = leftSubarray.right + rightSubarray.left;
        if (actual.right >= actual.left && actual.right >= maxConsPlotsCenter)
            actual.maxConsPlots = actual.right;
        else if (maxConsPlotsCenter >= actual.left && maxConsPlotsCenter >= actual.right)
            actual.maxConsPlots = maxConsPlotsCenter;
    }

    return actual;
}

int maxConsPlots(const vector<int> &v)
{
    if (v.empty())
        return 0;
    return (maxConsPlots(v, 0, v.size() - 1).maxConsPlots);
}

int main(int argc, char const *argv[])
{

    const vector<int> VECTOR = {1, 0, 1, 1, 1, 1, 0, 1, 0};

    cout << "Maximum number of consecutives plots: " << maxConsPlots(VECTOR) << endl;

    return 0;
}