#pragma once

#define M_E 2.718281828459

extern float maxTemperature;
extern float endTemperature;
extern float alpha1;
extern float alpha2;
extern int bigJump;

void initializeSearch();
void setupHandler();
void search();
