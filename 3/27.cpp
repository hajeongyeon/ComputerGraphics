#include <GL/freeglut.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;


// �Լ� ����
void SetupRC();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void DrawTree();
void DrawRunningMachine();
void DrawPullUpBar();
void DrawBenchPress();
void DrawCube();
void DrawRobot();

void TreeCollide();
void RunningCollide();
void BenchCollide();
void PullCollide();


// ����
int yRot;			// y�� ȸ��
float zoom;			// zoom

int LeafDir, LeftLegDir, RightLegDir, SwingDir, PushDir;		// ü���� ������Ʈ direction
double LeafRadius;												// ���� �� (��ü) radius
float Conveyor, LeftLeg, RightLeg, Swing, Push;					// ü���� ������Ʈ ������

bool IsDepthTest, IsCulling, IsFrontOpen, RobotMove;			// ��������, �ø�, ���� �Ա� on/off, �κ� ������ ���� ����

float opendoor;								// �Ѳ�
int RobotDir, RobotRot;						// �κ� ����, ����
float LLeg, RLeg, LArm, RArm;				// �� �ٸ� ����
int LLegDir, RLegDir, LArmDir, RArmDir;		// �� �ٸ� ����
float MoveX, MoveZ, Jump;					// �̵�
int JumpDir, SaveRobotDir;					// ���� ����


// �Լ� ����
void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 27"); // ������ ���� (������ �̸�)
	SetupRC(); // ���� ���� �ʱ�ȭ �Լ�
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

// �ʱ�ȭ �Լ�
void SetupRC()
{
	yRot = 0, zoom = 0.0f;

	LeafDir = 1, LeftLegDir = 1, RightLegDir = -1, SwingDir = 1, PushDir = 1;
	LeafRadius = 3.0;
	Conveyor = 0.0f, LeftLeg = 0.0f, RightLeg = 0.0f, Swing = 0.0f, Push = 2.0f;

	IsDepthTest = true, IsCulling = false, IsFrontOpen = false, RobotMove = false;

	opendoor = 0.0f;
	RobotDir = 0, RobotRot = 0;
	LLeg = 0.0f, RLeg = 0.0f, LArm = 0.0f, RArm = 0.0f;
	LLegDir = 1, RLegDir = -1, LArmDir = -1, RArmDir = 1;
	MoveX = 0.0f, MoveZ = 0.0f, Jump = 0.0f;
	JumpDir = 1, SaveRobotDir = 0;
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

	// ü����
	DrawTree();
	DrawRunningMachine();
	DrawPullUpBar();
	DrawBenchPress();

	// ����
	DrawCube();

	// �κ�
	DrawRobot();

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

	case '+':
		zoom -= 0.1f;
		break;

	case '-':
		zoom += 0.1f;
		break;

	case 'i': case 'I':
		SetupRC();
		break;

	case 'w': case 'W':
		RobotDir = 1;
		break;

	case 'a': case 'A':
		RobotDir = 2;
		break;

	case 's': case 'S':
		RobotDir = 0;
		break;

	case 'd': case 'D':
		RobotDir = 3;
		break;

	case 'j': case 'J':
		SaveRobotDir = RobotDir;
		RobotDir = 4;
		break;

	case 'o': case 'O':
		IsFrontOpen = true;
		break;

	case 'h': case 'H':
		if (!IsDepthTest)
		{
			IsDepthTest = true;
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			IsDepthTest = false;
			glDisable(GL_DEPTH_TEST);
		}
		break;

	case 'c': case 'C':
		if (!IsCulling)
		{
			IsCulling = true;
			glEnable(GL_CULL_FACE);
		}
		else
		{
			IsCulling = false;
			glDisable(GL_CULL_FACE);
		}
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void TimerFunction(int value)
{
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

	//
	if (IsFrontOpen)
	{
		opendoor += 0.4f;
		if (opendoor > 8.0f)
		{
			RobotMove = true;
			IsFrontOpen = false;
		}
	}

	if (RobotMove)
	{
		if (RobotDir != 4)
		{
			LArm += 5.0f * LArmDir;
			if (LArm > 30.0f || LArm < -30.0f) LArmDir *= -1;

			RArm += 5.0f * RArmDir;
			if (RArm > 30.0f || RArm < -30.0f) RArmDir *= -1;

			LLeg += 5.0f * LLegDir;
			if (LLeg > 30.0f || LLeg < -30.0f) LLegDir *= -1;

			RLeg += 5.0f * RLegDir;
			if (RLeg > 30.0f || RLeg < -30.0f) RLegDir *= -1;
		}

		if (RobotDir == 0)
		{
			RobotRot = 0;
			MoveZ += 0.3f;
			if (MoveZ > 15.0f) MoveZ = 15.0f;
		}
		else if (RobotDir == 1)
		{
			RobotRot = 180;
			MoveZ -= 0.3f;
			if (MoveZ < -15.0f) MoveZ = -15.0f;
		}
		else if (RobotDir == 2)
		{
			RobotRot = 270;
			MoveX -= 0.3f;
			if (MoveX < -15.0f) MoveX = -15.0f;
		}
		else if (RobotDir == 3)
		{
			RobotRot = 90;
			MoveX += 0.3f;
			if (MoveX > 15.0f) MoveX = 15.0f;
		}
		else if (RobotDir == 4)
		{
			LLeg = 0.0f, RLeg = 0.0f;

			Jump += 0.3f * JumpDir;
			if(Jump >= 2.0f) JumpDir *= -1;

			if (Jump < 0.0f)
			{
				JumpDir = 1;
				RobotDir = SaveRobotDir;
			}
		}
	}

	TreeCollide();
	RunningCollide();
	BenchCollide();
	PullCollide();

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
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

void DrawCube()
{
	glPushMatrix();	
		glTranslatef(0.0f, 4.1f, 3.0f);

		// ��
		glPushMatrix();
			glTranslatef(0.0f, opendoor, 0.0f);
		
			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-4.0f, 4.0f, 0.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-4.0f, -4.0f, 0.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(4.0f, -4.0f, 0.0f);
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(4.0f, 4.0f, 0.0f);
			glEnd();
		glPopMatrix();

		// ��
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(4.0f, 4.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(4.0f, -4.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(4.0f, -4.0f, -8.0f);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(4.0f, 4.0f, -8.0f);
		glEnd();

		// ��
		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(4.0f, 4.0f, -8.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(4.0f, -4.0f, -8.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-4.0f, -4.0f, -8.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-4.0f, 4.0f, -8.0f);
		glEnd();

		// ��
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-4.0f, 4.0f, -8.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-4.0f, -4.0f, -8.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-4.0f, -4.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-4.0f, 4.0f, 0.0f);
		glEnd();

		// ��
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-4.0f, 4.0f, -8.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-4.0f, 4.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(4.0f, 4.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(4.0f, 4.0f, -8.0f);
		glEnd();

		// �Ʒ�
		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-4.0f, -4.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-4.0f, -4.0f, -8.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(4.0f, -4.0f, -8.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(4.0f, -4.0f, 0.0f);
		glEnd();
	glPopMatrix();
}

void DrawRobot()
{
	glPushMatrix();
		glTranslatef(0.0f, 3.0f, 0.0f);
		glTranslatef(MoveX, 0.0f, 0.0f);
		glTranslatef(0.0f, Jump, 0.0f);
		glTranslatef(0.0f, 0.0f, MoveZ);
		glRotatef(RobotRot, 0.0f, 1.0f, 0.0f);

		// ����
		glPushMatrix();
			glScalef(0.8f, 1.0f, 0.5f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glutSolidCube(3.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(3.0);
		glPopMatrix();

		// �Ӹ�
		glPushMatrix();
			glTranslatef(0.0f, 2.0f, 0.0f);
			glScalef(0.8f, 1.0f, 0.5f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glutSolidCube(2.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(2.0);
		glPopMatrix();

		// ��
		glPushMatrix();
			glTranslatef(0.0f, 2.0f, 0.5f);
			glScalef(0.8f, 1.0f, 0.5f);
			glColor3f(0.95f, 0.38f, 0.65f);
			glutSolidCube(0.5);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(0.5);
		glPopMatrix();

		// ����
		glPushMatrix();
			glTranslatef(-1.4f, 0.0f, 0.0f);
			glTranslatef(0.0f, 1.0f, 0.0f);
			glRotatef(LArm, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -1.0f, 0.0f);
			glScalef(0.1f, 1.0f, 0.1f);
			glColor3f(0.81f, 0.69f, 1.0f);
			glutSolidCube(2.5);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(2.5);
		glPopMatrix();

		// ������
		glPushMatrix();
			glTranslatef(1.4f, 0.0f, 0.0f);
			glTranslatef(0.0f, 1.0f, 0.0f);
			glRotatef(RArm, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -1.0f, 0.0f);
			glScalef(0.1f, 1.0f, 0.1f);
			glColor3f(0.94f, 0.58f, 0.38f);
			glutSolidCube(2.5);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(2.5);
		glPopMatrix();

		// �޴ٸ�
		glPushMatrix();
			glTranslatef(-0.4f, -2.0f, 0.0f);
			glTranslatef(0.0f, 1.0f, 0.0f);
			glRotatef(LLeg, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -1.0f, 0.0f);
			glScalef(0.2f, 1.0f, 0.2f);
			glColor3f(0.4f, 0.6f, 1.0f);
			glutSolidCube(1.7);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(1.7);
		glPopMatrix();

		// �����ٸ�
		glPushMatrix();
			glTranslatef(0.4f, -2.0f, 0.0f);
			glTranslatef(0.0f, 1.0f, 0.0f);
			glRotatef(RLeg, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -1.0f, 0.0f);
			glScalef(0.2f, 1.0f, 0.2f);
			glColor3f(0.71f, 0.94f, 0.69f);
			glutSolidCube(1.7);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(1.7);
		glPopMatrix();
	glPopMatrix();
}

void TreeCollide()
{
	if (RobotDir == 3 && MoveZ > 11.0 && MoveX > 12.0)
	{
		SaveRobotDir = 4;
		RobotDir = 4;
	}
	else if (RobotDir == 0 && MoveZ > 11.0 && MoveX > 12.0)
	{
		SaveRobotDir = 4;
		RobotDir = 4;
	}
}

void RunningCollide()
{
	if (RobotDir == 2 && MoveZ > 10.0 && MoveX < -7.0)
	{
		SaveRobotDir = 4;
		RobotDir = 4;
	}
	else if (RobotDir == 0 && MoveZ > 10.0 && MoveX < -7.0)
	{
		SaveRobotDir = 4;
		RobotDir = 4;
	}
}

void BenchCollide()
{
	if (RobotDir == 3 && MoveZ < -10.0 && MoveX > 8.0)
	{
		SaveRobotDir = 4;
		RobotDir = 4;
	}
	else if (RobotDir == 1 && MoveZ < -10.0 && MoveX > 8.0)
	{
		SaveRobotDir = 4;
		RobotDir = 4;
	}
}

void PullCollide()
{
	if (RobotDir == 2 && MoveZ < -8.5 && MoveX < -12.0)
	{
		SaveRobotDir = 4;
		RobotDir = 4;
	}
	else if (RobotDir == 1 && MoveZ < -8.5 && MoveX < -12.0)
	{
		SaveRobotDir = 4;
		RobotDir = 4;
	}
}