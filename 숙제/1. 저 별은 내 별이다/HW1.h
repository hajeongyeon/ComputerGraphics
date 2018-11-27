#pragma once

#include <GL/freeglut.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

#define RADIAN 0.0174532

// 구조체
typedef struct {
	float x, y = 550.0f, rot;
	float p1[2], p2[2], p3[2];
	bool isRot = true;
	bool isStar = false;
} Triangle;

typedef struct {
	float y;
	bool isRot;
} Rect;

typedef struct {
	float x = 400.0f, y;
	float FallTime;
	float degree;
	float p1[2], p2[2], p3[2];
	bool isPush = false;
	bool isStar = false;
} LeftSliceTriangle;

typedef struct {
	float x = 400.0f, y;
	float FallTime;
	float degree;
	float p1[2], p2[2], p3[2];
	bool isPush = false;
	bool isStar = false;
} RightSliceTriangle;

typedef struct {
	float p1[2], p2[2], p3[2], p4[2], p5[2], p6[2];
	int Rot;
	float size;
	int dir;
	float r, g, b;
	float colX, colY;			// 충돌 좌표 저장
	float posX, posY;			// 별 위치 저장
} Star;

// 함수
void SetupRC();
GLvoid drawScene(GLvoid);

void Keyboard(unsigned char, int, int);
void TimerFunction(int); 
void TimerFunction2(int);
void Mouse(int, int, int, int);
void Motion(int, int);

GLvoid Reshape(int w, int h);

void DrawGrid();
void DrawSliceTriangle();
float FreeFall(float, float);
void Collision();
void MakeStar();
void DrawStar();

// 변수
vector<Triangle> triangle;
vector<Triangle>::iterator iter;

vector<Rect> rect;
vector<Rect>::iterator iter2;

vector<LeftSliceTriangle> Lslicetri;
vector<LeftSliceTriangle>::iterator iter3;

vector<RightSliceTriangle> Rslicetri;
vector<RightSliceTriangle>::iterator iter4;

vector<Star> star;
vector<Star>::iterator iter5;

bool left_button;

int mouseX[2], mouseY[2];	// 마우스 좌표 저장
float colX, colY;			// 충돌 좌표 저장
bool isSlice = false;