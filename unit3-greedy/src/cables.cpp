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
  Implementation of a Greedy algorithm for the following problem:
  There are n cables of lengths l1, . . . , ln. Merging two cables of 
  lengths a and b costs a + b and yields a cable of length a + b.
  Objective: merge all cables into a single one with the minimum total cost.

  When applying a greedy algorithm, it may not compute the globally optimal solution, 
  but it does compute the local optimal solution efficiently.
*/

// GREEDY ALGORITHM
// Idea:      merge the two cables with the shortest length.
// Input:     ·) cable_lengths, vector of pairs with the cable ID and its respective length.
// Output:    ·) total_cost, total cost of merging the solution cables;
//            ·) merged_cables, vector containing the pairs of cables merged in order.
//            ·) cables_post_merge, vector showing cables and their lengths after each merge.
//            ·) merge_costs, vector with the costs of each individual merge.

pair<int, tuple<vector<pair<float, float>>, vector<vector<pair<float, int>>>,
                vector<int>>>
greedy_cables(const vector<pair<float, int>> &cable_lengths) {

  // copy of the cables vector, from which we will remove merged cables and add the results.
  vector<pair<float, int>> sol_cable_lengths = cable_lengths;

  // sort the copy vector to easily find the two cables with the shortest length.
  sort(sol_cable_lengths.begin(), sol_cable_lengths.end(),
       [](const pair<float, int> &a, const pair<float, int> &b) {
         return a.second < b.second;
       });

  // outputs.
  int total_cost = 0;
  vector<pair<float, float>> merged_cables;
  vector<vector<pair<float, int>>>
      cables_post_merge; // represented as: merge of 1 and 2 -> 1,2
  vector<int> merge_costs;

  // cables to merge along with their lengths.
  pair<float, int> cable_1;
  pair<float, int> cable_2;
  int merge_length;
  float merged_cable_id;

  while (sol_cable_lengths.size() != 1) {

    cable_1 = sol_cable_lengths[0];
    cable_2 = sol_cable_lengths[1];
    merge_length = (cable_1.second + cable_2.second);

    // add merged cables and their cost to outputs.
    merged_cables.push_back({cable_1.first, cable_2.first});
    merge_costs.push_back(merge_length);
    total_cost += merge_length;

    // remove the two merged cables.
    sol_cable_lengths.erase(sol_cable_lengths.begin(),
                                sol_cable_lengths.begin() + 2);

    merged_cable_id = cable_1.first + cable_2.first / (float)10;

    sol_cable_lengths.push_back({merged_cable_id, merge_length});

    // re-sort the vector to keep the shortest cables at the beginning.
    sort(sol_cable_lengths.begin(), sol_cable_lengths.end(),
         [](const pair<int, int> &a, const pair<int, int> &b) {
           return a.second < b.second;
         });

    // add the vector state after this merge step.
    cables_post_merge.push_back(sol_cable_lengths);
  }

  tuple<vector<pair<float, float>>, vector<vector<pair<float, int>>>,
        vector<int>>
      outputs = {merged_cables, cables_post_merge, merge_costs};

  return {total_cost, outputs};
}

int main() {

  const vector<pair<float, int>> &CABLES = {
      {2, 3}, {4, 6}, {1, 2}, {3, 4}, {1, 8}};

  pair<int, tuple<vector<pair<float, float>>, vector<vector<pair<float, int>>>,
                  vector<int>>>
      result = greedy_cables(CABLES);

  cout << "-> Total cost: " << result.first << endl;
  cout << "-> Initial cables: " << endl;
  cout << "Cables:     ";
  for (pair<float, int> cable : CABLES)
    cout << fixed << setprecision(4) << cable.first << " ";
  cout << endl;
  cout << "Lengths:    ";
  for (pair<float, int> cable : CABLES)
    cout << to_string(cable.second) + "      ";
  cout << endl << endl;

  cout << "--> Merges: " << endl;
  for (int i = 0; i < get<2>(result.second).size(); i++) {
    cout << "------(" + to_string(i) + ")------" << endl;
    cout << "<" << fixed << setprecision(4) << get<0>(result.second)[i].first
         << ", " << get<0>(result.second)[i].second << ">"
         << ", cost: " << to_string(get<2>(result.second)[i]) << endl;
    cout << "Cables:     ";
    for (pair<float, int> cable : get<1>(result.second)[i])
      cout << fixed << setprecision(4) << cable.first << " ";
    cout << endl;
    cout << "Lengths:    ";
    for (pair<float, int> cable : get<1>(result.second)[i])
      cout << to_string(cable.second) + "      ";
    cout << endl;
  }

  return 0;
}