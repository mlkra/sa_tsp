#include "tsp.hpp"

#include "cities.hpp"
#include "solution.hpp"

#include <iostream>
#include <csignal>
#include <cstring>
#include <cmath>
#include <cstdlib>

using namespace std;

int ITERATIONS = 10000000;

solution_t theBestSolution;

void printResult() {
  // cout << calculateDistance(theBestSolution) << endl;
  for (int i = 0; i <= n; i++) {
    cerr << theBestSolution.order[i] + 1 << " ";
  }
  cerr << endl;
  cout << calculateDistance2(theBestSolution) << endl;
  delete[] theBestSolution.order;
}

void handler(int signum) {
  printResult();
  exit(0);
}

void initializeSearch() {
  calculateDistances();
  theBestSolution = createNEHSolution();
  cout << theBestSolution.value << endl;
  cout << calculateDistance2(theBestSolution) << endl;

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
  int k = 0;
  while (k < ITERATIONS) {
      permutation_t permutation = generatePermutation();
      double distance = calculateNeighbourDistance(theBestSolution, permutation);
      if (theBestSolution.value > distance) {
        swap(&theBestSolution, permutation);
        theBestSolution.value = distance;
        cout << theBestSolution.value << endl;
      }
      k++;
  }
  printResult();
}
