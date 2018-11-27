// 실습 3 : 임의의 도형 그리기
// 화면의 가로와 세로를 각각 3등분한다.
// 화면의 첫 칸에 아래의 도형 중 한 개의 도형을 그린다.
// 도형 : 선, 삼각형, 사각형, 오각형
// 다음 칸부터 도형의 꼭지점이 한 개씩 늘어나게 그리고, 오각형 후에는 역순으로 다시 그린다
// 선 -> 삼각형 -> 사각형 -> 오각형 -> 사각형
// 시작되는 도형은 임의로 선택된다.

#include <GL/freeglut.h>
#include <ctime>

GLvoid Reshape(int, int);
GLvoid drawScene(GLvoid);

void DrawGuideLine();
void DrawLine(float, float);
void DrawTriangle(float, float);
void DrawRectangle(float, float);
void DrawPentagon(float, float);

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 3"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	bool updown = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	DrawGuideLine();

	srand((unsigned int)time(NULL));

	int idx = rand() % 4 + 1;

	for (int i = 0; i < 9; ++i)
	{
		int x, y;

		if (i % 3 == 0)
			x = -200;
		else if (i % 3 == 1)
			x = 0;
		else if (i % 3 == 2)
			x = 200;

		if (i < 3)
			y = 200;
		else if (i > 2 && i < 6)
			y = 0;
		else if (i > 5 && i < 9)
			y = -200;

		if (idx == 1)
		{
			DrawLine(x, y);
			updown = true;
		}
		else if (idx == 2)
			DrawTriangle(x, y);
		else if (idx == 3)
			DrawRectangle(x, y);
		else if (idx == 4)
		{
			DrawPentagon(x, y);
			updown = false;
		}

		if (updown)
			idx++;
		if (!updown)
			idx--;
	}

	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-300.0, 300.0, -300.0, 300.0, -1.0, 1.0);
}

void DrawGuideLine()
{
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINES);

	glVertex2f(-300, 100);
	glVertex2f(300, 100);
	glVertex2f(-300, -100);
	glVertex2f(300, -100);
	glVertex2f(100, -300);
	glVertex2f(100, 300);
	glVertex2f(-100, -300);
	glVertex2f(-100, 300);

	glEnd();
}

void DrawLine(float x, float y)
{
	glColor3f(1.0f, 0.5f, 1.0f);

	glLineWidth(2.0f);

	glBegin(GL_LINES);

	glVertex2f(x - 50, y + 50);
	glVertex2f(x + 50, y - 50);

	glEnd();
}

void DrawTriangle(float x, float y)
{
	glColor3f(1.0f, 0.5f, 1.0f);
	glBegin(GL_TRIANGLES);

	glVertex2f(x, y + 50);
	glVertex2f(x - 50, y - 50);
	glVertex2f(x + 50, y - 50);

	glEnd();
}

void DrawRectangle(float x, float y)
{
	glColor3f(1.0f, 0.5f, 1.0f);

	glRectf(x - 50, y - 50, x + 50, y + 50);
}

void DrawPentagon(float x, float y)
{
	glColor3f(1.0f, 0.5f, 1.0f);

	glBegin(GL_POLYGON);

	glVertex2i(x - 50, y + 20);
	glVertex2i(x - 30, y - 50);
	glVertex2i(x + 30, y - 50);
	glVertex2i(x + 50, y + 20);
	glVertex2f(x, y + 75);

	glEnd();
}