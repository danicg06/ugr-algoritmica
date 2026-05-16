#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/*
  Implementation of a Greedy algorithm for the following problem:
  A vehicle starts at kilometer 0 heading towards kilometer D, with a full tank and
  a maximum range of C km. There are n gas stations at positions p1 < · · · < pn.
  Objective: minimize the number of refueling stops.

  When applying a greedy algorithm, it may not compute the globally optimal solution, 
  but it does compute the local optimal solution efficiently.
*/

// SELECTION FUNCTION FOR LOCAL OPTIMAL SOLUTION
// Input:     ·) range_end_km, the kilometer reachable without refueling;
//            ·) gas_stations_km, vector of kilometers where the gas stations are located;
//            ·) n_gas_stations, number of gas stations in the vector.
// PRE:       the vector of kilometers where the gas stations are located 
//            is sorted in ascending order.
// Output:    position of the optimal gas station in the vector:
//            ·) -1 if there is no gas station we can reach.
//            ·) the position of the optimal gas station in the vector.
int optimal_station_pos(int range_end_km,
                          const vector<int> &gas_stations_km,
                          int n_gas_stations) {
  bool is_feasible = true;
  int i = -1;

  while (i + 1 < n_gas_stations && is_feasible) {

    if (gas_stations_km[i + 1] > range_end_km)
      is_feasible = false;
    else
      i++;
  }

  return (i);
}

// GREEDY ALGORITHM
// Idea:      choose the gas station that is as far away as possible
//            without exceeding the vehicle's remaining range.
// Input:     ·) final_km, target kilometer to reach;
//            ·) range_km, kilometers the vehicle can travel without refueling;
//            ·) gas_stations_km, vector of kilometers where the gas stations are located;
//            ·) n_gas_stations, number of gas stations in the vector.
// Hypothesis: the initial kilometer is 0, with a full tank.
// PRE:       the vector of kilometers where the gas stations are located 
//            is sorted in ascending order.
// Output:    ·) reached_km, the kilometer reached with the given gas stations;
//            ·) sol_gas_stations_km, vector containing the solution gas stations.

pair<int, vector<int>> greedy_fuel(int final_km, int range_km,
                                          const vector<int> &gas_stations_km,
                                          int n_gas_stations) {

  // If the vector were not sorted, it would be sorted here. -> O(n logn)

  // solution vector
  vector<int> sol_gas_stations_km;

  // kilometer where we refueled for the last time.
  int last_refuel_km = 0;

  // copy the gas stations kilometers vector.
  vector<int> gas_km = gas_stations_km;

  // stores the maximum kilometer reachable after refueling at a gas station
  int range_end_km = range_km;

  // boolean indicating if any gas station is reachable or if there are no more
  // gas stations left to refuel.
  bool station_reachable = true;

  // we achieve the solution once the remaining range is greater than or equal to
  // the final destination kilometer.
  while (range_end_km < final_km && station_reachable) {

    // calculate the position of the optimal gas station in the vector.
    int refuel_pos_km =
        optimal_station_pos(range_end_km, gas_km, n_gas_stations);

    // check if there is any reachable gas station.
    station_reachable = (refuel_pos_km != -1);
    if (station_reachable) {

      // choose optimal gas station
      last_refuel_km = gas_km[refuel_pos_km];

      // add the gas station to the solution
      sol_gas_stations_km.push_back(last_refuel_km);

      // remove the added gas station and all previous ones from the vector.
      for (int j = 0; j <= refuel_pos_km; j++) {
        vector<int>::const_iterator it = gas_km.begin();
        it = gas_km.erase(it);
      }

      range_end_km = last_refuel_km + range_km;
    }
  }

  // final kilometer reached.
  int reached_km = range_end_km;
  if (reached_km > final_km)
    reached_km = final_km;

  return {reached_km, sol_gas_stations_km};
}

int main() {
  const int FINAL_KM = 25;
  const int RANGE_KM = 10;
  const vector<int> &GAS_STATIONS_KM = {3, 6, 11, 14, 18, 22};

  pair<int, vector<int>> solutions = greedy_fuel(
      FINAL_KM, RANGE_KM, GAS_STATIONS_KM, GAS_STATIONS_KM.size());

  cout << "-> Kilometer reached: " << solutions.first << endl;
  cout << "-> Gas stations used for refueling: " << endl;
  for (int station : solutions.second) {
    cout << to_string(station) << endl;
  }

  return 0;
}