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
  Implementation of Prim's algorithm (Greedy) for the following graph problem:
  Find a Minimum Spanning Tree for the following graph using Prim's algorithm:

    A(0): B(7)  D(5)
    B(1): A(7)  C(8)  D(9)  E(9)
    C(2): B(8)  D(7)  E(5)  F(15)
    D(3): A(5)  B(9)  C(7)  F(6)
    E(4): B(9)  C(5)  F(8)
    F(5): C(15) D(6)  E(8)
*/

// SELECTION FUNCTION FOR THE CONNECTING EDGE WITH THE MINIMUM WEIGHT
// Input:     ·) visited_v, vector of vertices already selected in the tree;
//            ·) unvisited_v, vector of unvisited vertices;
//            ·) edges, vector of the problem's edges.
// Output:    ·) output, selected edge that connects the current tree
//               with an unvisited vertex.
tuple<int, char, char>
select_edge(const vector<char> &visited_v,
                 const vector<char> &unvisited_v,
                 const vector<tuple<int, char, char>> &edges) {

  int min_weight = INT_MAX;
  tuple<int, char, char> selected_edge;

  for (tuple<int, char, char> edge : edges) {

    bool connect1 = ((find(visited_v.begin(), visited_v.end(),
                            get<1>(edge)) != visited_v.end()) &&
                      (find(unvisited_v.begin(), unvisited_v.end(),
                            get<2>(edge)) != unvisited_v.end()));
    bool connect2 = ((find(visited_v.begin(), visited_v.end(),
                            get<2>(edge)) != visited_v.end()) &&
                      (find(unvisited_v.begin(), unvisited_v.end(),
                            get<1>(edge)) != unvisited_v.end()));

    // if one vertex is in the tree and the other is unvisited, check its weight.
    if (connect1 || connect2) {
      if (get<0>(edge) < min_weight) {
        min_weight = get<0>(edge);
        selected_edge = edge;
      }
    }
  }

  return (selected_edge);
}

// FUNCTION TO UPDATE THE SETS OF VISITED AND UNVISITED VERTICES
// Input:     ·) visited_v, vector of already selected vertices;
//            ·) unvisited_v, vector of unvisited vertices;
//            ·) selected_edge, edge that connects both sets.
void update_vertices(vector<char> &visited_v,
                         vector<char> &unvisited_v,
                         tuple<int, char, char> selected_edge) {

  // if the first vertex of the edge has already been visited.
  if (find(visited_v.begin(), visited_v.end(),
           get<1>(selected_edge)) != visited_v.end()) {

    // push the second vertex to the visited vector.
    visited_v.push_back(get<2>(selected_edge));

    // erase the second vertex from the unvisited vector.
    unvisited_v.erase(find(unvisited_v.begin(), unvisited_v.end(),
                              get<2>(selected_edge)));
  } else { // if the second vertex of the edge has already been visited.

    // push the first vertex to the visited vector.
    visited_v.push_back(get<1>(selected_edge));

    // erase the first vertex from the unvisited vector.
    unvisited_v.erase(find(unvisited_v.begin(), unvisited_v.end(),
                              get<1>(selected_edge)));
  }
}

// PRIM ALGORITHM
// Idea:      choose the lowest weight edge that connects the constructed tree 
//            to an external vertex.
// Input:     ·) edges, vector of the graph's edges;
//            ·) n_vertices, number of vertices in the graph.
// Output:    ·) total_cost, cost of the calculated minimum spanning tree;
//            ·) min_cost_edges, set of edges forming the problem solution.
pair<int, vector<tuple<int, char, char>>>
prim_algorithm(vector<tuple<int, char, char>> edges, int n_vertices) {

  int total_cost = 0;
  vector<tuple<int, char, char>> min_cost_edges;

  // Step 1: Sort by weight.
  sort(edges.begin(), edges.end());

  // Step 2: Select starting vertex.
  char vertex_0 = get<1>(edges[0]);

  vector<char> visited_v;
  visited_v.push_back(vertex_0);

  vector<char> unvisited_v; // Vector of unvisited vertices.
  for (tuple<int, char, char> edge : edges) {
    if ((get<1>(edge) != vertex_0) &&
        (find(unvisited_v.begin(), unvisited_v.end(), get<1>(edge)) ==
         unvisited_v.end())) {
      unvisited_v.push_back(get<1>(edge));
    }
    if ((get<2>(edge) != vertex_0) &&
        (find(unvisited_v.begin(), unvisited_v.end(), get<2>(edge)) ==
         unvisited_v.end())) {
      unvisited_v.push_back(get<2>(edge));
    }
  }

  // Step 3: Add the next lightest edge if it connects the tree 
  //         to an external vertex, until |min_cost_edges| = |vertices| - 1.
  tuple<int, char, char> selected_edge;

  while (min_cost_edges.size() < (size_t)(n_vertices - 1)) {

    // select connecting edge with minimum weight.
    selected_edge = select_edge(visited_v, unvisited_v, edges);

    // add it to the solution.
    min_cost_edges.push_back(selected_edge);
    total_cost += get<0>(selected_edge);

    // update the sets of visited/unvisited vertices.
    update_vertices(visited_v, unvisited_v, selected_edge);
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
      prim_algorithm(EDGES, N_VERTICES);

  cout << "-> Total cost: " << to_string(result.first) << endl;
  cout << "-> Edges of the minimum spanning tree:" << endl;
  for (tuple<int, char, char> edge : result.second) {
    cout << "{" << to_string(get<0>(edge)) << " ," << get<1>(edge) << " ,"
         << get<2>(edge) << "}";
  }
  cout << endl;
}