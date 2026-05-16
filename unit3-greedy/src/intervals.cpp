#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/*
  Implementation of a Greedy algorithm for the following problem:
  Given n points x1 < · · · < xn and a length L > 0, cover all points 
  with the minimum number of intervals [a, a + L].

  When applying a greedy algorithm, it may not compute the globally optimal solution, 
  but it does compute the local optimal solution efficiently.
*/

// CANDIDATE UPDATE FUNCTION
// Input:     ·) interval, the interval on which the removed points depend;
//            ·) points, vector of points to be covered.
// Output:    ·) removed_points_count, total count of points covered by the interval.

int remove_covered_points(pair<int, int> interval, vector<int> &points) {

  auto it = points.begin();
  int removed_points_count = 0;

  while (it != points.end()) {
    if (interval.first <= *it && *it <= interval.second) {
      it = points.erase(it);
      ++removed_points_count;
    } else
      ++it;
  }

  return removed_points_count;
}

// GREEDY ALGORITHM
// Idea:      choose the interval that starts at the next uncovered point.
// Input:     ·) interval_length, length of the covering intervals;
//            ·) points, vector of points to be covered;
// PRE:       the vector of points is sorted in ascending order.
// Output:    ·) n_intervals, minimum number of intervals required to cover all points;
//            ·) sol_intervals, vector containing the required intervals.

pair<int, vector<pair<int, int>>> greedy_intervals(int interval_length,
                                                    const vector<int> &points) {

  // If the vector were not sorted, it would be sorted here. -> O(n logn)

  // solution vector
  vector<pair<int, int>> sol_intervals;

  // minimum number of required intervals
  int n_intervals = 0;

  // copy of the points vector, from which covered points will be removed.
  vector<int> remaining_points = points;

  // element selected as the local optimal solution
  pair<int, int> interval;
  int interval_start;

  while (!remaining_points.empty()) {

    // select the interval
    interval_start = remaining_points[0];
    interval = {interval_start, interval_start + interval_length};

    // remove points covered by this interval
    remove_covered_points(interval, remaining_points);

    // add local solution to the solutions vector
    sol_intervals.push_back(interval);

    // update interval count
    ++n_intervals;
  }

  return {n_intervals, sol_intervals};
}

int main() {
  const int INTERVAL_LENGTH = 4;
  const vector<int> &POINTS = {1, 3, 4, 7, 9, 11, 13, 15};

  pair<int, vector<pair<int, int>>> solutions =
      greedy_intervals(INTERVAL_LENGTH, POINTS);

  cout << "-> Minimum number of required intervals: " << solutions.first
       << endl;
  cout << "-> Intervals: " << endl;
  for (pair<int, int> interval : solutions.second) {
    cout << "[" << to_string(interval.first) << ", "
         << to_string(interval.second) << "]" << endl;
  }

  return 0;
}