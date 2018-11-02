#include <GL/freeglut.h>
#include <vector>
#include <iterator>
#include <time.h>
#include <iostream>
using namespace std;

//
typedef struct {
	float x, y, z;
	int dirX, dirY;
} Ball;

//
void SetupRC();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);

void Keyboard(unsigned char, int, int);
void Mouse(int, int);
void TimerFunction(int);

void DrawBigCube();
void MakeBall();
void DrawBall();
void DrawSmallCube();

//
int yRot;
float zRot, MoveX;
float zoom;

vector<Ball> ball;
vector<Ball>::iterator iter;

//
void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 26"); // ������ ���� (������ �̸�)
	SetupRC(); // ���� ���� �ʱ�ȭ �Լ�
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutKeyboardFunc(Keyboard);
	glutPassiveMotionFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glutMainLoop();
}

// �ʱ�ȭ �Լ�
void SetupRC()
{
	yRot = 0, zRot = 0.0f, MoveX = 9.9f;
	zoom = 0.0f;
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -12.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 12.0f);
	glTranslatef(0.0f, 0.0f, zoom);

	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	DrawBigCube();
	DrawBall();
	DrawSmallCube();

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

	case 'z':
		zoom += 0.3f;
		break;

	case 'Z':
		zoom -= 0.3f;
		break;

	case 'b': case 'B':
		MakeBall();
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void Mouse(int x, int y)
{
	if (x < 200)
	{
		zRot += 0.1f;
		if(MoveX > -9.9f && zRot > 0.0f)
			MoveX -= 0.05f;
	}
	else if (x > 600)
	{
		zRot -= 0.1f;
		if (MoveX < 9.9f && zRot < 0.0f)
			MoveX += 0.05f;
	}
}

void TimerFunction(int value)
{
	for (iter = ball.begin(); iter != ball.end(); ++iter)
	{
		iter->x += iter->dirX;
		iter->y -= iter->dirY;

		if (iter->x < -11.0f)
		{
			iter->x = -11.0f;
			iter->dirX *= -1;
		}
		else if (iter->x > 11.0f)
		{
			iter->x = 11.0f;
			iter->dirX *= -1;
		}
		else if (iter->y < -11.0f)
		{
			iter->y = -11.0f;
			iter->dirY *= -1;
		}
		else if (iter->y > 11.0f)
		{
			iter->y = 11.0f;
			iter->dirY *= -1;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawBigCube()
{
	glPushMatrix();
		// ��
		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-12.0f, 12.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-12.0f, -12.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(12.0f, -12.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(12.0f, 12.0f, 0.0f);
		glEnd();
		// ��
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(12.0f, 12.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(12.0f, -12.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(12.0f, -12.0f, -24.0f);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(12.0f, 12.0f, -24.0f);
		glEnd();
		// ��
		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(12.0f, 12.0f, -24.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(12.0f, -12.0f, -24.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-12.0f, -12.0f, -24.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-12.0f, 12.0f, -24.0f);
		glEnd();
		// ��
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-12.0f, 12.0f, -24.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-12.0f, -12.0f, -24.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-12.0f, -12.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-12.0f, 12.0f, 0.0f);
		glEnd();
		// ��
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-12.0f, 12.0f, -24.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-12.0f, 12.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(12.0f, 12.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(12.0f, 12.0f, -24.0f);
		glEnd();
		// �Ʒ�
		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-12.0f, -12.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-12.0f, -12.0f, -24.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(12.0f, -12.0f, -24.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(12.0f, -12.0f, 0.0f);
		glEnd();
	glPopMatrix();
}

void MakeBall()
{
	srand((unsigned int)time(NULL));

	Ball b;

	b.dirX = 1;
	b.dirY = 1;
	b.x = rand() % 16 - 8;
	b.y = rand() % 16 - 8;
	b.z = (rand() % 20 + 2) * -1;

	ball.push_back(b);

	if (ball.size() == 6) ball.erase(ball.begin());
}

void DrawBall()
{
	for (iter = ball.begin(); iter != ball.end(); ++iter)
	{
		glPushMatrix();
			glColor3f(0.95f, 0.38f, 0.65f);
			glTranslatef(iter->x, 0.0f, 0.0f);
			glTranslatef(0.0f, iter->y, 0.0f);
			glTranslatef(0.0f, 0.0f, iter->z);
			glutSolidSphere(1.0, 20, 20);
		glPopMatrix();
	}
}

void DrawSmallCube()
{
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -20.0f);
			glTranslatef(MoveX, 0.0f, 0.0f);
			glTranslatef(0.0f, -9.9f, 0.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glutSolidCube(4.0f);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -15.0f);
			glTranslatef(MoveX, 0.0f, 0.0f);
			glTranslatef(0.0f, -9.9f, 0.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glutSolidCube(4.0f);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -10.0f);
			glTranslatef(MoveX, 0.0f, 0.0f);
			glTranslatef(0.0f, -9.9f, 0.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glutSolidCube(4.0f);
		glPopMatrix();
	glPopMatrix();
}