#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

/*
  Implementation of Kruskal's algorithm (Greedy) for the following graph problem:
  Find a Minimum Spanning Tree for the following graph using Kruskal's algorithm:

    A(0): B(7)  D(5)
    B(1): A(7)  C(8)  D(9)  E(9)
    C(2): B(8)  D(7)  E(5)  F(15)
    D(3): A(5)  B(9)  C(7)  F(6)
    E(4): B(9)  C(5)  F(8)
    F(5): C(15) D(6)  E(8)
*/

// DISJOINT SET MAKE SET FUNCTION
// Input:     ·) vertex, single element of the set to return.
// Output:    ·) output, single-element vector of the given vertex.
vector<char> make_set(char vertex) {

  vector<char> output;
  output.push_back(vertex);

  return output;
}

// DISJOINT SET FIND FUNCTION
// Input:     ·) vertex, vertex of the set of interest;
//            ·) sets_vertices, vector of vertex sets.
// Output:    ·) i, representative (position) of the set containing the given vertex.
int find_set(char vertex, const vector<vector<char>> &sets_vertices) {

  size_t i = 0;
  bool found = false;
  vector<char> current_set;

  while (i < sets_vertices.size() && !found) {

    current_set = sets_vertices[i];

    if (find(current_set.begin(), current_set.end(), vertex) != current_set.end())
      found = true;
    else
      i++;
  }

  return (i);
}

// DISJOINT SET UNION FUNCTION
// Input:     ·) vertex1, vertex of one of the sets to merge;
//            ·) vertex2, another vertex from a different set to merge;
//            ·) sets_vertices, vector of vertex sets.
void union_set(char vertex1, char vertex2, vector<vector<char>> &sets_vertices) {

  int rep_set1 = find_set(vertex1, sets_vertices);
  int rep_set2 = find_set(vertex2, sets_vertices);

  // Merge the corresponding sets of vertices
  sets_vertices[rep_set1].insert(
      sets_vertices[rep_set1].end(),
      sets_vertices[rep_set2].begin(),
      sets_vertices[rep_set2].end());

  sets_vertices.erase(sets_vertices.begin() + rep_set2);
}

// KRUSKAL ALGORITHM
// Idea:      choose the edge with the lowest weight and add it to the solution 
//            if it does not form a cycle.
// Input:     ·) edges, vector of the graph's edges;
//            ·) n_vertices, number of vertices in the graph.
// Output:    ·) total_cost, cost of the calculated minimum spanning tree;
//            ·) min_cost_edges, set of edges forming the problem solution.
pair<int, vector<tuple<int, char, char>>>
kruskal_algorithm(vector<tuple<int, char, char>> edges, int n_vertices) {

  int total_cost = 0;
  vector<tuple<int, char, char>> min_cost_edges;

  // Step 1: Sort edges by weight
  sort(edges.begin(), edges.end());

  // Step 2: Create a disjoint set for each vertex
  vector<vector<char>> sets_vertices;
  for (int i = 0; i < n_vertices; ++i) {
    sets_vertices.push_back(make_set((char)('A' + i)));
  }

  // Step 3: Add the next lightest edge if it doesn't form a cycle,
  //         until |min_cost_edges| = |vertices| - 1.
  tuple<int, char, char> selected_edge;
  size_t i = 0;

  while (min_cost_edges.size() < (size_t)(n_vertices - 1) && i < edges.size()) {

    selected_edge = edges[i];

    char vertex1 = get<1>(selected_edge);
    char vertex2 = get<2>(selected_edge);
    int rep_set1 = find_set(vertex1, sets_vertices);
    int rep_set2 = find_set(vertex2, sets_vertices);

    // If they are not in the same component, merge them.
    if (rep_set1 != rep_set2) {
      min_cost_edges.push_back(selected_edge);
      union_set(vertex1, vertex2, sets_vertices);
      total_cost += get<0>(selected_edge);
    }

    ++i;
  }

  return {total_cost, min_cost_edges};
}

int main() {

  // {weight, node1, node2}
  vector<tuple<int, char, char>> EDGES = {
      {5, 'A', 'D'},  // A-D
      {9, 'B', 'D'},  // B-D
      {5, 'C', 'E'},  // C-E
      {8, 'B', 'C'},  // B-C
      {6, 'D', 'F'},  // D-F
      {7, 'A', 'B'},  // A-B
      {15, 'C', 'F'}, // C-F
      {7, 'C', 'D'},  // C-D
      {8, 'E', 'F'},  // E-F
      {9, 'B', 'E'},  // B-E
  };

  const int N_VERTICES = 6;

  pair<int, vector<tuple<int, char, char>>> result =
      kruskal_algorithm(EDGES, N_VERTICES);

  cout << "-> Total cost: " << to_string(result.first) << endl;
  cout << "-> Edges of the minimum spanning tree:" << endl;
  for (tuple<int, char, char> edge : result.second) {
    cout << "{" << to_string(get<0>(edge)) << " ," << get<1>(edge) << " ,"
         << get<2>(edge) << "}";
  }
  cout << endl;
}