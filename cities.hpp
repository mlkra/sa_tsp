#pragma once

typedef struct {
  int label;
  float x;
  float y;
} city_t;

extern short n;
extern float maxDistance;

void loadCities();
void calculateDistances();
float getDistance(int c1, int c2);
