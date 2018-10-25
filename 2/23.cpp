#include <GL/freeglut.h>
#include <iostream>
using namespace std;

//
int MainMenu, DepthMenu, CullingMenu, ShadingMenu, UpOpenMenu, FrontOpenMenu;

int yRot;

bool IsDepthTest, IsCulling, IsShading, IsUpOpen, IsFrontOpen;

//
void SetupRC();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);

void MenuFunc(int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void DrawCube();

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 23"); // ������ ���� (������ �̸�)
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
	glutAddMenuEntry("yes", 41);
	glutAddMenuEntry("no", 42);
	FrontOpenMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("yes", 51);
	glutAddMenuEntry("no", 52);
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

	IsDepthTest = true, IsCulling = true, IsShading = false, IsUpOpen = false, IsFrontOpen = false;
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
		yRot++;
		break;

	case 'Y':
		yRot--;
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

void DrawCube()
{
	glBegin(GL_QUADS);
	// ��
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-3.0f, 3.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-3.0f, -3.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(3.0f, -3.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(3.0f, 3.0f, 0.0f);
	// ��
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(3.0f, 3.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(3.0f, -3.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(3.0f, -3.0f, -6.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(3.0f, 3.0f, -6.0f);
	// ��
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(3.0f, 3.0f, -6.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(3.0f, -3.0f, -6.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-3.0f, -3.0f, -6.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-3.0f, 3.0f, -6.0f);
	// ��
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-3.0f, 3.0f, -6.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-3.0f, -3.0f, -6.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-3.0f, -3.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-3.0f, 3.0f, 0.0f);
	// ��
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-3.0f, 3.0f, -6.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-3.0f, 3.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(3.0f, 3.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(3.0f, 3.0f, -6.0f);
	// �Ʒ�
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-3.0f, -3.0f, -6.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-3.0f, -3.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(3.0f, -3.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(3.0f, -3.0f, -6.0f);
	glEnd();
}