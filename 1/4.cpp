#include <GL/freeglut.h>
#include "456.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Mouse(int, int, int, int);
void TimerFunction(int);

void DrawRectangle(int, int, int, int);

vector<Shape> rect;
vector<Shape>::iterator iter;

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 4"); // 윈도우 생성 (윈도우 이름)
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

	srand((unsigned int)time(NULL));

	for (iter = rect.begin(); iter != rect.end(); ++iter)
	{
		R = (rand() % 256) / 256.0f;
		G = (rand() % 256) / 256.0f;
		B = (rand() % 256) / 256.0f;

		DrawRectangle((float)iter->x, (float)iter->y, (float)iter->width, (float)iter->length);
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
		s.width = rand() % 40 + 30;
		s.length = rand() % 40 + 30;
		s.shapeSize = 1;

		rect.push_back(s);

		if (rect.size() == 11) rect.erase(rect.begin());
	}
}

void TimerFunction(int value)
{
	srand((unsigned int)time(NULL));

	for (iter = rect.begin(); iter != rect.end(); ++iter)
	{
		iter->width += iter->shapeSize;
		iter->length += iter->shapeSize;

		if (iter->width < 30 || iter->width > 70)
		{
			iter->shapeSize *= -1;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawRectangle(int x, int y, int width, int length)
{
	glColor3f(R, G, B);

	glRectf(x - width, y - length, x + width, y + length);
}