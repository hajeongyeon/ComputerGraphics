#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void DrawBigTriangle();
void DrawXYTriangle();
void DrawYZTriangle();

float BigRot = 0.0f, SmallRot = 0.0f;									// 회전 각도
float MoveX = 0.0f, MoveY1 = 0.0f , MoveY2 = 0.0f, MoveZ = 0.0f;		// 변환 위치
int tmp = 0;															// 경로 변수..
float shapesize = 1.0f;													// 크기

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 13"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// 선
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINES);
	glVertex2f(-1.0, 0.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, 1.0);
	glEnd();

	glLoadIdentity();

	glPushMatrix();
	
	glRotatef(BigRot, 0.0f, 1.0f, 0.0f);
	glScalef(shapesize, shapesize, shapesize);
	DrawBigTriangle();

	glPushMatrix();
	glTranslatef(MoveX, MoveY1, 0.0f);
	glRotatef(SmallRot, 0.0f, 1.0f, 0.0f);
	DrawXYTriangle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, MoveY2, MoveZ);
	glRotatef(SmallRot, 0.0f, 1.0f, 0.0f);
	DrawYZTriangle();
	glPopMatrix();

	glPopMatrix();

	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -400.0, 400.0);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'y':
		++BigRot;
		SmallRot += 5.0f;
		break;

	case 'Y':
		--BigRot;
		SmallRot += 5.0f;
		break;

	case 's':
		shapesize += 0.05f;
		break;

	case 'S':
		shapesize -= 0.05f;
		break;

	case 'q': case 'Q':
		glutLeaveMainLoop();
		break;

	default:
		break;
	}
}

void TimerFunction(int value)
{
	if (tmp < 80)
	{
		MoveX -= 0.01f;
		MoveY1 -= 0.02f;
		MoveY2 -= 0.02f;
		MoveZ -= 0.01f;
	}
	else if (tmp >= 80 && tmp < 160)
	{
		MoveX += 0.02f;
		MoveZ += 0.02f;
	}
	else if (tmp >= 160 && tmp < 240)
	{
		MoveX -= 0.01f;
		MoveY1 += 0.02f;
		MoveY2 += 0.02f;
		MoveZ -= 0.01f;
	}

	++tmp;

	if (tmp > 240)
		tmp = 0;

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawBigTriangle()
{
	glBegin(GL_LINES);

	// xy 큰 삼각형
	glVertex3f(0, 0.8, 0);
	glVertex3f(-0.8, -0.8, 0);
	glVertex3f(-0.8, -0.8, 0);
	glVertex3f(0.8, -0.8, 0);
	glVertex3f(0.8, -0.8, 0);
	glVertex3f(0, 0.8, 0);

	// yz 큰 삼각형
	glVertex3f(0, 0.8, 0);
	glVertex3f(0, -0.8, -0.8);
	glVertex3f(0, -0.8, -0.8);
	glVertex3f(0, -0.8, 0.8);
	glVertex3f(0, -0.8, 0.8);
	glVertex3f(0, 0.8, 0);

	glEnd();
}

void DrawXYTriangle()
{
	// xy 작은 삼각형
	glColor3f(1.0, 1.0f, 0.5f);
	glBegin(GL_TRIANGLES);

	glVertex3f(0, 0.85, 0);
	glVertex3f(-0.05, 0.75, 0);
	glVertex3f(0.05, 0.75, 0);

	glEnd();
}

void DrawYZTriangle()
{
	// yz 작은 삼각형
	glColor3f(1.0f, 0.5f, 1.0f);
	glBegin(GL_TRIANGLES);

	glVertex3f(0, 0.85, 0);
	glVertex3f(0, 0.75, -0.05);
	glVertex3f(0, 0.75, 0.05);

	glEnd();
}