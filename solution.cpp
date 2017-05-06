#include "solution.hpp"

#include "cities.hpp"

#include <cstring>
#include <cfloat>

solution_t createSimpleSolution() {
  solution_t solution;
  double value = 0;
  int *order = new int[n+1];
  order[0] = 0;
  for (int i = 1; i < n; i++) {
    order[i] = i;
    value += getDistance(order[i-1], order[i]);
  }
  order[n] = 0;
  value += getDistance(order[n-1], order[n]);

  solution.order = order;
  solution.value = value;
  return solution;
}

double calculateDistance(solution_t solution) {
  double distance = 0;
  for (int i = 1; i <= n; i++) {
    distance += getDistance(solution.order[i-1], solution.order[i]);
  }
  return distance;
}

double calculateNeighbourDistance(solution_t solution, permutation_t permutation) {
  double distance = solution.value;
  distance -= getDistance(solution.order[permutation.a-1], solution.order[permutation.a]);
  distance -= getDistance(solution.order[permutation.b], solution.order[permutation.b+1]);
  distance += getDistance(solution.order[permutation.a-1], solution.order[permutation.b]);
  distance += getDistance(solution.order[permutation.a], solution.order[permutation.b+1]);
  return distance;
}

void swap(solution_t *solution, permutation_t permutation) {
  int length = (permutation.b - permutation.a + 1) / 2;
  for (int i = 0; i < length; i++) {
    int temp = solution->order[permutation.a+i];
    solution->order[permutation.a+i] = solution->order[permutation.b-i];
    solution->order[permutation.b-i] = temp;
  }
}
