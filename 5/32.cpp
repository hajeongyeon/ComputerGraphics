#include <GL/freeglut.h>
#include <iostream>
using namespace std;

#define RADIAN 0.0174532

void SetupRC();
GLvoid drawScene(GLvoid);
void Reshape(int w, int h);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void DrawPyramid(float, float, float);
void DrawMoon();

int degree;
float yRot;
bool nflight1, nflight2, isNormal;

GLfloat AmbientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat DiffuseLight1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat SpecularLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos1[] = { 10.0f, 10.0f, 0.0f, 1.0f };
GLfloat gray1[] = { 0.25f, 0.25f, 0.25f, 1.0f };

GLfloat DiffuseLight2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat SpecularLight2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos2[] = { -10.0f, 10.0f, 0.0f, 1.0f };
GLfloat gray2[] = { 0.25f, 0.25f, 0.25f, 1.0f };

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 32"); // ������ ���� (������ �̸�)
	SetupRC(); // ���� ���� �ʱ�ȭ �Լ�
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}

void SetupRC()
{
	degree = 0;
	yRot = 0.0f;
	nflight1 = false, nflight2 = false, isNormal = true;
}

GLvoid drawScene(GLvoid)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������, ���� ���� Ŭ���� �ϱ�

	glLoadIdentity();

	glTranslatef(0.0f, -10.0f, 0.0f);
	glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// ���� �ֺ���
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	// 1�� ����
	glPushMatrix();
		glTranslatef(lightPos1[0], lightPos1[1], lightPos1[2]);
		glutSolidSphere(1.0, 10, 10);
	glPopMatrix();

	if (nflight1)
	{
		// ������ ����ϵ��� ���� 
		glEnable(GL_LIGHTING);

		// ���� ����
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight1);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight1);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLight1);
		glMateriali(GL_FRONT, GL_SHININESS, 64);

		glEnable(GL_LIGHT0);
	}
	else
		glDisable(GL_LIGHT0);

	// 2�� ����
	glPushMatrix();
		glTranslatef(lightPos2[0], lightPos2[1], lightPos2[2]);
		glutSolidSphere(1.0, 10, 10);
	glPopMatrix();

	if (nflight2)
	{
		// ������ ����ϵ��� ���� 
		glEnable(GL_LIGHTING);

		// ���� ����
		glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight2);
		glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight2);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray2);
		glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLight2);
		glMateriali(GL_FRONT, GL_SHININESS, 64);

		glEnable(GL_LIGHT1);
	}
	else
		glDisable(GL_LIGHT1);

	// �ٴ�
	glPushMatrix();
		glScalef(1.0f, 0.0f, 1.0f);
		glutSolidCube(30.0f);
	glPopMatrix();

	// �Ƕ�̵�
	DrawPyramid(0, 15, 0);
	DrawPyramid(-12, 6, -12);
	DrawPyramid(12, 6, -12);
	DrawPyramid(-12, 6, 12);
	DrawPyramid(12, 6, 12);
	
	// ��
	DrawMoon();

	glutSwapBuffers(); // ��� ���
}

void Reshape(int w, int h)
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
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		if (nflight1) nflight1 = false;
		else nflight1 = true;
		break;

	case '2':
		if (nflight2) nflight2 = false;
		else nflight2 = true;
		break;

	case 'y':
		yRot++;
		break;

	case 'Y':
		yRot--;
		break;

	case 'a':
		for (int i = 0; i < 4; ++i)
		{
			AmbientLight[i] += 0.1f;
			AmbientLight[i] += 0.1f;
		}
		break;

	case 'A':
		for (int i = 0; i < 4; ++i)
		{
			AmbientLight[i] -= 0.1f;
			AmbientLight[i] -= 0.1f;
		}
		break;

	case 'd':
		for (int i = 0; i < 4; ++i)
		{
			DiffuseLight1[i] += 0.1f;
			DiffuseLight2[i] += 0.1f;
		}
		break;

	case 'D':
		for (int i = 0; i < 4; ++i)
		{
			DiffuseLight1[i] -= 0.1f;
			DiffuseLight2[i] -= 0.1f;
		}
		break;

	case 's':
		for (int i = 0; i < 4; ++i)
		{
			SpecularLight1[i] += 0.1f;
			SpecularLight2[i] += 0.1f;
		}
		break;

	case 'S':
		for (int i = 0; i < 4; ++i)
		{
			SpecularLight1[i] -= 0.1f;
			SpecularLight2[i] -= 0.1f;
		}
		break;

	case 'o': case 'O':
		if (!isNormal) isNormal = true;
		else isNormal = false;
		break;

	case 'r': case 'R':
		SetupRC();
		break;

	case 'q': case 'Q':
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	degree += 20;

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawPyramid(float x, float y, float z)
{
	if (!isNormal)
	{
		glEnable(GL_NORMALIZE);
		glEnable(GL_AUTO_NORMAL);
	}

	glPushMatrix();
		// �ٴ�
		glBegin(GL_POLYGON);
		glVertex3f(x - 3, 0, z - 3);
		glVertex3f(x + 3, 0, z - 3);
		glVertex3f(x + 3, 0, z + 3);
		glVertex3f(x - 3, 0, z + 3);
		glEnd();

		// ��
		glBegin(GL_POLYGON);
		if (!isNormal) glNormal3f(18, 0, 0);
		glVertex3f(x - 3, 0, z - 3);
		glVertex3f(x + 3, 0, z - 3);
		glVertex3f(x, y, z);
		glEnd();

		glBegin(GL_POLYGON);
		if (!isNormal) glNormal3f(0, 0, 18);
		glVertex3f(x + 3, 0, z - 3);
		glVertex3f(x + 3, 0, z + 3);
		glVertex3f(x, y, z);
		glEnd();

		glBegin(GL_POLYGON);
		if (!isNormal) glNormal3f(18, 0, 0);
		glVertex3f(x + 3, 0, z + 3);
		glVertex3f(x - 3, 0, z + 3);
		glVertex3f(x, y, z);
		glEnd();

		glBegin(GL_POLYGON);
		if (!isNormal) glNormal3f(0, 0, 18);
		glVertex3f(x - 3, 0, z + 3);
		glVertex3f(x - 3, 0, z - 3);
		glVertex3f(x, y, z);
		glEnd();
	glPopMatrix();
}

void DrawMoon()
{
	glPushMatrix();
		glTranslatef(5.0f * cos(degree * RADIAN), 15, 5.0f * sin(degree * RADIAN));
		glutSolidSphere(2.0, 10, 10);
	glPopMatrix();
}