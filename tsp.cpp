#include "tsp.hpp"

#include "cities.hpp"
#include "solution.hpp"

#include <iostream>
#include <csignal>
#include <cstring>
#include <cmath>

using namespace std;

int ITERATIONS = 1000000000;

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
  calculateDistances();
  theBestSolution = createNEHSolution();

  cout << theBestSolution.value;

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

  int k = 0;
  while (k < ITERATIONS) {
      permutation_t permutation = generatePermutation();
      double distance = calculateNeighbourDistance(currentSolution, permutation);
      if (currentSolution.value < distance) {
        swap(&currentSolution, permutation);
        currentSolution.value = distance;
        if (currentSolution.value < theBestSolution.value) {
          theBestSolution.value = currentSolution.value;
          memcpy(theBestSolution.order, currentSolution.order, (n + 1) * sizeof(int));
        }
      }
      k++;
  }
  printResult();
}
