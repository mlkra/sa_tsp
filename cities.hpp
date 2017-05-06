#pragma once

typedef struct {
  int label;
  float x;
  float y;
} city_t;

extern short n;

void loadCities();
float getDistance(int c1, int c2);
