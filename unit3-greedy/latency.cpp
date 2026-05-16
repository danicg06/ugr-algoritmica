#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/*
  Implementation of a Greedy algorithm for the following problem:
  There are n tasks with processing time pi and deadline di. All tasks must be executed 
  (one at a time).
  The latency of task i is Li = Ci − di (positive if delayed, negative if finished 
  before the deadline).
  Note that Ci is the completion time of that task, hence latency measures the deviation 
  relative to the deadline.
  Objective: minimize max {Li}.

  When applying a greedy algorithm, it may not compute the globally optimal solution, 
  but it does compute the local optimal solution efficiently.
*/

// GREEDY ALGORITHM
// Idea:      choose the task with the shortest deadline.
// Input:     ·) processing_deadline, vector of integer pairs: processing time and 
//               deadline of task i (position in the vector).
// Output:    ·) max_latency, maximum latency among all tasks;
//            ·) sol_processing_deadline, vector of pairs with processing time and 
//               deadline of the chosen tasks in order.
//            ·) completion_latency, vector of pairs with completion time and 
//               latency in the order tasks were chosen.

pair<int, pair<vector<pair<int, int>>, vector<pair<int, int>>>>
greedy_latency(const vector<pair<int, int>> &processing_deadline) {

  // sort a copy of the deadlines vector in ascending order with respect to deadlines.
  // This avoids a loop to search for the task with the shortest deadline in each iteration.
  vector<pair<int, int>> sol_processing_deadline = processing_deadline;
  sort(sol_processing_deadline.begin(), sol_processing_deadline.end(),
       [](const pair<int, int> &a, const pair<int, int> &b) {
         return a.second < b.second;
       });

  // vector containing the completion time and latency of each task.
  vector<pair<int, int>> completion_latency;
  int latency;

  int current_time = 0;

  // loop to calculate each completion time, latency, and find the maximum latency.
  int max_latency = INT_MIN;
  for (pair<int, int> p_deadline : sol_processing_deadline) {

    // calculate completion time and latency.
    current_time += p_deadline.first;
    latency = current_time - p_deadline.second;

    // add this completion time and latency to the respective vector.
    completion_latency.push_back({current_time, latency});

    if (latency > max_latency) {
      max_latency = latency;
    }
  }

  pair<int, pair<vector<pair<int, int>>, vector<pair<int, int>>>> result = {
      max_latency, {sol_processing_deadline, completion_latency}};

  return result;
}

int main() {

  const vector<pair<int, int>> &PROCESSING_DEADLINE = {
      {1, 3}, {2, 5}, {3, 8}, {2, 7}, {1, 4}};

  pair<int, pair<vector<pair<int, int>>, vector<pair<int, int>>>> result =
      greedy_latency(PROCESSING_DEADLINE);

  cout << "-> Maximum latency: " << result.first << endl;
  cout << "-> Processing time and deadline vector: " << endl;
  for (pair<int, int> p_deadline : result.second.first) {
    cout << "(" << to_string(p_deadline.first) << ", " << to_string(p_deadline.second)
         << ")" << endl;
  }
  cout << "-> Completion time and latency vector: " << endl;
  for (pair<int, int> comp_latency : result.second.second) {
    cout << "(" << to_string(comp_latency.first) << ", "
         << to_string(comp_latency.second) << ")" << endl;
  }

  return 0;
}