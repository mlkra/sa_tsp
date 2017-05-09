#include "tsp.hpp"

#include "cities.hpp"
#include "solution.hpp"

#include <iostream>
#include <csignal>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <random>
#include <ctime>

using namespace std;

int ITERATIONS = 1000000000;

solution_t theBestSolution;

// potentially risky
// random_device rd;
// mt19937 generator(rd());
mt19937 generator(time(NULL));
uniform_real_distribution<double> disD(0.0, 1.0);
uniform_int_distribution<int> disI;

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
  disI.param(uniform_int_distribution<>::param_type{1, n-1});
  calculateDistances();
  theBestSolution = createNEHSolution();
  // cout << calculateDistance(theBestSolution) << endl;

  srand(time(NULL));
}

void setupHandler() {
  struct sigaction act;
  act.sa_handler = handler;
  sigaction(SIGINT, &act, NULL);
}

inline permutation_t generatePermutation() {
  // int a = rand() % (n - 1) + 1;
  int a = disI(generator);
  // int b = rand() % (n - 1) + 1;
  int b = disI(generator);
  while (a == b) {
    // b = rand() % (n - 1) + 1;
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
  int k = 0;
  while (k < ITERATIONS) {
      permutation_t permutation = generatePermutation();
      double distance = calculateNeighbourDistance(theBestSolution, permutation);
      if (theBestSolution.value > distance) {
        swap(&theBestSolution, permutation);
        theBestSolution.value = distance;
        // TODO remove
        cout << theBestSolution.value << endl;
      }
      k++;
  }
  printResult();
}
