#include <GL/freeglut.h>
#include <iostream>
using namespace std;

#define PI 3.141592
#define RADIAN 0.0174532

//
int MainMenu, DepthMenu, CullingMenu, ShadingMenu, UpOpenMenu, FrontOpenMenu;

int yRot;

bool IsDepthTest, IsCulling, IsShading, IsUpOpen, IsFrontOpen;

int UpRot, FrontRot;
float MoveZ, sRotz, MoveY;		// Ball
float SpringY;

//
void SetupRC();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);

void MenuFunc(int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void DrawCube();
void DrawSpring();
void DrawBall();

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 25"); // ������ ���� (������ �̸�)
	SetupRC(); // ���� ���� �ʱ�ȭ �Լ�

	DepthMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("on", 11);
	glutAddMenuEntry("off", 12);
	CullingMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("on", 21);
	glutAddMenuEntry("off", 22);
	ShadingMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("flat", 31);
	glutAddMenuEntry("smooth", 32);
	UpOpenMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("open", 41);
	glutAddMenuEntry("close", 42);
	FrontOpenMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("open", 51);
	glutAddMenuEntry("close", 52);
	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Hidden Surface Delete", DepthMenu);
	glutAddSubMenu("Culling", CullingMenu);
	glutAddSubMenu("Shading", ShadingMenu);
	glutAddSubMenu("Up Surface", UpOpenMenu);
	glutAddSubMenu("Front Surface", FrontOpenMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}

// �ʱ�ȭ �Լ�
void SetupRC()
{
	yRot = 0;

	IsDepthTest = true, IsCulling = false, IsShading = false, IsUpOpen = false, IsFrontOpen = false;

	UpRot = 0, FrontRot = 0;
	MoveZ = 0.0f, sRotz = 0.0f, MoveY = 0.0f;
	SpringY = 1.0f;
}

// �޴�
void MenuFunc(int button)
{
	switch (button)
	{
	case 11:
		IsDepthTest = true;
		break;

	case 12:
		IsDepthTest = false;
		break;

	case 21:
		IsCulling = true;
		break;

	case 22:
		IsCulling = false;
		break;

	case 31:
		IsShading = true;
		break;

	case 32:
		IsShading = false;
		break;

	case 41:
		IsUpOpen = true;
		break;

	case 42:
		IsUpOpen = false;
		break;

	case 51:
		IsFrontOpen = true;
		break;

	case 52:
		IsFrontOpen = false;
		break;
	}

	glutPostRedisplay();
}


// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (IsDepthTest) glEnable(GL_DEPTH_TEST);
	else glDisable(GL_DEPTH_TEST);

	if (IsCulling) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	if (IsShading) glShadeModel(GL_FLAT);
	else glShadeModel(GL_SMOOTH);

	glLoadIdentity();

	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	DrawCube();
	DrawSpring();
	DrawBall();

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
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'y':
		yRot += 3;
		break;

	case 'Y':
		yRot -= 3;
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	//
	if (IsUpOpen && FrontRot == 0)
	{
		if(UpRot < 90) UpRot += 5;
		else UpRot = 90;
	}
	if (!IsUpOpen && FrontRot == 0 && UpRot > 0)
	{
		if (MoveY <= 0) UpRot -= 5;
		else
		{
			MoveY--;
			SpringY -= 0.3f;
		}
	}
	if (IsFrontOpen && UpRot == 0)
	{
		if (FrontRot > -90) FrontRot -= 5;
		else FrontRot = -90;
	}
	if (!IsFrontOpen && UpRot == 0 && FrontRot < 0)
	{
		if (MoveZ <= 0) FrontRot += 5;
		else
		{
			sRotz -= 5;
			MoveZ -= 2 * PI * 2 / 72;
		}
	}

	if (IsFrontOpen && FrontRot == -90)
	{
		if (MoveZ >= 7)
		{
			MoveZ = 7;
			sRotz = 210;
		}
		else
		{
			sRotz += 5;
			MoveZ += 2 * PI * 2 / 72;
		}
	}

	if (IsUpOpen && UpRot == 90)
	{
		if (MoveY >= 8) MoveY = 8;
		else
		{
			MoveY++;
			SpringY += 0.3f;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawCube()
{
	glPushMatrix();
		// ��
		glPushMatrix();
			glTranslatef(3.0f, 3.0f, 0.0f);
			glRotatef(FrontRot, 1.0f, 0.0f, 0.0f);
			glTranslatef(-3.0f, -3.0f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-3.0f, 3.0f, 0.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-3.0f, -3.0f, 0.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(3.0f, -3.0f, 0.0f);
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(3.0f, 3.0f, 0.0f);
			glEnd();
		glPopMatrix();
		// ��
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(3.0f, 3.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(3.0f, -3.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(3.0f, -3.0f, -6.0f);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(3.0f, 3.0f, -6.0f);
		glEnd();
		// ��
		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(3.0f, 3.0f, -6.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(3.0f, -3.0f, -6.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-3.0f, -3.0f, -6.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-3.0f, 3.0f, -6.0f);
		glEnd();
		// ��
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-3.0f, 3.0f, -6.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-3.0f, -3.0f, -6.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-3.0f, -3.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-3.0f, 3.0f, 0.0f);
		glEnd();
		// ��
		glPushMatrix();
			glTranslatef(-3.0f, 3.0f, -6.0f);
			glRotatef(-UpRot, 1.0f, 0.0f, 0.0f);
			glTranslatef(3.0f, -3.0f, 6.0f);

			glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-3.0f, 3.0f, -6.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-3.0f, 3.0f, 0.0f);
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(3.0f, 3.0f, 0.0f);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(3.0f, 3.0f, -6.0f);
			glEnd();
		glPopMatrix();
		// �Ʒ�
		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-3.0f, -3.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-3.0f, -3.0f, -6.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(3.0f, -3.0f, -6.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(3.0f, -3.0f, 0.0f);
		glEnd();
	glPopMatrix();
}

void DrawSpring()
{
	glPushMatrix();
		GLfloat z = 0.0f;

		glTranslatef(0.0f, 0.0f, -3.0f);
		glTranslatef(0.0f, -2.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

		glColor3f(0.5f, 0.5f, 0.5f);
		glBegin(GL_LINE_STRIP);

		for (float theta = 0.0f; theta <= 30.0f; theta += 0.1f)
		{
			glVertex3f(2 * sin(theta), 2 * cos(theta), z);

			z += 0.01f * SpringY;
		}

		glEnd();
	glPopMatrix();
}

void DrawBall()
{
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -3.0f);
		glTranslatef(0.0f, MoveY, 0.0f);
		glTranslatef(0.0f, 0.0f, MoveZ);
		glRotatef(sRotz, 1.0f, 0.0f, 0.0f);

		glColor3f(0.5f, 0.5f, 0.5f);
		glutWireSphere(2.0, 10, 10);
	glPopMatrix();
}