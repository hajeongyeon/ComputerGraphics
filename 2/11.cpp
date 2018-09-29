#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

#define PI 3.141592

enum ShapeType
{
	NOTHING = 0,
	SINE = 1,
	SPRING = 2,
	RIBBON = 3,
	RECTANGLE = 4
};

typedef struct {
	int moveX, moveY;
	int Xsize, Ysize;
	bool Manim, Panim;
	ShapeType type;
} Shape;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char, int, int);
void TimerFunction(int);

double ConvertToRadian(double);

void DrawSineWave(int, int, float, float, bool, bool);	// 사인 곡선
void DrawSpring(int, int, float, float, bool, bool);		// 스프링
void DrawRibbon(int, int, int, int, bool, bool);		// 리본
void DrawRectangle(int, int, int, int, bool, bool);	// 사각형

ShapeType shapetype = NOTHING;

vector<Shape> shape;
vector<Shape>::iterator iter;

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 11"); // 윈도우 생성 (윈도우 이름)
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

	// 선
	glColor3f(1.0f, 1.0f, 1.0f);

	GLint p1[2] = { 0, 300 };
	GLint p2[2] = { 800, 300 };
	GLint p3[2] = { 400, 0 };
	GLint p4[2] = { 400, 600 };

	glBegin(GL_LINES);
	glVertex2iv(p1);
	glVertex2iv(p2);
	glVertex2iv(p3);
	glVertex2iv(p4);
	glEnd();

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		if (iter->type == 1)
			DrawSineWave(iter->moveX, iter->moveY, iter->Xsize, iter->Ysize, iter->Manim, iter->Panim);
		else if (iter->type == 2)
			DrawSpring(iter->moveX, iter->moveY, iter->Xsize, iter->Ysize, iter->Manim, iter->Panim);
		else if (iter->type == 3)
			DrawRibbon(iter->moveX, iter->moveY, iter->Xsize, iter->Ysize, iter->Manim, iter->Panim);
		else if (iter->type == 4)
			DrawRectangle(iter->moveX, iter->moveY, iter->Xsize, iter->Ysize, iter->Manim, iter->Panim);
	}

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
	case '1':
	{
		Shape s;

		s.moveX = 0;
		s.moveY = 0;
		s.Xsize = 0;
		s.Ysize = 0;
		s.Manim = false;
		s.Panim = false;
		s.type = SINE;
		shape.push_back(s);
	}
		break;

	case '2':
	{
		Shape s;

		s.moveX = 0;
		s.moveY = 0;
		s.Xsize = 0;
		s.Ysize = 0;
		s.Manim = false;
		s.Panim = false;
		s.type = SPRING;
		shape.push_back(s);
	}
		break;

	case '3':
	{
		Shape s;

		s.moveX = 0;
		s.moveY = 0;
		s.Xsize = 0;
		s.Ysize = 0;
		s.Manim = false;
		s.Panim = false;
		s.type = RIBBON;
		shape.push_back(s);
	}
		break;

	case '4':
	{
		Shape s;

		s.moveX = 0;
		s.moveY = 0;
		s.Xsize = 0;
		s.Ysize = 0;
		s.Manim = false;
		s.Panim = false;
		s.type = RECTANGLE;
		shape.push_back(s);
	}
		break;

	case 'x':
		for (iter = shape.begin(); iter != shape.end(); ++iter)
		{
			if(!iter->Manim || !iter->Panim)
				iter->moveX += 10;
		}
		break;

	case 'X':
		for (iter = shape.begin(); iter != shape.end(); ++iter)
		{
			if (!iter->Manim || !iter->Panim)
				iter->moveX -= 10;
		}
		break;

	case 'y': 
		for (iter = shape.begin(); iter != shape.end(); ++iter)
		{
			if (!iter->Manim || !iter->Panim)
				iter->moveY += 10;
		}
		break;

	case 'Y':
		for (iter = shape.begin(); iter != shape.end(); ++iter)
		{
			if (!iter->Manim || !iter->Panim)
				iter->moveY -= 10;
		}
		break;

	case 's': 
		for (iter = shape.begin(); iter != shape.end(); ++iter) iter->Xsize += 10;
		break;

	case 'S':
		for (iter = shape.begin(); iter != shape.end(); ++iter) iter->Xsize -= 10;
		break;

	case 'r':
		for (iter = shape.begin(); iter != shape.end(); ++iter) iter->Ysize += 10;
		break;

	case 'R':
		for (iter = shape.begin(); iter != shape.end(); ++iter) iter->Ysize -= 10;
		break;

	case 'a':
		for (iter = shape.begin(); iter != shape.end(); ++iter)
		{
			if (iter->Manim) iter->Manim = false;
			iter->Panim = true;
		}
		break;

	case 'A':
		for (iter = shape.begin(); iter != shape.end(); ++iter)
		{
			if (iter->Panim) iter->Panim = false;
			iter->Manim = true;
		}
		break;

	case 't': case 'T':
		for (iter = shape.begin(); iter != shape.end(); ++iter)
		{
			iter->Panim = false;
			iter->Manim = false;
		}
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
	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		if (iter->Panim)
			iter->moveX += 10;
		else if (iter->Manim)
			iter->moveX -= 10;
	}
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

double ConvertToRadian(double DegreeValue)
{
	double RadianValue = DegreeValue * (PI / 180.0);
	return RadianValue;
}

void DrawSineWave(int moveX, int moveY, float Xsize, float Ysize, bool Manim, bool Panim)
{
	GLfloat x = 0.0f;

	if (Xsize < -100)
		Xsize = -100;
	if (Ysize < -100)
		Ysize = -100;

	glColor3f(1.0f, 0.5f, 1.0f);
	glBegin(GL_POINTS);

	for (float theta = 0.0f; theta <= 2100.0f; theta += 1.0f)
	{
		glVertex3d(200 + x + moveX - Xsize, 500 + (50 + Ysize/10) * sin(ConvertToRadian(theta)) + moveY, 0.0f);

		x += (0.2f + Xsize / 1000);
	}

	glEnd();
}

void DrawSpring(int moveX, int moveY, float Xsize, float Ysize, bool Manim, bool Panim)
{
	GLfloat x = 0.0f;

	if (Xsize < -100)
		Xsize = -100;
	if (Ysize < -100)
		Ysize = -100;

	glColor3f(1.0f, 1.0f, 0.5f);
	glBegin(GL_LINE_STRIP);

	for (float theta = -100.0f; theta <= 2100.0f; theta += 1.0f)
	{
		glVertex3f(40.0f * cos(ConvertToRadian(theta)) + 200 + x + moveX - Xsize, (40.0f + Ysize/10) * sin(ConvertToRadian(theta)) + 350 + moveY, 0.0f);

		x += (0.2f + Xsize / 1000);
	}

	glEnd();
}

void DrawRibbon(int moveX, int moveY, int Xsize, int Ysize, bool Manim, bool Panim)
{
	if (Xsize < -40)
		Xsize = -40;
	if (Ysize < -120)
		Ysize = -120;

	glColor3f(0.5f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);

	glVertex2f(350 + moveX - Xsize, 250 + moveY + (Ysize/10));
	glVertex2f(350 + moveX - Xsize, 200 + moveY - (Ysize / 10));
	glVertex2f(400 + moveX, 225 + moveY);

	glVertex2f(450 + moveX + Xsize, 250 + moveY + (Ysize / 10));
	glVertex2f(450 + moveX + Xsize, 200 + moveY - (Ysize / 10));
	glVertex2f(400 + moveX, 225 + moveY);

	glEnd();
}

void DrawRectangle(int moveX, int moveY, int Xsize, int Ysize, bool Manim, bool Panim)
{
	int Xtmp = 0;
	int rectsize = Xsize / 10;
	int rectsize2 = Ysize / 10;

	if (rectsize > 20)
		rectsize = 20;
	else if (rectsize < -20)
		rectsize = -20;

	if (rectsize2 < -20)
		rectsize2 = -20;

	glColor3f(0.5f, 0.5f, 1.0f);

	for (int i = 0; i < 4; ++i)
	{
		glRectf(100 + (i * 150) + Xtmp + moveX - rectsize, 150 + moveY + rectsize2, 200 + (i * 150) + Xtmp + moveX + rectsize, 50 + moveY - rectsize2);

		if (i == 1)
			Xtmp += 50;
	}
}