#include <GL/freeglut.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <iterator>
#include "1618.h"
using namespace std;

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 16"); // ������ ���� (������ �̸�)
	SetupRC(); // ���� ���� �ʱ�ȭ �Լ�
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}

// �ʱ�ȭ �Լ�
void SetupRC()
{
	shapetype = Sphere;
	type = 1;

	AllrotX = 0.0f;
	AllrotY = 0.0f;
	AllrotZ = 0.0f;

	LrotX = 0.0f;
	LrotY = 0.0f;
	LrotZ = 0.0f;

	RrotX = 0.0f;
	RrotY = 0.0f;
	RrotZ = 0.0f;
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ��ǥ��
	glLoadIdentity();
	AllRotation();
	glBegin(GL_LINES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glEnd();

	// Plane
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -10.0f, 10.0f);
		glScalef(1.0f, 0.1f, 1.0f);
		glutSolidCube(30.0f);
	glPopMatrix();

	// ����
	glPushMatrix();
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 0.0f);
			glTranslatef(-8.0f, -5.0f, 0.0f);
			LRotation();
			DrawSolidShape();
		glPopMatrix();
		glPushMatrix();
			glColor3f(1.0f, 0.0f, 1.0f);
			glTranslatef(8.0f, -5.0f, 0.0f);
			RRotation();
			DrawWireShape();
		glPopMatrix();
	glPopMatrix();

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
	case 'x': case 'X':
		AllrotX++;
		LrotX += 5;
		RrotX += 5;
		break;

	case 'y': case 'Y':
		AllrotY++;
		LrotY += 5;
		RrotY += 5;
		break;

	case 'z': case 'Z':
		AllrotZ++;
		LrotZ += 5;
		RrotZ += 5;
		break;

	case 'l': case 'L':
		LrotY += 5;
		break;

	case 'r': case 'R':
		RrotY += 5;
		break;

	case 'o': case 'O':
		LrotY += 5;
		RrotY += 5;
		break;

	case 'c': case 'C':
		++type;

		if (type == 1)
			shapetype = Sphere;
		else if (type == 2)
			shapetype = Cube;
		else if (type == 3)
			shapetype = Cone;
		else if (type == 4)
		{
			shapetype = Teapot;
			type = 0;
		}

		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawSolidShape()
{
	switch (shapetype)
	{
	case Sphere:
		glutSolidSphere(5.0, 20.0, 20.0);
		break;

	case Cube:
		glutSolidCube(5.0);
		break;

	case Cone:
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		glutSolidCone(5.0, 5.0, 20.0, 20.0);
		break;

	case Teapot:
		glutSolidTeapot(5.0);
		break;
	}
}

void DrawWireShape()
{
	switch (shapetype)
	{
	case Sphere:
		glutWireSphere(5.0, 20.0, 20.0);
		break;

	case Cube:
		glutWireCube(5.0);
		break;

	case Cone:
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		glutWireCone(5.0, 5.0, 20.0, 20.0);
		break;

	case Teapot:
		glutWireTeapot(5.0);
		break;
	}
}

void AllRotation()
{
	glRotatef(AllrotX, 1.0f, 0.0f, 0.0f);
	glRotatef(AllrotY, 0.0f, 1.0f, 0.0f);
	glRotatef(AllrotZ, 0.0f, 0.0f, 1.0f);
}

void LRotation()
{
	glRotatef(LrotX, 1.0f, 0.0f, 0.0f);
	glRotatef(LrotY, 0.0f, 1.0f, 0.0f);
	glRotatef(LrotZ, 0.0f, 0.0f, 1.0f);
}

void RRotation()
{
	glRotatef(RrotX, 1.0f, 0.0f, 0.0f);
	glRotatef(RrotY, 0.0f, 1.0f, 0.0f);
	glRotatef(RrotZ, 0.0f, 0.0f, 1.0f);
}