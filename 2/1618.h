#pragma once

enum SHAPETYPE
{
	Sphere = 1,
	Cube = 2,
	Cone = 3,
	Teapot = 4
};

//
void SetupRC();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void DrawSolidShape();
void DrawWireShape();

void AllRotation();
void LRotation();
void RRotation();

//
SHAPETYPE shapetype;
int type;

float AllrotX, AllrotY, AllrotZ;
float LrotX, LrotY, LrotZ;
float RrotX, RrotY, RrotZ;

double zoom;
float CameraRot;