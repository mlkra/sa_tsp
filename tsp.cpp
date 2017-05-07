#include "tsp.hpp"

#include "cities.hpp"
#include "solution.hpp"

#include <iostream>
#include <csignal>
#include <cstring>
#include <cmath>

using namespace std;

double initialTemperature;
double endTemperature;
float alpha1 = 0.65;
float alpha2 = 0.85;
int bigJump = 1000;
int ITERATIONS = 100000000;

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

inline double getInitialTemperature(double min) {
  solution_t solution;
  solution = createSimpleSolution();
  double max = solution.value;
  delete[] solution.order;
  for (int i = 0; i < 50; i ++) {
    solution = createRandomSolution();
    if (max < solution.value) {
      max = solution.value;
    }
    delete[] solution.order;
  }
  return max - min;
}

void initializeSearch() {
  loadCities();
  // theBestSolution = createSimpleSolution();
  // theBestSolution = createGreedySolution();
  theBestSolution = createNEHSolution();

  // TODO initial initialization, subject to changes
  // max temperature should be better
  initialTemperature = getInitialTemperature(theBestSolution.value) / 2;
  endTemperature = 0.01 * initialTemperature;

  srand(time(NULL));
}

void setupHandler() {
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
  float temperature = initialTemperature;

  int k = 0;
  while (k < ITERATIONS) {
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
        // temperature *= alpha1;
      } else {
        double delta = distance - currentSolution.value;
        float p = exp(-delta / temperature);
        if ((float) rand() / (1.0 * RAND_MAX) < p) {
          swap(&currentSolution, permutation);
          currentSolution.value = distance;
          // temperature *= alpha1;
        }
      }
      temperature *= alpha1;
      k++;
    }
    currentSolution.value = theBestSolution.value;
    memcpy(currentSolution.order, theBestSolution.order, (n + 1) * sizeof(int));
    temperature = initialTemperature;
  }
  printResult();
}
