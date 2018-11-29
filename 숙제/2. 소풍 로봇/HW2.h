#pragma once

#include <GL/freeglut.h>
#include <random>
#include <iostream>
using namespace std;

////// 구조체 //////

// 장애물
typedef struct {
	float x, y, z;
} OBJECT;

// 날씨
typedef struct {
	float x, y, z;
} WEATHER;

///////////////////


////// 변수 //////
GLfloat xRot, yRot;
bool right_button;

bool isOrtho, isEdit;				// 직교인지 원근인지 / 롤러코스터 편집 중인지

OBJECT obj[10];
int num;
GLfloat ctrlpoints[9][3];			// 롤러코스터 제어점
bool isCP;							// 제어점 위치가 장애물 위치랑 같은지

int WeatherType;					// 1 맑음 2 눈 3 비
WEATHER weather[100];

///////////////////


////// 함수 //////
void SetupRC();
GLvoid drawScene(GLvoid);
void Reshape(int w, int h);
void Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);
void Motion(int, int);
void TimerFunction(int);

void DrawWeather();