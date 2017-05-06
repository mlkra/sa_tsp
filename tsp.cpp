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
float alpha1;
float alpha2;
int bigJump;

solution_t theBestSolution;

void printResult() {
  cout << calculateDistance(theBestSolution) << endl;
  for (int i = 0; i <= n; i++) {
    cerr << theBestSolution.order[i] + 1 << " ";
  }
  cerr << endl;
  delete[] theBestSolution.order;
  //exit(0);
}

void handler(int signum) {
  printResult();
}

void initializeSearch() {
  loadCities();
  // theBestSolution = createSimpleSolution();
  theBestSolution = createGreedySolution();

  // TODO initial initialization, subject to changes
  maxTemperature = theBestSolution.value;
  endTemperature = 0.01 * maxTemperature;
  alpha1 = 0.01;
  alpha2 = 0.15;
  bigJump = 1000;

  srand(time(NULL));
  struct sigaction act;
  act.sa_handler = handler;
  sigaction(SIGINT, &act, NULL);
}

void search() {
  solution_t currentSolution;
  currentSolution.order = new int[n+1];
  currentSolution.value = theBestSolution.value;
  memcpy(currentSolution.order, theBestSolution.order, (n + 1) * sizeof(int));
  float temperature = maxTemperature;

  while (temperature > endTemperature) {
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
    double distance = calculateNeighbourDistance(currentSolution, permutation);
    if (currentSolution.value < distance) {
      swap(&currentSolution, permutation);
      currentSolution.value = distance;
      if (currentSolution.value < theBestSolution.value) {
        theBestSolution.value = currentSolution.value;
        memcpy(theBestSolution.order, currentSolution.order, (n + 1) * sizeof(int));
      }
      temperature = temperature * (1 - alpha1);
    } else {
      double delta = distance - currentSolution.value;
      float p = exp(-delta / temperature);
      // float p = 1.0 / (1.0 + exp(delta / temperature));
      if ((float) rand() / (1.0 * RAND_MAX) < p) {
        swap(&currentSolution, permutation);
        currentSolution.value = distance;
        temperature = temperature * (1 - alpha1);
      }
    }
  }
  printResult();
}
