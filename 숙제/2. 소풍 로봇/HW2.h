#pragma once

#include <GL/freeglut.h>
#include <random>
#include <time.h>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

////// ����ü //////

// ��ֹ�
typedef struct {
	float x, y, z;
} OBJECT;

typedef struct {
	int RobotDir, RobotRot;						// �κ� ����, ����
	float LLeg, RLeg, LArm, RArm;				// �� �ٸ� ����
	int LLegDir, RLegDir, LArmDir, RArmDir;		// �� �ٸ� ����
	float MoveX, MoveZ;							// �̵�

	GLfloat capepoints[10][3][3];
	int capeXdir = 1, capeZdir = 1;
	int capeYdir1 = 1, capeYdir2 = 1, capeYdir3 = 1;
} ROBOT;

// �Ѿ�
typedef struct {
	float x = -1000, y = -1000, z = -1000;
	int dir = 0;
	int time = 0;
} BULLET;

// ����
typedef struct {
	float x, y, z;
} WEATHER;

///////////////////


////// ���� //////

// �⺻ ������
GLfloat xTrs, yTrs, xRot, yRot, zoom;
bool right_button;

// bool
bool isOrtho, isEdit;					// �������� �������� / �ѷ��ڽ��� ���� ������
bool isCP;								// ������ ��ġ�� ��ֹ� ��ġ�� ������
bool isFire, BTcollision, BPcollision;	// �Ѿ� �߻�, �Ѿ� �浹üũ

// �ѷ��ڽ��� ������
OBJECT obj[10];
int num;
GLfloat ctrlpoints[7][3];			// �ѷ��ڽ��� ������
GLfloat tmp[7];

// �κ� ���� ������
ROBOT robot[2];

vector<BULLET> bullet;
vector<BULLET>::iterator iter;

// ���� ������
int WeatherType;					// 1 ���� 2 �� 3 ��
WEATHER weather[100];

///////////////////


////// �Լ� //////

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

void ROCollide();		// �κ��� ������Ʈ�� �浹
void BOCollide();		// �Ѿ˰� ������Ʈ�� �浹