#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

/*
  Implementation of Dijkstra's algorithm (Greedy) for the following graph problem:
  Find a Minimum Spanning Tree for the following directed weighted graph
  using Dijkstra's algorithm:

    // DIRECTED GRAPH:
    //
    //  Node  Connections (destination, weight)
    //  ----  ---------------------------------
    //  s(0): a(2)  b(5)
    //  a(1): c(3)  b(8)  t(10)
    //  b(2): d(2)
    //  c(3): t(1)  d(4)
    //  d(4): t(6)
    //  t(5): -

  In this case, it is difficult to extract the exact edges of the solution because the algorithm
  chooses the best vertex according to the selection function. Therefore, the algorithm's
  function only returns the order in which the vertices were selected.
*/

// SELECTION FUNCTION FOR THE VERTEX WITH THE MINIMUM TENTATIVE DISTANCE
// Input:     ·) unvisited_v, vector of unvisited vertices;
//            ·) D, map containing the tentative distances of each vertex.
// Output:    ·) output, vertex with the minimum tentative distance.
char select_vertex(const vector<char> &unvisited_v, map<char, int> D) {

  char output;
  int min_dist = INT_MAX;

  for (char vertex : unvisited_v) {

    int value = D[vertex];
    if (value < min_dist) {
      output = vertex;
      min_dist = value;
    }
  }
  return output;
}

// FUNCTION TO UPDATE THE SETS OF VISITED AND UNVISITED VERTICES
// Input:     ·) visited_v, vector of already selected vertices;
//            ·) unvisited_v, vector of unvisited vertices;
//            ·) selected_vertex, vertex that needs to be updated.
void update_vertices(vector<char> &visited_v,
                         vector<char> &unvisited_v,
                         char selected_vertex) {

  visited_v.push_back(selected_vertex);
  unvisited_v.erase(
      find(unvisited_v.begin(), unvisited_v.end(), selected_vertex));
}

// FUNCTION TO UPDATE THE TENTATIVE DISTANCES OF DIRECTED NEIGHBORS
// Input:     ·) edges, vector of the graph's edges;
//            ·) D, map containing the tentative distances of each vertex;
//            ·) selected_vertex, neighbor source of the vertices whose 
//               distances need to be updated.
void update_distances(const vector<tuple<int, char, char>> &edges,
                           char selected_vertex, map<char, int> &D) {

  for (tuple<char, int, int> edge : edges) {

    // find neighbor vertex directed from the selected one.
    if (get<1>(edge) == selected_vertex) {

      char neighbor = get<2>(edge);
      int neighbor_distance = get<0>(edge);

      if (D[selected_vertex] + neighbor_distance < D[neighbor])
        D[neighbor] = D[selected_vertex] + neighbor_distance;
    }
  }
}

// DIJKSTRA ALGORITHM
// Idea:      choose the vertex with the lowest tentative distance from the source.
// Input:     ·) edges, vector of the graph's edges;
//            ·) initial_vertex, starting vertex for Dijkstra's algorithm;
//            ·) vertices, vertices of the problem.
// Output:    ·) ordered list of vertices as they are visited.
vector<char> dijkstra_algorithm(const vector<tuple<int, char, char>> &edges,
                      char initial_vertex, const vector<char> &vertices) {

  vector<char> visited_v;

  // tentative distance map.
  map<char, int> D;
  D[initial_vertex] = 0;
  for (char vertex : vertices) {
    if (vertex != initial_vertex)
      D[vertex] = INT_MAX;
  }

  // loop to add the selected vertex until all vertices are visited.
  vector<char> unvisited_v = vertices;
  char selected_vertex;

  while (visited_v.size() < vertices.size()) {

    // select vertex with minimum tentative distance.
    selected_vertex = select_vertex(unvisited_v, D);

    // update the vectors of visited and unvisited vertices.
    update_vertices(visited_v, unvisited_v, selected_vertex);

    // update tentative distances of the neighbors.
    update_distances(edges, selected_vertex, D);
  }

  return {visited_v};
}

int main() {

  // {weight, origin, destination}
  vector<tuple<int, char, char>> EDGES = {
      {2, 's', 'a'},  // s->a
      {5, 's', 'b'},  // s->b
      {3, 'a', 'c'},  // a->c
      {8, 'a', 'b'},  // a->b
      {10, 'a', 't'}, // a->t
      {2, 'b', 'd'},  // b->d
      {1, 'c', 't'},  // c->t
      {4, 'c', 'd'},  // c->d
      {6, 'd', 't'},  // d->t
  };

  const vector<char> &vertices = {'s', 'a', 'b', 'c', 'd', 't'};
  const char INITIAL_VERTEX = 's';

  vector<char> result = dijkstra_algorithm(EDGES, INITIAL_VERTEX, vertices);

  cout << "Selected vertices (in order): {" << result[0];

  for (size_t i = 1; i < result.size(); ++i) {
    cout << ", " << result[i];
  }
  cout << "}" << endl;
}