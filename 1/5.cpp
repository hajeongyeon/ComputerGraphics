#include <GL/freeglut.h>
#include "456.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char, int, int);
void SpecialKeyboard(int, int, int);
void Mouse(int, int, int, int);
void TimerFunction(int);

void DrawRectangle(int, int, int, int);
void DrawTriangle(int, int, int);
void Collision(Shape*);

vector<Shape> shape;
vector<Shape>::iterator iter;
ShapeType type = RECTANGLE;

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 5"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
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

	srand((unsigned int)time(NULL));

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		R = (rand() % 256) / 256.0f;
		G = (rand() % 256) / 256.0f;
		B = (rand() % 256) / 256.0f;

		if ((iter->type) == RECTANGLE)
			DrawRectangle(iter->x, iter->y, iter->width, iter->length);
		else
			DrawTriangle(iter->x, iter->y, iter->length);
	}

	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 0, 600, -1, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 't':
		type = TRIANGLE;
		break;

	case 'r':
		type = RECTANGLE;
		break;
	}
}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		for (iter = shape.begin(); iter != shape.end(); ++iter)
		{
			if(iter->speed < 11)
				++(iter->speed);
		}
	}
	else if (key == GLUT_KEY_DOWN)
	{
		for (iter = shape.begin(); iter != shape.end(); ++iter)
		{
			if (iter->speed > 1)
				--(iter->speed);
		}
	}
}

void Mouse(int button, int state, int x, int y)
{
	srand((unsigned int)time(NULL));

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Shape s;

		int X = rand() % 2;
		int Y = rand() % 2;

		s.x = x;
		s.y = 600 - y;
		s.width = rand() % 40 + 30;
		s.length = rand() % 40 + 30;
		s.shapeSize = 1;
		if (X == 1) s.xdir = 1;
		else s.xdir = -1;
		if (Y == 1) s.ydir = 1;
		else s.ydir = -1;
		s.speed = rand() % 10 + 1;
		s.type = type;

		shape.push_back(s);

		if (shape.size() == 11) shape.erase(shape.begin());
	}
}

void TimerFunction(int value)
{
	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		iter->width += iter->shapeSize;
		iter->length += iter->shapeSize;

		if (iter->width < 30 || iter->width > 70 || iter->length < 30 || iter->length > 70)
			iter->shapeSize *= -1;
	}

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		iter->x += (iter->speed * iter->xdir);
		iter->y += (iter->speed * iter->ydir);
	}

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		Collision(&(*iter));
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawRectangle(int x, int y, int width, int length)
{
	glColor3f(R, G, B);

	glRectf(x - width, y - length, x + width, y + length);
}

void DrawTriangle(int x, int y, int length)
{
	glColor3f(R, G, B);
	glBegin(GL_TRIANGLES);

	glVertex2f(x, y + length);
	glVertex2f(x - length, y - length);
	glVertex2f(x + length, y - length);

	glEnd();
}

void Collision(Shape* shape)
{
	if (shape->type == RECTANGLE)
	{
		if ((shape->x - shape->width) <= 0)
			shape->xdir = 1;
		if ((shape->x + shape->width) >= 800)
			shape->xdir = -1;
		if ((shape->y - shape->length) <= 0)
			shape->ydir = 1;
		if ((shape->y + shape->length) >= 600)
			shape->ydir = -1;
	}
	else
	{
		if ((shape->x - shape->length) <= 0)
			shape->xdir = 1;
		if ((shape->x + shape->length) >= 800)
			shape->xdir = -1;
		if ((shape->y - shape->length) <= 0)
			shape->ydir = 1;
		if ((shape->y + shape->length) >= 600)
			shape->ydir = -1;
	}
}