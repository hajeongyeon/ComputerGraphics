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
	glutCreateWindow("실습 19"); // 윈도우 생성 (윈도우 이름)
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
	radius = 2.0;
	MoveX = 0.0, MoveY = 0.0, MoveZ = 0.0;

	sRotx = 0.0, sRoty = 0.0, sRotz = 0.0;

	yRot = 0;
	zoom = 0.0f;
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// 좌표계
	glBegin(GL_LINES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glEnd();

	glTranslatef(0.0f, -10.0f, -20.0f);
	glTranslatef(0.0f, -0.0f, -zoom);
	glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
	//gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// Plane
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glScalef(1.0f, 0.0f, 1.0f);
		glutSolidCube(30.0f);
	glPopMatrix();

	// 구
	glPushMatrix();
		glTranslatef(0.0f, 2.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		YRoll();
		XRoll();
		ZRoll();
		glutWireSphere(radius, 10.0, 15.0);
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

	case 'l':
		sRotx += 3;
		MoveX += 2 * PI * radius / 120;
		break;

	case 'L':
		sRotx -= 3;
		MoveX -= 2 * PI * radius / 120;
		break;

	case 'm':
		sRoty += 3;
		break;

	case 'M':
		sRoty -= 3;
		break;

	case 'n':
		sRotz += 3;
		MoveZ += 2 * PI * radius / 120;
		break;

	case 'N':
		sRotz -= 3;
		MoveZ -= 2 * PI * radius / 120;
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void XRoll()
{
	if (MoveX > 14.0) MoveX = 14.0;
	else if (MoveX < -14.0) MoveX = -14.0;

	glTranslatef(0.0f, 0.0f, MoveX);
	glRotatef(sRotx, 1.0f, 0.0f, 0.0f);
}

void YRoll()
{
	glTranslatef(0.0f, 0.0f, MoveX);
	glTranslatef(MoveZ, 0.0f, 0.0f);
	glRotatef(sRoty, 0.0f, 1.0f, 0.0f);
	glTranslatef(-MoveZ, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -MoveX);
}

void ZRoll()
{
	if (MoveZ > 14.0) MoveZ = 14.0;
	else if (MoveZ < -14.0) MoveZ = -14.0;

	glTranslatef(MoveZ, 0.0f, 0.0f);
	glRotatef(-sRotz, 0.0f, 0.0f, 1.0f);
}