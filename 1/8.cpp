#include <GL/freeglut.h>
#include "78.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Mouse(int, int, int, int);
void TimerFunction(int);

void DrawCircle(int, int, int, int, int, double, double);

vector<Shape> circle;
vector<Shape>::iterator iter;

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 8"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	for (iter = circle.begin(); iter != circle.end(); ++iter)
	{
		DrawCircle(iter->x, iter->y, iter->rad, iter->degree, iter->check, iter->tmpX, iter->tmpY);
	}

	glFlush(); // ȭ�鿡 ����ϱ�
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
		s.rad = 5;
		s.SaveRad = s.rad;
		s.check = rand() % 2;
		s.degree = 0;
		s.tmpX = 0;
		s.tmpY = 0;

		circle.push_back(s);

		if (circle.size() == 11) circle.erase(circle.begin());
	}
}

void TimerFunction(int value)
{
	srand((unsigned int)time(NULL));

	for (iter = circle.begin(); iter != circle.end(); ++iter)
	{
		if (iter->degree >= 120)
			iter->degree = 120;
		else
			iter->degree += 1;
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawCircle(int x, int y, int rad, int degree, int check, double tmpX, double tmpY)
{
	double angle;

	glColor3f(R, G, B);

	glBegin(GL_POINTS);

	for (int i = 0; i < degree; ++i)
	{
		angle = (i * 3.141592) / 10;

		if (check == 0)
		{
			if (i <= 60)
			{
				tmpX = (rad + i / 2) * cos(angle) + x;
				tmpY = (rad + i / 2) * sin(angle) + y;
			}
			else
			{
				tmpX = (rad - (140 - i) / 2) * cos(-angle) + x + 70;
				tmpY = (rad - (140 - i) / 2) * sin(-angle) + y;
			}
		}
		else
		{
			if (i <= 60)
			{
				tmpX = (rad + i / 2) * cos(-angle) + x;
				tmpY = (rad + i / 2) * sin(-angle) + y;
			}
			else
			{
				tmpX = (rad - (140 - i) / 2) * cos(angle) + x + 70;
				tmpY = (rad - (140 - i) / 2) * sin(angle) + y;
			}
		}

		glVertex2f(tmpX, tmpY);
	}

	glEnd();
}