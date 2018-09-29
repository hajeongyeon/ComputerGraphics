#pragma once

#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

enum ShapeType
{
	RECTANGLE = 0,
	TRIANGLE = 1
};

typedef struct {
	int x, y;
	int width, length;
	int shapeSize;
	int xdir, ydir;
	int speed;
	bool isRot = false;
	bool stop = false;
	bool allstop = false;
	ShapeType type;

	int ForR;
	int xRot = 1;
	int yRot = 1;
	int SaveX, SaveY;
	bool rot = false;
} Shape;

float R = 0.0f;
float G = 1.0f;
float B = 1.0f;

int MoveX = 30;
int MoveY = 30;