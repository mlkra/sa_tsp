#pragma once

typedef struct {
  int label;
  double x;
  double y;
} city_t;

extern short n;
extern city_t* cities;
extern float maxDistance;

void loadCities();
void calculateDistances();
float getDistance(int c1, int c2);
