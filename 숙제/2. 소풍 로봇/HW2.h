#pragma once

#include <GL/freeglut.h>
#include <random>
#include <time.h>
#include <iostream>
using namespace std;

////// ����ü //////

// ��ֹ�
typedef struct {
	float x, y, z;
} OBJECT;

// ����
typedef struct {
	float x, y, z;
} WEATHER;

///////////////////


////// ���� //////

// �⺻ ������
GLfloat xRot, yRot, zoom;
bool right_button;

// bool
bool isOrtho, isEdit;				// �������� �������� / �ѷ��ڽ��� ���� ������
bool isCP;							// ������ ��ġ�� ��ֹ� ��ġ�� ������

// �ѷ��ڽ��� ������
OBJECT obj[10];
int num;
GLfloat ctrlpoints[9][3];			// �ѷ��ڽ��� ������

// �κ� ������
int RobotDir, RobotRot;						// �κ� ����, ����
float LLeg, RLeg, LArm, RArm;				// �� �ٸ� ����
int LLegDir, RLegDir, LArmDir, RArmDir;		// �� �ٸ� ����
float MoveX, MoveZ, Jump;					// �̵�

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

void DrawTree();
void DrawRobot();
void DrawWeather();