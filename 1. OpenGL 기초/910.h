#pragma once

#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

enum ShapeType
{
	RECTANGLE = 0,
	TRAPEZOID = 1,
	TRIANGLE = 2
};

typedef struct {
	float R = 0.0f;
	float G = 1.0f;
	float B = 1.0f;
	
	int x, y;
	int shapeSize;
	int xdir, ydir;
	int trape_time, tri_time;
	ShapeType type;
} Shape;

int currX, currY;
bool left_button;