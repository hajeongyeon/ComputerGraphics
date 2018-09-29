#include <GL/freeglut.h>
#include "78.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Mouse(int, int, int, int);
void TimerFunction(int);

void DrawCircle(int, int, int);

vector<Shape> circle;
vector<Shape>::iterator iter;

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 7"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	for (iter = circle.begin(); iter != circle.end(); ++iter)
	{
		if (iter->check == 0)
		{
			R = (rand() % 256) / 256.0f;
			G = (rand() % 256) / 256.0f;
			B = (rand() % 256) / 256.0f;
		}
		else
		{
			R = 0.5f;
			G = 1.0f;
			B = 1.0f;
		}

		DrawCircle(iter->x, iter->y, iter->rad);
	}

	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 0, 600, -1, 1);
}

void Mouse(int button, int state, int x, int y)
{
	srand((unsigned int)time(NULL));

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Shape s;

		s.x = x;
		s.y = 600 - y;
		s.rad = rand() % 30 + 30;
		s.SaveRad = s.rad;
		s.check = rand() % 5;

		circle.push_back(s);

		if (circle.size() == 6) circle.erase(circle.begin());
	}
}

void TimerFunction(int value)
{
	srand((unsigned int)time(NULL));

	for (iter = circle.begin(); iter != circle.end(); ++iter)
	{
		iter->rad += 10;

		if (iter->check != 0 && iter->rad >= 150)
		{
			iter->rad = iter->SaveRad;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawCircle(int x, int y, int rad)
{
	glColor3f(R, G, B);

	glBegin(GL_POINTS);

	for (int i = 0; i < 360; i++)
	{
		double angle = i * 3.141592 / 30;
		double tmpX = rad * cos(angle) + x;
		double tmpY = rad * sin(angle) + y;
		glVertex2f(tmpX, tmpY);
	}

	glEnd();
}