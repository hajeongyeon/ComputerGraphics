#pragma once

#include <GL/freeglut.h>
#include <random>
#include <time.h>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

////// 구조체 //////

// 장애물
typedef struct {
	float x, y, z;
} OBJECT;

typedef struct {
	int RobotDir, RobotRot;						// 로봇 방향, 각도
	float LLeg, RLeg, LArm, RArm;				// 팔 다리 각도
	int LLegDir, RLegDir, LArmDir, RArmDir;		// 팔 다리 방향
	float MoveX, MoveZ;							// 이동

	GLfloat capepoints[10][3][3];
	int capeXdir = 1, capeZdir = 1;
	int capeYdir1 = 1, capeYdir2 = 1, capeYdir3 = 1;
} ROBOT;

// 총알
typedef struct {
	float x = -1000, y = -1000, z = -1000;
	int dir = 0;
	int time = 0;
} BULLET;

// 날씨
typedef struct {
	float x, y, z;
} WEATHER;

///////////////////


////// 변수 //////

// 기본 변수들
GLfloat xTrs, yTrs, xRot, yRot, zoom;
bool right_button;

// bool
bool isOrtho, isEdit;					// 직교인지 원근인지 / 롤러코스터 편집 중인지
bool isCP;								// 제어점 위치가 장애물 위치랑 같은지
bool isFire, BTcollision, BPcollision;	// 총알 발사, 총알 충돌체크

// 롤러코스터 변수들
OBJECT obj[10];
int num;
GLfloat ctrlpoints[7][3];			// 롤러코스터 제어점
GLfloat tmp[7];

// 로봇 관련 변수들
ROBOT robot[2];

vector<BULLET> bullet;
vector<BULLET>::iterator iter;

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

void DrawPillar(float, float, float);
void DrawTree();
void DrawRobot();
void DrawBullet();
void MakeCape();
void DrawCape();
void DrawWeather();

void ROCollide();		// 로봇과 오브젝트의 충돌
void BOCollide();		// 총알과 오브젝트의 충돌