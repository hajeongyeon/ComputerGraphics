#include <GL/freeglut.h>
#include "910.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);
void Motion(int, int);
void TimerFunction(int);

void DrawRectangle(int, int, int, float, float, float);
void DrawTrapezoid(int, int, int, float, float, float);
void DrawTriangle(int, int, int, float, float, float);
void DrawEraser(int, int);
void Collision(Shape*);

vector<Shape> shape;
vector<Shape>::iterator iter;
ShapeType type = RECTANGLE;

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 10"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	srand((unsigned int)time(NULL));

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		if (iter->type == RECTANGLE)
			DrawRectangle(iter->x, iter->y, iter->shapeSize, iter->R, iter->G, iter->B);
		else if (iter->type == TRAPEZOID)
			DrawTrapezoid(iter->x, iter->y, iter->shapeSize, iter->R, iter->G, iter->B);
		else
			DrawTriangle(iter->x, iter->y, iter->shapeSize, iter->R, iter->G, iter->B);
	}

	if (left_button)
		DrawEraser(currX, currY);

	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 0, 600, -1, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	srand((unsigned int)time(NULL));

	switch (key)
	{
	case '1':
		for (int i = 0; i < 30; ++i)
		{
			Shape s;

			int X = rand() % 2;
			int Y = rand() % 2;

			s.R = (rand() % 128) / 256.0f;
			s.G = (rand() % 128) / 256.0f;
			s.B = (rand() % 128) / 256.0f;

			s.x = (rand() % 780) + 1;
			s.y = (rand() % 580) + 1;
			s.shapeSize = 15;
			s.type = type;

			if (X == 1) s.xdir = 1;
			else s.xdir = -1;
			if (Y == 1) s.ydir = 1;
			else s.ydir = -1;

			s.trape_time = 0;
			s.tri_time = 0;

			shape.push_back(s);
		}
		break;

	default:
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	srand((unsigned int)time(NULL));

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		left_button = true;

		currX = x;
		currY = 600 - y;
	}
	else
	{
		left_button = false;
	}
}

void Motion(int x, int y)
{
	currX = x;
	currY = 600 - y;
}

void TimerFunction(int value)
{
	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		iter->x += (5 * iter->xdir);
		iter->y += (5 * iter->ydir);

		Collision(&(*iter));
	}

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		if ((iter->x - 15) <= (currX + 30) && (iter->x + 15) >= (currX - 30) &&
			(iter->y - 15) <= (currY + 30) && (iter->y + 15) >= (currY - 30) && iter->type == RECTANGLE)
		{
			iter->R = (rand() % 256) / 256.0f;
			iter->G = (rand() % 256) / 256.0f;
			iter->B = (rand() % 256) / 256.0f;

			iter->type = TRAPEZOID;
			iter->shapeSize += 20;
		}
	}

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		if (iter->type == TRAPEZOID)
		{
			iter->trape_time += 1;

			if (iter->trape_time >= 20)
			{
				iter->trape_time = 0;
				iter->type = TRIANGLE;
			}
		}
	}

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		if (iter->type == TRIANGLE)
		{
			iter->tri_time += 1;

			if (iter->tri_time >= 20)
				iter->shapeSize = 15;

			if (iter->tri_time >= 40)
			{
				iter->tri_time = 0;
				iter->type = RECTANGLE;
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawRectangle(int x, int y, int size, float r, float g, float b)
{
	glColor3f(r, g, b);

	glRectf(x - size, y - size, x + size, y + size);
}

void DrawTrapezoid(int x, int y, int size, float r, float g, float b)
{
	glColor3f(r, g, b);

	glRectf(x - size, y - size, x + size, y + size);

	glBegin(GL_TRIANGLES);

	glVertex2f(x - size, y + size);
	glVertex2f(x - size, y - size);
	glVertex2f(x - (size * 2), y - size);

	glVertex2f(x + size, y + size);
	glVertex2f(x + size, y - size);
	glVertex2f(x + (size * 2), y - size);

	glEnd();
}

void DrawTriangle(int x, int y, int size, float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);

	glVertex2f(x, y + size);
	glVertex2f(x - size, y - size);
	glVertex2f(x + size, y - size);

	glEnd();
}

void DrawEraser(int x, int y)
{
	glColor3f(0.5f, 1.0f, 1.0f);

	glRectf(x - 30, y - 30, x + 30, y + 30);
}

void Collision(Shape* shape)
{
	if ((shape->x - 15) <= 0)
		shape->xdir = 1;
	if ((shape->x + 15) >= 800)
		shape->xdir = -1;
	if ((shape->y - 15) <= 0)
		shape->ydir = 1;
	if ((shape->y + 15) >= 600)
		shape->ydir = -1;
}