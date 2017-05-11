#pragma once

extern double initialTemperature;
extern int divisor;
extern float alpha1;
extern int ITERATIONS;

void loadCities();
void initializeSearch();
void setupHandler();
void search();
