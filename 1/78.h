#pragma once

#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

typedef struct {
	int x, y;
	double rad;
	double SaveRad;
	int check;
	int degree;
	double tmpX, tmpY;
} Shape;

float R = 0.5f;
float G = 1.0f;
float B = 1.0f;