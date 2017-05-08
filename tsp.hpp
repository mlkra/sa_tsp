#pragma once

extern double initialTemperature;
extern double endTemperature;
extern float alpha1;
extern float alpha2;
extern int bigJump;
extern int ITERATIONS;

void loadCities();
void initializeSearch();
void setupHandler();
void search();
