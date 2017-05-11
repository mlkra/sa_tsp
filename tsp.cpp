#include "tsp.hpp"

#include "cities.hpp"
#include "solution.hpp"

#include <iostream>
#include <csignal>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <random>
#include <functional>
#include <ctime>
#include <cfloat>

using namespace std;

int ITERATIONS = 10000000;

double initialTemperature;
int divisor = 32;
float alpha1 = 0.9999999;

solution_t theBestSolution;

// potentially risky
// random_device rd;
// mt19937 generator(rd());
mt19937 generator(time(NULL));
uniform_real_distribution<double> disD(0.0, 1.0);
uniform_int_distribution<int> disI;

// TODO only for debug
double neh;

void printResult() {
  // TODO uncomment
  // cout << calculateDistance(theBestSolution) << endl;
  for (int i = 0; i <= n; i++) {
    cerr << theBestSolution.order[i] + 1 << " ";
  }
  cerr << endl;
  cout << calculateDistance(theBestSolution) << endl;
  // TODO only for debug
  cout << neh << endl;
  delete[] theBestSolution.order;
}

void handler(int signum) {
  printResult();
  exit(0);
}

void initializeSearch() {
  disI.param(uniform_int_distribution<>::param_type{1, n-1});
  calculateDistances();
  initialTemperature = maxDistance / divisor;
  theBestSolution = createNEHSolution();
  // TODO only for debug
  neh = theBestSolution.value;
}

void setupHandler() {
  struct sigaction act;
  act.sa_handler = handler;
  sigaction(SIGINT, &act, NULL);
}

inline permutation_t generatePermutation() {
  int a = disI(generator);
  int b = disI(generator);
  while (a == b) {
    b = disI(generator);
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
  auto doubleRand = bind(disD, generator);
  // int k = 0;
  // int wCounter = 0;
  solution_t currentSulution;
  currentSulution.order = new int[n+1];
  memcpy(currentSulution.order, theBestSolution.order, (n+1)*sizeof(int));
  currentSulution.value = theBestSolution.value;
  double temperature = initialTemperature;
  // while (k < ITERATIONS) {
    // memcpy(currentSulution.order, theBestSolution.order, (n+1)*sizeof(int));
    // currentSulution.value = theBestSolution.value;
    // temperature = initialTemperature;
    while (temperature > 1) {
      permutation_t permutation = generatePermutation();
      double distance = calculateNeighbourDistance(currentSulution, permutation);
      double delta = distance - currentSulution.value;
      if (delta < 0) {
        swap(&currentSulution, permutation);
        currentSulution.value = distance;
        if (currentSulution.value < theBestSolution.value) {
          // wCounter = 0;
          cout << currentSulution.value << endl;
          memcpy(theBestSolution.order, currentSulution.order, (n+1)*sizeof(int));
          theBestSolution.value = currentSulution.value;
        }
      } else if ((1 / (1 + exp(delta / temperature))) > doubleRand()) {
        // wCounter++;
        swap(&currentSulution, permutation);
        currentSulution.value = distance;
      }
      // if (wCounter > 20) {
      //   wCounter = 0;
      //   memcpy(currentSulution.order, theBestSolution.order, (n+1)*sizeof(int));
      //   currentSulution.value = theBestSolution.value;
      // }
      temperature *= alpha1;
      // k++;
    }
  // }
  delete[] currentSulution.order;
  printResult();
}
