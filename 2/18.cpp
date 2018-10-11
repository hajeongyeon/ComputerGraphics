//	18. 실습 16에 카메라 적용하기
//	- 실습 16에서 양쪽의 객체는 자동으로 모델의 y축 기준으로 회전하고 있다.
//	  실습 16의 명령어는 계속 실행하도록 한다.
//	- 키보드 명령을 적용한다.
//	  i / o : 카메라를 z축에 대해 줌인 / 줌아웃 한다
//	  + / -: 카메라를 전체의 y축 기준으로 양 / 음 방향으로 회전한다
//	  카메라는 항상 중앙을 바라보고 있다.

#include <GL/freeglut.h>
#include <iostream>
#include "1618.h"
using namespace std;

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 18"); // 윈도우 생성 (윈도우 이름)
	SetupRC(); // 상태 변수 초기화 함수
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}

// 초기화 함수
void SetupRC()
{
	shapetype = Sphere;
	type = 1;

	AllrotX = 0.0f;
	AllrotY = 0.0f;
	AllrotZ = 0.0f;

	LrotX = 0.0f;
	LrotY = 0.0f;
	LrotZ = 0.0f;

	RrotX = 0.0f;
	RrotY = 0.0f;
	RrotZ = 0.0f;

	zoom = 0.0;
	CameraRot = 0.0f;
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 좌표계
	glLoadIdentity();
	AllRotation();
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

	if (CameraRot > 20.0f)
		CameraRot = 20.0f;

	glTranslatef(0.0f, 0.0f, CameraRot);
	gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

	// Plane
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -10.0f, 10.0f);
	glScalef(1.0f, 0.1f, 1.0f);
	glutSolidCube(30.0f);
	glPopMatrix();

	// 도형
	glPushMatrix();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(-8.0f, -5.0f, 0.0f);
	LRotation();
	DrawSolidShape();
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 1.0f);
	glTranslatef(8.0f, -5.0f, 0.0f);
	RRotation();
	DrawWireShape();
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

	// 관측 변환: 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능)
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x': case 'X':
		AllrotX++;
		LrotX += 3;
		RrotX += 3;
		break;

	case 'y': case 'Y':
		AllrotY++;
		break;

	case 'z': case 'Z':
		AllrotZ++;
		LrotZ += 3;
		RrotZ += 3;
		break;

	case 'c': case 'C':
		++type;

		if (type == 1)
			shapetype = Sphere;
		else if (type == 2)
			shapetype = Cube;
		else if (type == 3)
			shapetype = Cone;
		else if (type == 4)
		{
			shapetype = Teapot;
			type = 0;
		}

		break;

	case 'i': case 'I':
		zoom -= 0.5;
		break;

	case 'o': case 'O':
		zoom += 0.5;
		break;

	case '+':
		CameraRot += 0.1f;
		break;

	case '-':
		CameraRot -= 0.1f;
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	LrotY += 3;
	RrotY += 3;

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawSolidShape()
{
	switch (shapetype)
	{
	case Sphere:
		glutSolidSphere(5.0, 20.0, 20.0);
		break;

	case Cube:
		glutSolidCube(5.0);
		break;

	case Cone:
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		glutSolidCone(5.0, 5.0, 20.0, 20.0);
		break;

	case Teapot:
		glutSolidTeapot(5.0);
		break;
	}
}

void DrawWireShape()
{
	switch (shapetype)
	{
	case Sphere:
		glutWireSphere(5.0, 20.0, 20.0);
		break;

	case Cube:
		glutWireCube(5.0);
		break;

	case Cone:
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		glutWireCone(5.0, 5.0, 20.0, 20.0);
		break;

	case Teapot:
		glutWireTeapot(5.0);
		break;
	}
}

void AllRotation()
{
	glRotatef(AllrotX, 1.0f, 0.0f, 0.0f);
	glRotatef(AllrotY, 0.0f, 1.0f, 0.0f);
	glRotatef(AllrotZ, 0.0f, 0.0f, 1.0f);
}

void LRotation()
{
	glRotatef(LrotX, 1.0f, 0.0f, 0.0f);
	glRotatef(LrotY, 0.0f, 1.0f, 0.0f);
	glRotatef(LrotZ, 0.0f, 0.0f, 1.0f);
}

void RRotation()
{
	glRotatef(RrotX, 1.0f, 0.0f, 0.0f);
	glRotatef(RrotY, 0.0f, 1.0f, 0.0f);
	glRotatef(RrotZ, 0.0f, 0.0f, 1.0f);
}