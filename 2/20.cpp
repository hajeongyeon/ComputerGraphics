#include <GL/freeglut.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <iterator>
#include "19to22.h"
using namespace std;

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 20"); // 윈도우 생성 (윈도우 이름)
	SetupRC(); // 상태 변수 초기화 함수
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glutMainLoop();
}

// 초기화 함수
void SetupRC()
{
	yRot = 0;
	zoom = 0.0f;

	BMoveX = 0.0f, BRoty = 0.0f;
	MRotx = 0.0f, MRoty = 0.0f;
	TRotx = 0.0f, TRotz = 0.0f;
	dir = 1;
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0.0f, -10.0f, -20.0f);
	glTranslatef(0.0f, 0.0f, -zoom);
	glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
	//gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// Plane
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glScalef(1.0f, 0.0f, 1.0f);
		glutSolidCube(30.0f);
	glPopMatrix();

	if (MRotx >= 90.0f) MRotx = 90.0f;
	else if (MRotx <= -90.0f) MRotx = -90.0f;

	if (TRotx >= 90.0f) TRotx = 90.0f;
	else if (TRotx <= -90.0f) TRotx = -90.0f;

	if (TRotz >= 90.0f) TRotz = 90.0f;
	else if (TRotz <= -90.0f) TRotz = -90.0f;

	glPushMatrix();
		glTranslatef(BMoveX, 0.0f, 0.0f);
		glRotatef(BRoty, 0.0f, 1.0f, 0.0f);
		BottomBody();
		//
		glPushMatrix();
			glTranslatef(BMoveX, 6.0f, 0.0f);
			glRotatef(MRotx, 1.0f, 0.0f, 0.0f);
			glTranslatef(-BMoveX, -6.0f, 0.0f);
			glRotatef(MRoty, 0.0f, 1.0f, 0.0f);
			MiddleBody();
			//
			glPushMatrix();
				glTranslatef(BMoveX, 13.5f, 0.0f);
				glRotatef(TRotx, 1.0f, 0.0f, 0.0f);
				glTranslatef(-BMoveX, -13.5f, 0.0f);
				glTranslatef(0.0f, 13.5f, 0.0f);
				glRotatef(TRotz, 0.0f, 0.0f, 1.0f);
				glTranslatef(-0.0f, -13.5f, 0.0f);
				TopBody();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 원근 투영
	gluPerspective(60.0f, w / h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -30.0);

	// 직각 투영
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'y': case 'Y':
		yRot++;
		break;

	case '+':
		zoom -= 0.1f;
		break;

	case '-':
		zoom += 0.1f;
		break;

	case 'i': case 'I':
		SetupRC();
		break;

	// 아래 몸체 y축 회전
	case '1':
		BRoty += 3;
		break;

	// 중간 몸체 x축 회전 (양)
	case '2':
		MRotx += 1;
		break;

	// 중간 몸체 x축 회전 (음)
	case '3':
		MRotx -= 1;
		break;

	// 중간 몸체 y축 회전 (양)
	case '4':
		MRoty += 1;
		break;

	// 중간 몸체 y축 회전 (음)
	case '5':
		MRoty -= 1;
		break;

	// 위 몸체 x축 회전 (양)
	case '6':
		TRotx += 1;
		break;

	// 위 몸체 x축 회전 (음)
	case '7':
		TRotx -= 1;
		break;

	// 위 몸체 z축 회전 (양)
	case '8':
		TRotz += 1;
		break;

	// 위 몸체 z축 회전 (음)
	case '9':
		TRotz -= 1;
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	BMoveX += 0.5f * dir;

	if (BMoveX > 10) dir = -1;
	else if (BMoveX < -10) dir = 1;

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void BottomBody()
{
	glPushMatrix();
		glTranslatef(0.0f, 4.0f, 0.0f);
		glScalef(1.0f, 0.5f, 0.8f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidCube(8.0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(8.0);
	glPopMatrix();
}

void MiddleBody()
{
	glPushMatrix();
		glTranslatef(0.0f, 10.0f, 0.0f);
		glScalef(0.3f, 1.0f, 0.3f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glutSolidCube(7.0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(7.0);
	glPopMatrix();
}

void TopBody()
{
	glPushMatrix();
		glTranslatef(0.0f, 15.0f, 0.0f);
		glScalef(0.1f, 0.5f, 0.1f);
		glColor3f(0.0f, 1.0f, 1.0f);
		glutSolidCube(7.0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(7.0);
	glPopMatrix();
}