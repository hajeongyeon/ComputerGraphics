#pragma once

#define PI 3.141592
#define RADIAN 0.0174532

typedef struct {
	float MoveX, MoveZ;
	float SphereSize;
} Shape;

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

float BMoveX, BMoveZ, BRoty;
float MRotx, MRoty;
float TRotx, TRotz;
int dir;


// 21
void DrawTree();
void DrawRunningMachine();
void DrawPullUpBar();
void DrawBenchPress();
void Collide();

int SphereDir, LeafDir, LeftLegDir, RightLegDir, SwingDir, PushDir;
double LeafRadius;

float Conveyor, LeftLeg, RightLeg, Swing, Push;


// 22
void DrawAirplane();

GLUquadricObj *quadratic;
int propeller;
float airplaneX, airplaneZ;
int airplanedegree;

int checktime;

int airplaneRot;