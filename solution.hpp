#pragma once

typedef struct {
  double value;
  int *order;
} solution_t;

typedef struct {
  int a, b;
} permutation_t;

solution_t createSimpleSolution();
double calculateDistance(solution_t solution);
double calculateNeighbourDistance(solution_t solution, permutation_t permutation);
void swap(solution_t *solution, permutation_t permutation);
