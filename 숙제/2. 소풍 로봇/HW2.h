#pragma once

#include <GL/freeglut.h>
#include <random>
#include <time.h>
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

// 기본 변수들
GLfloat xRot, yRot, zoom;
bool right_button;

// bool
bool isOrtho, isEdit;				// 직교인지 원근인지 / 롤러코스터 편집 중인지
bool isCP;							// 제어점 위치가 장애물 위치랑 같은지

// 롤러코스터 변수들
OBJECT obj[10];
int num;
GLfloat ctrlpoints[9][3];			// 롤러코스터 제어점

// 로봇 변수들
int RobotDir, RobotRot;						// 로봇 방향, 각도
float LLeg, RLeg, LArm, RArm;				// 팔 다리 각도
int LLegDir, RLegDir, LArmDir, RArmDir;		// 팔 다리 방향
float MoveX, MoveZ, Jump;					// 이동

// 날씨 변수들
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

void DrawTree();
void DrawRobot();
void DrawWeather();