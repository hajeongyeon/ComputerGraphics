#pragma once

#define PI 3.141592

//
void SetupRC();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char, int, int);
void TimerFunction(int);

int yRot;
float zoom;


// 19
void XRoll();
void YRoll();
void ZRoll();

double radius;
double MoveX, MoveY, MoveZ;

double sRotx, sRoty, sRotz;


// 20
void BottomBody();
void MiddleBody();
void TopBody();

float BMoveX, BRoty;
float MRotx, MRoty;
float TRotx, TRotz;
int dir;