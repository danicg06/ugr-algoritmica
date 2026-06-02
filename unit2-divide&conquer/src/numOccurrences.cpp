#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <map>
#include <vector>

using namespace std;

/*
    Given an array of integers of size n, sorted in ascending order, and where
    duplicate numbers may exist, the goal is to count how many times a specific
    number x appears, or indicate that the number does not appear at all.
*/

/*
    DESCRIPTIVE RECURSION:
    T(n) = 2T(n/2) + O(1)

    EFICIENCY: (Master Theorem)
    O(n)
*/

int firstOccurrence(const vector<int> &v, int start, int end, int x)
{

    // if it is not in the subarray
    if (start > end)
        return -1;

    int mid = start + (end - start) / 2;

    // if mid is a occurrence of x
    if (v[mid] == x)
    {
        // if it is the first element of the subarray or the first occurrence
        if (mid == start || v[mid - 1] != x)
            return mid;
        // if there is more occurrences before the actual one.
        else
        {
            // v[mid-1] cannot produce segment violation because we ensure that
            // mid != start.
            return firstOccurrence(v, start, mid - 1, x);
        }
    }
    else
    { // mid is not a occurrence
        // if x's index is before mid
        if (v[mid] > x)
        {
            return firstOccurrence(v, start, mid - 1, x);
        }
        // if x's index is after mid
        // v[mid+1] cannot produce segment violation because we ensure that
        // mid != end in its declaration
        else
        {
            return firstOccurrence(v, mid + 1, end, x);
        }
    }
}

int lastOccurrence(const vector<int> &v, int start, int end, int x)
{

    // if it is not in the subarray
    if (start > end)
        return -1;

    int mid = start + (end - start) / 2;

    // if mid is a occurrence of x
    if (v[mid] == x)
    {
        // if it is the last element of the subarray or the last occurrence
        if (mid == end || v[mid + 1] != x)
            return mid;
        // if there is more occurrences after the actual one.
        else
        {
            return lastOccurrence(v, mid + 1, end, x);
        }
    }
    else
    { // mid is not a occurrence
        // if x's index is before mid
        if (v[mid] > x)
        {
            return lastOccurrence(v, start, mid - 1, x);
        }
        // if x's index is after mid
        else
        {
            return lastOccurrence(v, mid + 1, end, x);
        }
    }
}

// DIVIDE AND CONQUER ALGORITHM
// Idea:      search the first and last index of the element in the vector.
// Input:     ·) v, the given vector of integers.
//            ·) start, the beginning element of the current subarray.
//            ·) end, the last element of the current subarray.
//            ·) x, the element to count its ocurrences.
// Output:    ·) int, number of ocurrences in the subarray.
int numOccurrences(const vector<int> &v, int start, int end, int x)
{
    int firstIndex = firstOccurrence(v, start, end, x);

    if (firstIndex == -1)
        return 0;

    int lastIndex = lastOccurrence(v, start, end, x);

    return lastIndex - firstIndex + 1;
}

int numOccurrences(const vector<int> &v, int x)
{
    if (v.empty())
        return 0;
    return (numOccurrences(v, 0, v.size() - 1, x));
}

int main(int argc, char const *argv[])
{

    const vector<int> VECTOR = {0, 0, 1, 2, 3, 3, 3, 4};

    cout << "Vector: ";
    for (size_t i = 0; i < VECTOR.size(); ++i)
    {
        cout << VECTOR[i];
        if (i + 1 < VECTOR.size())
            cout << ", ";
    }
    cout << "\n";

    cout << "Element to count: ";
    int x;
    if (!(cin >> x))
    {
        cout << "Must introduce an integer!" << endl;
        return 1;
    }

    int count = numOccurrences(VECTOR, x);
    if (count > 0)
        cout << "--> " << x << " is " << count << " time" << (count == 1 ? "" : "s") << " in the vector" << endl;
    else
        cout << "--> " << x << " is NOT in the vector" << endl;

    return 0;
}