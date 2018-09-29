// �ǽ� 3 : ������ ���� �׸���
// ȭ���� ���ο� ���θ� ���� 3����Ѵ�.
// ȭ���� ù ĭ�� �Ʒ��� ���� �� �� ���� ������ �׸���.
// ���� : ��, �ﰢ��, �簢��, ������
// ���� ĭ���� ������ �������� �� ���� �þ�� �׸���, ������ �Ŀ��� �������� �ٽ� �׸���
// �� -> �ﰢ�� -> �簢�� -> ������ -> �簢��
// ���۵Ǵ� ������ ���Ƿ� ���õȴ�.

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
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 3"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	bool updown = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

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

	glFlush(); // ȭ�鿡 ����ϱ�
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