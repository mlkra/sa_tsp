#include "solution.hpp"

#include "cities.hpp"

#include <cstring>
#include <cfloat>
#include <cmath>
#include <iostream>

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

solution_t createRandomSolution() {
  solution_t solution;
  int *order = new int[n+1];
  for (int i = 0; i < n; i++) {
    order[i] = i;
  }
  order[n] = 0;

  for (int i = 0; i < n*log(n); i++) {
    int a = rand() % (n - 1) + 1;
    int b = rand() % (n - 1) + 1;
    int temp = order[a];
    order[a] = order[b];
    order[b] = temp;
  }

  solution.order = order;
  solution.value = calculateDistance(solution);

  return solution;
}

solution_t createGreedySolution() {
  solution_t solution;
  double value = 0;
  int *order = new int[n + 1];
  bool *avalible = new bool[n];
  memset(avalible, true, n*sizeof(bool));
  order[0] = 0;
  order[n] = 0;
  avalible[0] = false;
  int minPos;
  double min;
  for (int i = 1; i < n; i++) {
    min = FLT_MAX;
    for (int j = 1; j < n; j++) {
      if (avalible[j]) {
        float temp = getDistance(order[i-1], j);
        if (temp < min) {
          minPos = j;
          min = temp;
        }
      }
    }
    avalible[minPos] = false;
    order[i] = minPos;
    value += min;
  }
  value += getDistance(order[n], order[n-1]);

  delete[] avalible;
  solution.order = order;
  solution.value = value;
  return solution;
}

solution_t createNEHSolution() {
  solution_t solution;
  double value = 0;
  int *order = new int[n + 1];
  memset(order, -1, (n + 1) * sizeof(int));
  order[0] = 0; order[1] = 1; order[2] = 0;
  value += getDistance(0, 1) * 2;

  for (int i = 2; i < n; i++) {
    double min = FLT_MAX;
    int minPos;
    for (int j = 1; j <= i; j++) {
      double distance = getDistance(order[j-1], i) + getDistance(i, order[j]) - getDistance(order[j-1], order[j]);
      if (distance < min) {
        min = distance;
        minPos = j;
      }
    }
    for (int j = n; j > minPos; j--) {
      order[j] = order[j-1];
    }
    order[minPos] = i;
    value += min;
  }

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

double calculateDistance2(solution_t solution) {
  double distance = 0;
  for (int i = 1; i <= n; i++) {
    city_t c1 = cities[solution.order[i-1]];
    city_t c2 = cities[solution.order[i]];
    double x = c1.x - c2.x;
    double y = c1.y - c2.y;
    distance += sqrt((x*x) + (y*y));
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
