#pragma once

#include <GL/freeglut.h>
#include <random>
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
GLfloat xRot, yRot;
bool right_button;

bool isOrtho, isEdit;				// �������� �������� / �ѷ��ڽ��� ���� ������

OBJECT obj[10];
int num;
GLfloat ctrlpoints[9][3];			// �ѷ��ڽ��� ������
bool isCP;							// ������ ��ġ�� ��ֹ� ��ġ�� ������

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

void DrawWeather();