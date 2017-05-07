#pragma once

#define M_E 2.718281828459

extern double initialTemperature;
extern double endTemperature;
extern float alpha1;
extern float alpha2;
extern int bigJump;
extern int ITERATIONS;

void initializeSearch();
void setupHandler();
void search();
