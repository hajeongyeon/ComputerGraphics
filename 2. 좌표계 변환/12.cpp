#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

#define PI 3.141592

typedef struct 
{
	float x = -1.0f, y;
} Point;

enum CourseType
{
	CIRCLE = 0,
	SINE = 1,
	TWISTER = 2,
	ZIGZAG = 3,
	COURSE = 4
};

enum ShapeType
{
	NOTHING = 0,
	TRIANGLE = 1,
	RECTANGLE = 2
};

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);
void TimerFunction(int);

double ConvertToRadian(double);

void DrawCircle();
void DrawSine();
void DrawTwister();
void DrawZigzag();
void DrawCourse();
void DrawTriangle();
void DrawRectangle();

CourseType coursetype = CIRCLE;
ShapeType shapetype = TRIANGLE;

bool TorR = false;						// true면 이동 false면 회전
float TriX = 0.0f, TriY = 0.5f, RectX = 0.0f, RectY = 0.5f;
float shapesize = 0.0f;					// 크기
int dir = 1;							// 크기 확대 축소 변환
float MoveX = 0.0f, MoveY = 0.0f;		// 위치
float Rot = 0.0f;						// 각도
int theta = 0;							// 원의 각도
Point point[5];

float tmpX = -150.0f;					// 회오리의 더해지는 x 값
float tmpDir = 1;						// 지그재그의 방향
int tmp = 0;							// 경로 변수..
bool click = false;						// 경로 클릭 체크
int idx = 0;							// Point 구조체 배열 개수
int yRot = 0.0f;						// y축 회전 각도

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 12"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard);
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

	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	if (coursetype == CIRCLE)
		DrawCircle();
	else if (coursetype == SINE)
		DrawSine();
	else if (coursetype == TWISTER)
		DrawTwister();
	else if (coursetype == ZIGZAG)
		DrawZigzag();
	else if (coursetype == COURSE)
		DrawCourse();

	if (!TorR && coursetype == CIRCLE)
	{
		glRotatef(Rot, 0.0f, 0.0f, 1.0f);
	}
	else
		glTranslatef(MoveX, MoveY, 0.0f);

	if (shapetype == TRIANGLE)
		DrawTriangle();
	else if (shapetype == RECTANGLE)
		DrawRectangle();

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
	case '0':
		coursetype = CIRCLE;
		shapetype = TRIANGLE;
		TorR = false;
		TriX = 0.0f, TriY = 0.5f;
		RectX = 0.0f, RectY = 0.5f;
		MoveX = 0.0f, MoveY = 0.0f;
		theta = 0;
		yRot = 0.0f;
		break;

	case '1':
		coursetype = SINE;
		shapetype = TRIANGLE;
		TorR = true;
		TriX = -1.0f, TriY = 0.0f;
		RectX = -1.0f, RectY = 0.0f;
		MoveX = 0.0f, MoveY = 0.0f;
		theta = 0;
		yRot = 0.0f;
		break;

	case '2':
		coursetype = TWISTER;
		shapetype = TRIANGLE;
		TorR = true;
		TriX = -0.85f, TriY = 0.0f;
		RectX = -0.85f, RectY = 0.0f;
		MoveX = 0.0f, MoveY = 0.0f;
		theta = -100;
		tmpX = -150.0f;
		yRot = 0.0f;
		break;

	case '3':
		coursetype = ZIGZAG;
		shapetype = TRIANGLE;
		TorR = true;
		TriX = -1.0f, TriY = 0.0f;
		RectX = -1.0f, RectY = 0.0f;
		MoveX = 0.0f, MoveY = 0.0f;
		tmpDir = 1;
		yRot = 0.0f;
		break;

	case '4':
		coursetype = COURSE;
		shapetype = NOTHING;
		TorR = true;
		MoveX = 0.0f, MoveY = 0.0f;
		TriX = MoveX, TriY = MoveX;
		RectX = MoveX, RectY = MoveY;
		click = false;
		yRot = 0.0f;
		break;

	case 'y':
		++yRot;
		break;

	case 'Y':
		--yRot;
		break;

	case 't': case 'T':			// Triangle
		shapetype = TRIANGLE;
		break;

	case 'r': case 'R':			// Rectangle
		shapetype = RECTANGLE;
		break;

	case 'o':					// Translate
		TorR = true;
		break;

	case 'O':					// Rotate
		TorR = false;
		break;

	case 'q': case 'Q':
		glutLeaveMainLoop();
		break;

	default:
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && coursetype == COURSE)
	{
		if (idx < 5) {
			point[idx].x = (float)(x - 400) / 400;
			point[idx].y = (float)(300 - y) / 300;
			idx++;
		}
		else
		{
			idx = 0;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && click == false)
	{
		click = true;
		shapetype = TRIANGLE;
	}
}

void TimerFunction(int value)
{
	if (shapesize > 0.02f || shapesize < 0.0f) dir *= -1;
	shapesize += (0.001f * dir);

	if (!TorR && coursetype == CIRCLE)
	{
		if (Rot <= 90.0f)
			Rot += 1.0f;
		else
			Rot += 1.0f;
	}
	else
	{
		if (coursetype == CIRCLE)
		{
			MoveX = cos(ConvertToRadian(theta)) * 0.5f;
			MoveY = sin(ConvertToRadian(theta)) * 0.5f - 0.5f;
			theta += 1;
		}
		else if (coursetype == SINE)
		{
			MoveX += 0.001f;
			MoveY = (500 * sin(ConvertToRadian(theta))) / 1000;
			theta += 1;
		}
		else if (coursetype == TWISTER)
		{
			MoveX = (150 * cos(ConvertToRadian(theta)) + tmpX) / 1000;
			MoveY = (500 * sin(ConvertToRadian(theta))) / 1000;
			theta += 1;
			tmpX += 0.8f;
		}
		else if (coursetype == ZIGZAG)
		{
			MoveX += 0.002f;
			MoveY += 0.01f * tmpDir;
			if (MoveY > 0.7f)
				tmpDir *= -1;
			else if (MoveY < -0.7f)
				tmpDir *= -1;
		}
		else if (coursetype == COURSE && click == true)
		{
			if (tmp < 51) {
				MoveX = point[0].x + (point[1].x - point[0].x) / 50 * tmp;
				MoveY = point[0].y + (point[1].y - point[0].y)*tmp / 50;
			}
			else if (tmp >= 51 && tmp < 101)
			{
				MoveX = point[1].x + (point[2].x - point[1].x) / 50 * (tmp - 50);
				MoveY = point[1].y + (point[2].y - point[1].y)*(tmp - 50) / 50;
			}
			else if (tmp >= 101 && tmp < 151)
			{
				MoveX = point[2].x + (point[3].x - point[2].x) / 50 * (tmp - 100);
				MoveY = point[2].y + (point[3].y - point[2].y)*(tmp - 100) / 50;
			}
			else if (tmp >= 151 && tmp < 201)
			{
				MoveX = point[3].x + (point[4].x - point[3].x) / 50 * (tmp - 150);
				MoveY = point[3].y + (point[4].y - point[3].y)*(tmp - 150) / 50;
			}
			else
			{
				MoveX = point[4].x;
				MoveY = point[4].y;
			}

			tmp += 1;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}

double ConvertToRadian(double DegreeValue)
{
	double RadianValue = DegreeValue * (PI / 180.0);
	return RadianValue;
}

void DrawCircle()
{
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i++)
		glVertex2f(cos(ConvertToRadian(i)) * 0.5f, sin(ConvertToRadian(i)) * 0.5f);

	glEnd();
}

void DrawSine()
{
	GLfloat x = -1.0f;

	glBegin(GL_LINE_STRIP);

	for (float t = 0.0f; t <= 2000.0f; t++)
	{
		glVertex3d(x, (500 * sin(ConvertToRadian(t))) / 1000, 0.0f);

		x += 0.001f;
	}

	glEnd();
}

void DrawTwister()
{
	GLfloat x = -1000.0f;

	glBegin(GL_LINE_STRIP);

	for (float t = -100.0f; t <= 2500.0f; t++)
	{
		glVertex3f((150 * cos(ConvertToRadian(t)) + x)/1000, (500 * sin(ConvertToRadian(t))) / 1000, 0.0f);

		x += 0.8f;
	}

	glEnd();
}

void DrawZigzag()
{
	GLfloat x = -1.0f, y = 0.0f;
	int dir = 1;

	glBegin(GL_LINE_STRIP);

	for (int i = 0; i < 1000; ++i)
	{
		glVertex3f(x, y, 0.0f);

		x += 0.002f;
		y += 0.01f * dir;

		if (y > 0.7f)
			dir *= -1;
		else if (y < -0.7f)
			dir *= -1;
	}

	glEnd();
}

void DrawCourse()
{
	glBegin(GL_LINE_STRIP);

	for (int i = 0; i < 4; i++)
	{
		glVertex2f(point[i].x, point[i].y);
		glVertex2f(point[i + 1].x, point[i + 1].y);
	}

	glEnd();
}

void DrawTriangle()
{
	glColor3f(0.5f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);

	glVertex2f(TriX, TriY + 0.05f + shapesize);
	glVertex2f(TriX - 0.05f - shapesize, TriY - 0.05f);
	glVertex2f(TriX + 0.05f + shapesize, TriY - 0.05f);

	glEnd();
}

void DrawRectangle()
{
	glColor3f(0.5f, 1.0f, 1.0f);

	glRectf(RectX -0.05f - shapesize, RectY + 0.05f + shapesize, RectX + 0.05f + shapesize, RectY - 0.05f - shapesize);
}