#include <GL/freeglut.h>
#include <iostream>
using namespace std;

#define RADIAN 0.0174532

void SetupRC();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void MenuFunc(int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void DrawSun();
void DrawEarth();
void DrawJupiter();
void DrawNeptune();

//
bool isSolid;
int degree;
float EarthX, EarthZ;
float JupiterX, JupiterZ;

void main(int argc, char *argv[])
{
	int SolidMenu, WireMenu;

	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 800); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 17"); // ������ ���� (������ �̸�)
	SetupRC(); // ���� ���� �ʱ�ȭ �Լ�

	glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Solid", 1);
	glutAddMenuEntry("Wire", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glutMainLoop();
}

// �ʱ�ȭ �Լ�
void SetupRC()
{
	isSolid = true;
	degree = 0;
	EarthX = 10.0f, EarthZ = 0.0f;
}

// �޴�
void MenuFunc(int button)
{
	switch (button)
	{
	case 1:
		isSolid = true;
		break;

	case 2:
		isSolid = false;
		break;
	}

	glutPostRedisplay();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawSun();
	DrawEarth();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// ���� ����
	gluPerspective(60.0f, w / h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -30.0);

	// ���� ����
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);

	// ���� ��ȯ: ī�޶��� ��ġ ���� (�ʿ��� ���, �ٸ� ���� ���� ����)
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	default:
		break;
	}

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	EarthX = 10.0f * cos(degree * RADIAN);
	EarthZ = 10.0f * sin(degree * RADIAN);

	degree += 5;

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawSun()
{
	glPushMatrix();
		glColor3f(0.85f, 0.0f, 0.0f);
		if (isSolid)
			glutSolidSphere(3.0, 20.0, 20.0);
		else
		{
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glutWireSphere(3.0, 20.0, 20.0);
		}
	glPopMatrix();
}

void DrawEarth()
{
	glPushMatrix();
		glColor3f(0.0f, 0.85f, 0.0f);
		glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
	
		// �˵�
		glPushMatrix();
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < 360; i++)
			{
				float angle = i * RADIAN;
				glVertex3f(10.0f * cos(angle), 0.0f, 10.0f * sin(angle));
			}
			glEnd();
		glPopMatrix();
	
		// �༺
		glPushMatrix();
			glTranslatef(EarthX, 0.0f, EarthZ);
			if (isSolid)
			{
				glutSolidSphere(1.5, 20.0, 20.0);
			}
			else
			{
				glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
				glutWireSphere(1.5, 20.0, 20.0);
			}
		glPopMatrix();
	glPopMatrix();
}

void DrawJupiter()
{
}

void DrawNeptune()
{
}