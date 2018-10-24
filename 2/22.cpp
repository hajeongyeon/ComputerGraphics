#include <GL/freeglut.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <iterator>
#include "19to22.h"
using namespace std;

vector<Shape> shape;
vector<Shape>::iterator iter;

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 22"); // ������ ���� (������ �̸�)
	SetupRC(); // ���� ���� �ʱ�ȭ �Լ�
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
	radius = 2.0;
	MoveX = 14.0, MoveY = 0.0, MoveZ = 0.0;

	sRotx = 0.0, sRoty = 0.0, sRotz = 0.0;

	yRot = 0;
	zoom = 0.0f;

	BMoveX = 0.0f, BMoveZ = 0.0f, BRoty = 0.0f;
	MRotx = 0.0f, MRoty = 0.0f;
	TRotx = 0.0f, TRotz = 0.0f;
	dir = 0;

	SphereDir = 0, LeafDir = 1, LeftLegDir = 1, RightLegDir = -1, SwingDir = 1, PushDir = 1;
	LeafRadius = 3.0;

	Conveyor = 0.0f, LeftLeg = 0.0f, RightLeg = 0.0f, Swing = 0.0f, Push = 2.0f;

	quadratic = gluNewQuadric();
	propeller = 0;
	airplaneX = 15.0f, airplaneZ = 0.0f;
	airplanedegree = 0;

	airplaneRot = 0;
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0.0f, -10.0f, -20.0f);
	glTranslatef(0.0f, 0.0f, -zoom);
	glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// Plane
	glPushMatrix();
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glScalef(1.0f, 0.0f, 1.0f);
			glutSolidCube(30.0f);
		glPopMatrix();
		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.49f);
			glBegin(GL_TRIANGLES);
			glVertex3f(15.0f, 0.01f, 15.0f); // v1 
			glVertex3f(15.0f, 0.01f, 0.0f); // v2
			glVertex3f(0.0f, 0.01f, 15.0f); // v3 
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.52f, 0.89f, 0.49f);
			glBegin(GL_TRIANGLES);
			glVertex3f(-15.0f, 0.01f, 15.0f); // v1 
			glVertex3f(0.0f, 0.01f, 15.0f); // v2
			glVertex3f(-15.0f, 0.01f, 0.0f); // v3 
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.64f, 0.4f, 1.0f);
			glBegin(GL_TRIANGLES);
			glVertex3f(-15.0f, 0.01f, -15.0f); // v1 
			glVertex3f(-15.0f, 0.01f, 0.0f); // v2
			glVertex3f(0.0f, 0.01f, -15.0f); // v3 
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.4f, 0.6f, 1.0f);
			glBegin(GL_TRIANGLES);
			glVertex3f(15.0f, 0.01f, -15.0f); // v1 
			glVertex3f(0.0f, 0.01f, -15.0f); // v2
			glVertex3f(15.0f, 0.01f, 0.0f); // v3 
			glEnd();
		glPopMatrix();
	glPopMatrix();

	srand((unsigned int)time(NULL));

	// ��
	glPushMatrix();
		glTranslatef(0.0f, 2.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		XRoll();
		ZRoll();
		glutWireSphere(radius, 10.0, 15.0);
	glPopMatrix();

	// ũ����
	if (MRotx >= 90.0f) MRotx = 90.0f;
	else if (MRotx <= -90.0f) MRotx = -90.0f;

	if (TRotx >= 90.0f) TRotx = 90.0f;
	else if (TRotx <= -90.0f) TRotx = -90.0f;

	if (TRotz >= 90.0f) TRotz = 90.0f;
	else if (TRotz <= -90.0f) TRotz = -90.0f;

	if (BMoveX > 13 && dir == 0) dir = 1;
	else if (BMoveX < -13 && dir == 1) dir = 0;
	else if (BMoveZ > 13 && dir == 2) dir = 3;
	else if (BMoveZ < -13 && dir == 3) dir = 2;

	glPushMatrix();
	if (dir == 0 || dir == 1)
	{
		glTranslatef(BMoveX, 0.0f, BMoveZ);
		glRotatef(BRoty, 0.0f, 1.0f, 0.0f);
		BottomBody();
		//
		glPushMatrix();
			glTranslatef(BMoveX, 6.0f, BMoveZ);
			glRotatef(MRotx, 1.0f, 0.0f, 0.0f);
			glTranslatef(-BMoveX, -6.0f, -BMoveZ);
			glRotatef(MRoty, 0.0f, 1.0f, 0.0f);
			MiddleBody();
			//
			glPushMatrix();
				glTranslatef(BMoveX, 13.5f, BMoveZ);
				glRotatef(TRotx, 1.0f, 0.0f, 0.0f);
				glTranslatef(-BMoveX, -13.5f, -BMoveZ);
				glTranslatef(0.0f, 13.5f, 0.0f);
				glRotatef(TRotz, 0.0f, 0.0f, 1.0f);
				glTranslatef(-0.0f, -13.5f, 0.0f);
				TopBody();
			glPopMatrix();
		glPopMatrix();
	}
	else if (dir == 2 || dir == 3)
	{
		glTranslatef(BMoveX, 0.0f, BMoveZ);
		glRotatef(BRoty, 0.0f, 1.0f, 0.0f);
		BottomBody();
		//
		glPushMatrix();
			glTranslatef(BMoveX, 6.0f, 0.0f);
			glRotatef(MRotx, 1.0f, 0.0f, 0.0f);
			glTranslatef(-BMoveX, -6.0f, 0.0f);
			glRotatef(MRoty, 0.0f, 1.0f, 0.0f);
			MiddleBody();
			//
			glPushMatrix();
				glTranslatef(BMoveX, 13.5f, 0.0f);
				glRotatef(TRotx, 1.0f, 0.0f, 0.0f);
				glTranslatef(-BMoveX, -13.5f, 0.0f);
				glTranslatef(0.0f, 13.5f, 0.0f);
				glRotatef(TRotz, 0.0f, 0.0f, 1.0f);
				glTranslatef(-0.0f, -13.5f, 0.0f);
				TopBody();
			glPopMatrix();
		glPopMatrix();
	}
	glPopMatrix();

	// ü����
	DrawTree();
	DrawRunningMachine();
	DrawPullUpBar();
	DrawBenchPress();

	// �����
	DrawAirplane();

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
	case 'y': case 'Y':
		yRot++;
		break;

	case '+':
		zoom -= 0.1f;
		break;

	case '-':
		zoom += 0.1f;
		break;

	case 'i': case 'I':
		SetupRC();
		break;

		// �Ʒ� ��ü y�� ȸ��
	case '1':
		BRoty += 3;
		break;

		// �߰� ��ü x�� ȸ�� (��)
	case '2':
		MRotx += 1;
		break;

		// �߰� ��ü x�� ȸ�� (��)
	case '3':
		MRotx -= 1;
		break;

		// �߰� ��ü y�� ȸ�� (��)
	case '4':
		MRoty += 1;
		break;

		// �߰� ��ü y�� ȸ�� (��)
	case '5':
		MRoty -= 1;
		break;

		// �� ��ü x�� ȸ�� (��)
	case '6':
		TRotx += 1;
		break;

		// �� ��ü x�� ȸ�� (��)
	case '7':
		TRotx -= 1;
		break;

		// �� ��ü z�� ȸ�� (��)
	case '8':
		TRotz += 1;
		break;

		// �� ��ü z�� ȸ�� (��)
	case '9':
		TRotz -= 1;
		break;

	case 'm': case 'M':
		airplaneRot++;
		break;

	case 'l': case 'L':
		airplaneRot--;
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	//
	if (dir == 0) BMoveX += 0.5f;
	else if (dir == 1) BMoveX -= 0.5f;
	else if (dir == 2) BMoveZ += 0.5f;
	else if (dir == 3) BMoveZ -= 0.5f;

	//
	if (SphereDir == 0)
	{
		sRotx += 5;
		MoveX += 2 * PI * radius / 72;
	}
	else if (SphereDir == 1)
	{
		sRotx -= 5;
		MoveX -= 2 * PI * radius / 72;
	}
	else if (SphereDir == 2)
	{
		sRotz += 5;
		MoveZ += 2 * PI * radius / 72;
	}
	else if (SphereDir == 3)
	{
		sRotz -= 5;
		MoveZ -= 2 * PI * radius / 72;
	}

	//
	LeafRadius += 0.1 * LeafDir;
	if (LeafRadius >= 4.0 || LeafRadius <= 3.0) LeafDir *= -1;

	//
	Conveyor += 2.0f;

	LeftLeg += 4.0f * LeftLegDir;
	if (LeftLeg >= 20.0f || LeftLeg <= -20.0f) LeftLegDir *= -1;
	RightLeg += 4.0f * RightLegDir;
	if (RightLeg >= 20.0f || RightLeg <= -20.0f) RightLegDir *= -1;

	//
	Swing += 3.0f * SwingDir;
	if (Swing >= 70.0f || Swing <= -70.0f) SwingDir *= -1;

	//
	Push += 0.1f * PushDir;
	if (Push >= 4.0f || Push <= 2.0f) PushDir *= -1;

	Collide();
	
	//
	propeller += 8;

	airplaneX = 15.0f * cos(airplanedegree * RADIAN);
	airplaneZ = 15.0f * sin(airplanedegree * RADIAN);

	airplanedegree--;

	//
	if (checktime >= 10)
	{
		Shape s;
		s.MoveZ = 7.0f;
		s.SphereSize = 0.8f;

		shape.push_back(s);

		if (shape.size() == 4) shape.erase(shape.begin());

		checktime = 0;
	}

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		iter->MoveZ += 0.5f;
		iter->SphereSize -= 0.02f;
	}

	checktime++;

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void XRoll()
{
	if (MoveX > 14.0) SphereDir = 1;
	else if (MoveX < -14.0) SphereDir = 0;

	glTranslatef(0.0f, 0.0f, MoveX);
	glRotatef(sRotx, 1.0f, 0.0f, 0.0f);
}

void ZRoll()
{
	if (MoveZ > 14.0) SphereDir = 3;
	else if (MoveZ < -14.0) SphereDir = 2;

	glTranslatef(MoveZ, 0.0f, 0.0f);
	glRotatef(-sRotz, 0.0f, 0.0f, 1.0f);
}

void BottomBody()
{
	glPushMatrix();
		glTranslatef(0.0f, 4.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidCube(5.0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(5.0);
	glPopMatrix();
}

void MiddleBody()
{
	glPushMatrix();
		glTranslatef(0.0f, 10.0f, 0.0f);
		glScalef(0.3f, 1.0f, 0.3f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glutSolidCube(7.0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(7.0);
	glPopMatrix();
}

void TopBody()
{
	glPushMatrix();
		glTranslatef(0.0f, 15.0f, 0.0f);
		glScalef(0.1f, 0.5f, 0.1f);
		glColor3f(0.0f, 1.0f, 1.0f);
		glutSolidCube(7.0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(7.0);
	glPopMatrix();
}

void DrawTree()
{
	glPushMatrix();
		glTranslatef(13.0f, 0.0f, 13.0f);
		// ���
		glPushMatrix();
			glTranslatef(0.0f, 4.0f, 0.0f);
			glScalef(0.2f, 1.0f, 0.2f);
			glColor3f(0.6f, 0.23f, 0.02f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();
		// Ǯ
		glPushMatrix();
			glTranslatef(0.0f, 9.0f, 0.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glutWireSphere(LeafRadius, 10.0, 10.0);
		glPopMatrix();
	glPopMatrix();
}

void DrawRunningMachine()
{
	glPushMatrix();
		glTranslatef(-11.0f, 0.0f, 12.0f);

		// �ٴ�
		glPushMatrix();
			glScalef(0.8f, 0.1f, 0.5f);
			glColor3f(0.5f, 0.5f, 0.5f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();

		// ���
		glPushMatrix();
			glTranslatef(-2.5f, 2.0f, 1.5f);
			glScalef(0.05f, 0.8f, 0.05f);
			glColor3f(0.5f, 0.5f, 0.5f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-2.5f, 2.0f, -1.5f);
			glScalef(0.05f, 0.8f, 0.05f);
			glColor3f(0.5f, 0.5f, 0.5f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-2.0f, 4.6f, 0.0f);
			glScalef(0.2f, 0.1f, 0.5f);
			glColor3f(0.5f, 0.5f, 0.5f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();

		// �����̾�
		glPushMatrix();
			glScalef(0.25f, 0.05f, 0.5f);
			glRotatef(Conveyor, 0.0f, 0.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireTorus(5.0, 10.0, 20.0, 20.0);
		glPopMatrix();

		// �ٸ�
		glPushMatrix();
			glTranslatef(0.0f, 4.5f, 0.0f);
			glRotatef(LeftLeg, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f, -4.5f, 0.0f);
			glTranslatef(0.0f, 2.0f, 0.4f);
			glScalef(0.05f, 0.3f, 0.05f);
			glColor3f(0.98f, 0.87f, 0.83f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 4.5f, 0.0f);
			glRotatef(RightLeg, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f, -4.5f, 0.0f);
			glTranslatef(0.0f, 2.0f, -0.4f);
			glScalef(0.05f, 0.3f, 0.05f);
			glColor3f(0.98f, 0.87f, 0.83f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();
	glPopMatrix();
}

void DrawPullUpBar()
{
	glPushMatrix();
		glTranslatef(-13.5f, 4.0f, -12.0f);

		// ö��
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, 2.5f);
			glScalef(0.05f, 1.2f, 0.05f);
			glColor3f(1.0f, 0.36f, 0.0f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -2.5f);
			glScalef(0.05f, 1.2f, 0.05f);
			glColor3f(1.0f, 0.36f, 0.0f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 4.0f, 0.0f);
			glScalef(0.05f, 0.1f, 0.8f);
			glColor3f(1.0f, 0.36f, 0.0f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();

		// ���
		glPushMatrix();
			glTranslatef(0.0f, 4.0f, 0.0f);
			glRotatef(Swing, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f, -4.0f, 0.0f);

			// ��
			glPushMatrix();
				glTranslatef(0.0f, 2.0f, 0.0f);
				glScalef(0.1f, 0.1f, 0.1f);
				glColor3f(0.98f, 0.87f, 0.83f);
				glutSolidCube(7.0);
				glColor3f(0.0f, 0.0f, 0.0f);
				glutWireCube(7.0);
			glPopMatrix();

			// ��
			glPushMatrix();
				glTranslatef(0.0f, 2.5f, -0.8f);
				glScalef(0.05f, 0.35f, 0.05f);
				glColor3f(0.98f, 0.87f, 0.83f);
				glutSolidCube(7.0);
				glColor3f(0.0f, 0.0f, 0.0f);
				glutWireCube(7.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 2.5f, 0.8f);
				glScalef(0.05f, 0.35f, 0.05f);
				glColor3f(0.98f, 0.87f, 0.83f);
				glutSolidCube(7.0);
				glColor3f(0.0f, 0.0f, 0.0f);
				glutWireCube(7.0);
			glPopMatrix();

			// ����
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, 0.0f);
				glScalef(0.1f, 0.4f, 0.3f);
				glColor3f(0.5f, 0.5f, 1.0f);
				glutSolidCube(7.0);
				glColor3f(0.0f, 0.0f, 0.0f);
				glutWireCube(7.0);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void DrawBenchPress()
{
	glPushMatrix();
		glTranslatef(11.0f, 0.0f, -12.0f);

		// �ٴ�
		glPushMatrix();
			glScalef(0.8f, 0.1f, 0.5f);
			glColor3f(0.5f, 0.5f, 0.5f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();

		// ���
		glPushMatrix();
			glTranslatef(2.0f, 2.0f, 1.5f);
			glScalef(0.05f, 0.8f, 0.05f);
			glColor3f(0.5f, 0.5f, 0.5f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(2.0f, 2.0f, -1.5f);
			glScalef(0.05f, 0.8f, 0.05f);
			glColor3f(0.5f, 0.5f, 0.5f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();

		// �ٺ�
		glPushMatrix();
			glTranslatef(1.8f, Push, 0.0f);
			glPushMatrix();
				glScalef(0.05f, 0.1f, 0.8f);
				glColor3f(0.85f, 0.25f, 0.77f);
				glutSolidCube(7.0);
				glColor3f(0.0f, 0.0f, 0.0f);
				glutWireCube(7.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, 2.5f);
				glScalef(0.2f, 0.2f, 0.03f);
				glColor3f(0.85f, 0.25f, 0.77f);
				glutSolidSphere(5.0, 10.0, 15.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, -2.5f);
				glScalef(0.2f, 0.2f, 0.03f);
				glColor3f(0.85f, 0.25f, 0.77f);
				glutSolidSphere(5.0, 10.0, 15.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, 2.8f);
				glScalef(0.1f, 0.1f, 0.03f);
				glColor3f(0.9f, 0.8f, 0.6f);
				glutSolidSphere(5.0, 10.0, 15.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, -2.8f);
				glScalef(0.1f, 0.1f, 0.03f);
				glColor3f(0.9f, 0.8f, 0.6f);
				glutSolidSphere(5.0, 10.0, 15.0);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void Collide()
{
	if ((MoveX - radius < BMoveZ + 2.5f) && (MoveZ - radius < BMoveX + 2.5f) && SphereDir == 1)
	{
		SphereDir = 2;
		dir = 3;
		printf("col 2\n");

	}

	if ((MoveZ - radius < BMoveX + 2.5f) && (MoveX - radius < BMoveZ + 2.5f) && SphereDir == 3)
	{
		SphereDir = 0;
		dir = 1;

		printf("col 4\n");
	}
}

void DrawAirplane()
{
	glPushMatrix();
		glTranslatef(0.0f, 15.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

		glTranslatef(airplaneX, 0.0f, airplaneZ);

		glRotatef(-airplanedegree, 0.0f, 1.0f, 0.0f);

		glRotatef(airplaneRot, 0.0f, 1.0f, 0.0f);

		// ����
		glPushMatrix();
			glColor3f(0.0f, 0.5f, 1.0f);
			glScalef(1.0f, 1.0f, 3.0f);
			glutSolidCylinder(1.0, 2.0, 20, 8);
		glPopMatrix();

		// ���
		glPushMatrix();
			glColor3f(0.5f, 0.0f, 1.0f);
			glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
			gluCylinder(quadratic, 1.0, 0.1, 2.0, 20, 8);
		glPopMatrix();

		// �� ����
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(0.0f, 0.0f, 1.0f);
			glScalef(4.0f, 0.2f, 1.0f);
			glutSolidCube(2.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(2.0);
		glPopMatrix();

		// �� ����
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(0.0f, 0.0f, 5.1f);
			glScalef(2.0f, 0.2f, 0.8f);
			glutSolidCube(2.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(2.0);
		glPopMatrix();

		// ����
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(0.0f, 1.0f, 5.1f);
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			glScalef(1.5f, 0.2f, 0.4f);
			glutSolidSphere(2.0, 3.0, 3.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireSphere(2.0, 3.0, 3.0);
		glPopMatrix();

		// �����緯
		glPushMatrix();
			glRotatef(propeller, 0.0f, 0.0f, 1.0f);

			glPushMatrix();
				glColor3f(1.0f, 0.0f, 0.0f);
				glTranslatef(0.0f, 1.0f, -2.0f);
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(1.0f, 0.1f, 0.1f);
				glutSolidCube(2.0);
				glColor3f(0.0f, 0.0f, 0.0f);
				glutWireCube(2.0);
			glPopMatrix();
			glPushMatrix();
				glColor3f(0.0f, 1.0f, 0.0f);
				glTranslatef(-0.8f, -0.5f, -2.0f);
				glRotatef(210.0f, 0.0f, 0.0f, 1.0f);
				glScalef(1.0f, 0.1f, 0.1f);
				glutSolidCube(2.0);
				glColor3f(0.0f, 0.0f, 0.0f);
				glutWireCube(2.0);
			glPopMatrix();
			glPushMatrix();
				glColor3f(0.0f, 0.0f, 1.0f);
				glTranslatef(0.8f, -0.5f, -2.0f);
				glRotatef(-210.0f, 0.0f, 0.0f, 1.0f);
				glScalef(1.0f, 0.1f, 0.1f);
				glutSolidCube(2.0);
				glColor3f(0.0f, 0.0f, 0.0f);
				glutWireCube(2.0);
			glPopMatrix();
		glPopMatrix();

		// ����
		for (iter = shape.begin(); iter != shape.end(); ++iter)
		{
			glPushMatrix();
				glColor3f(0.8f, 0.8f, 0.8f);
				glTranslatef(0.0f, 0.0f, iter->MoveZ);
				glScalef(iter->SphereSize, iter->SphereSize, iter->SphereSize);
				glutSolidSphere(1.0, 10, 10);
			glPopMatrix();
		}
	glPopMatrix();
}