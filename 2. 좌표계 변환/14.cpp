//	14. �̵� ȸ�� �����ϱ�
//		- ȭ�鿡 ���콺�� Ŭ���ϸ� �� �ڸ��� ������ ������ �׷�����
//			glut ���̺귯������ �����ϴ� 3���� ��ü�� �׷�����.
//			�ٸ� ��, �ٸ� ũ��� �׸���.
//		- �� ������ ������ �࿡ ���Ͽ� ȸ���ϸ� ���� �۾�����.
//			ũ�Ⱑ 0�� �Ǹ� �����ȴ�.
//		- �ٸ� ���� Ŭ���ϸ� �� �ٸ� ������ �׷����� ȸ���ϸ� ���� �۾�����.
//		- Ư�� Ű���带 ������ �������� �ݴ� �������� ȸ���Ѵ�.
//		- ���� ����� �Է��� ������ ��ӵȴ�.
//			�ִ� 20������ �׸����� �Ѵ�.

#include <GL/freeglut.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

typedef struct
{
	int type;							// ���� Ÿ��
	float r, g, b;						// ��
	float x, y;							// ��ġ
	int axis;							// ȸ����
	int rot;							// ȸ�� ����
	float shapesize;					// ���� ũ��

	double base, height;				// ����
	int slices, stacks;					// ����, ��
	double size;						// ����ü, ������
	double radius;						// ��
	double innerradius, outerradius;	// �䷯��
	int sides, rings;					// �䷯��
} Shape;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);
void TimerFunction(int);

vector<Shape> shape;
vector<Shape>::iterator iter;

int dir = 1;

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 14"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutKeyboardFunc(Keyboard);
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
	glMatrixMode(GL_MODELVIEW);

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		glLoadIdentity();
	
		glTranslatef(iter->x, iter->y, 0.0f);

		printf("%d %d\n", iter->type, iter->axis);

		if (iter->axis == 0)
			glRotatef(iter->rot, 1.0f, 0.0f, 0.0f);
		else if (iter->axis == 1)
			glRotatef(iter->rot, 0.0f, 1.0f, 0.0f);
		else if (iter->axis == 2)
			glRotatef(iter->rot, 0.0f, 0.0f, 1.0f);

		glScalef(iter->shapesize, iter->shapesize, iter->shapesize);

		glColor3f(iter->r, iter->g, iter->b);

		if(iter->type == 1)
			glutWireCone(iter->base, iter->height, iter->slices, iter->stacks);
		else if (iter->type == 2)
			glutWireCube(iter->size);
		else if (iter->type == 3)
			glutWireSphere(iter->radius, iter->slices, iter->stacks);
		else if (iter->type == 4)
			glutWireTorus(iter->innerradius, iter->outerradius, iter->sides, iter->rings);
		else if (iter->type == 5)
			glutWireTeapot(iter->size);
	}

	glFlush(); // ȭ�鿡 ����ϱ�
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
		dir *= -1;
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
	srand((unsigned int)time(NULL));

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Shape s;

		s.type = rand() % 5 + 1;
		s.r = (rand() % 256) / 256.0f;
		s.g = (rand() % 256) / 256.0f;
		s.b = (rand() % 256) / 256.0f;
		s.x = (float)(x - 400) / 400;
		s.y = (float)(300 - y) / 300;
		s.axis = rand() % 3;
		s.rot = 0;
		s.shapesize = 1.0f;

		if (s.type == 1)
		{
			s.base = (rand() % 3 + 1) / 10.0;
			s.height = (rand() % 3 + 1) / 10.0;
			s.slices = rand() % 10 + 10;
			s.stacks = rand() % 10 + 10;
		}
		else if (s.type == 3)
		{
			s.radius = (rand() % 3 + 1) / 10.0;
			s.slices = rand() % 10 + 10;
			s.stacks = rand() % 10 + 10;
		}
		else if (s.type == 4)
		{
			s.innerradius = (rand() % 6 + 5) / 100.0;
			s.outerradius = (rand() % 2 + 1) / 10.0;
			s.sides = rand() % 10 + 10;
			s.rings = rand() % 10 + 10;
		}
		else
		{
			s.size = (rand() % 5 + 1) / 10.0;
		}

		shape.push_back(s);

		if (shape.size() == 20) shape.erase(shape.begin());
	}
}

void TimerFunction(int value)
{
	for (iter = shape.begin(); iter != shape.end();)
	{
		iter->rot += 5 * dir;
		iter->shapesize -= 0.005f;

		if (iter->shapesize <= 0.0f)
			iter = shape.erase(iter);
		else
			++iter;
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}