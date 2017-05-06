#include "tsp.hpp"

#include "cities.hpp"
#include "solution.hpp"

#include <iostream>
#include <csignal>
#include <cstring>
#include <cmath>

using namespace std;

float maxTemperature;
float endTemperature;
float alpha1 = 0.95;
float alpha2 = 0.85;
int bigJump = 1000;

solution_t theBestSolution;

void printResult() {
  // cout << calculateDistance(theBestSolution) << endl;
  for (int i = 0; i <= n; i++) {
    cerr << theBestSolution.order[i] + 1 << " ";
  }
  cerr << endl;
  cout << calculateDistance(theBestSolution) << endl;
  delete[] theBestSolution.order;
}

void handler(int signum) {
  printResult();
  exit(0);
}

void initializeSearch() {
  loadCities();
  // theBestSolution = createSimpleSolution();
  // theBestSolution = createGreedySolution();
  theBestSolution = createNEHSolution();

  // TODO initial initialization, subject to changes
  // max temperature should be better
  maxTemperature = theBestSolution.value;
  endTemperature = 0.01 * maxTemperature;

  srand(time(NULL));
  struct sigaction act;
  act.sa_handler = handler;
  sigaction(SIGINT, &act, NULL);
}

inline permutation_t generatePermutation() {
  int a = rand() % (n - 1) + 1;
  int b = rand() % (n - 1) + 1;
  while (a == b) {
    b = rand() % (n - 1) + 1;
  }
  permutation_t permutation;
  if (a > b) {
    permutation.a = b;
    permutation.b = a;
  } else {
    permutation.a = a;
    permutation.b = b;
  }
  return permutation;
}

void search() {
  solution_t currentSolution;
  currentSolution.order = new int[n+1];
  currentSolution.value = theBestSolution.value;
  memcpy(currentSolution.order, theBestSolution.order, (n + 1) * sizeof(int));
  float temperature = maxTemperature;

  while (temperature > endTemperature) {
    permutation_t permutation = generatePermutation();
    double distance = calculateNeighbourDistance(currentSolution, permutation);
    if (currentSolution.value < distance) {
      swap(&currentSolution, permutation);
      currentSolution.value = distance;
      if (currentSolution.value < theBestSolution.value) {
        theBestSolution.value = currentSolution.value;
        memcpy(theBestSolution.order, currentSolution.order, (n + 1) * sizeof(int));
      }
      temperature = temperature * alpha1;
    } else {
      double delta = distance - currentSolution.value;
      float p = exp(-delta / temperature);
      if ((float) rand() / (1.0 * RAND_MAX) < p) {
        swap(&currentSolution, permutation);
        currentSolution.value = distance;
        temperature = temperature * alpha1;
      }
    }
  }
  printResult();
}
