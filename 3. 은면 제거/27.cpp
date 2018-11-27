#include <GL/freeglut.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;


// 함수 선언
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


// 변수
int yRot;			// y축 회전
float zoom;			// zoom

int LeafDir, LeftLegDir, RightLegDir, SwingDir, PushDir;		// 체육관 오브젝트 direction
double LeafRadius;												// 나무 잎 (구체) radius
float Conveyor, LeftLeg, RightLeg, Swing, Push;					// 체육관 오브젝트 변수들

bool IsDepthTest, IsCulling, IsFrontOpen, RobotMove;			// 은면제거, 컬링, 무대 입구 on/off, 로봇 움직임 시작 변수

float opendoor;								// 뚜껑
int RobotDir, RobotRot;						// 로봇 방향, 각도
float LLeg, RLeg, LArm, RArm;				// 팔 다리 각도
int LLegDir, RLegDir, LArmDir, RArmDir;		// 팔 다리 방향
float MoveX, MoveZ, Jump;					// 이동
int JumpDir, SaveRobotDir;					// 점프 방향


// 함수 정의
void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 27"); // 윈도우 생성 (윈도우 이름)
	SetupRC(); // 상태 변수 초기화 함수
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

// 초기화 함수
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

// 윈도우 출력 함수
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

	// 체육관
	DrawTree();
	DrawRunningMachine();
	DrawPullUpBar();
	DrawBenchPress();

	// 무대
	DrawCube();

	// 로봇
	DrawRobot();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 원근 투영
	gluPerspective(60.0f, w / h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -30.0);

	// 직각 투영
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
		// 기둥
		glPushMatrix();
			glTranslatef(0.0f, 4.0f, 0.0f);
			glScalef(0.2f, 1.0f, 0.2f);
			glColor3f(0.6f, 0.23f, 0.02f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();
		// 풀
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

		// 바닥
		glPushMatrix();
			glScalef(0.8f, 0.1f, 0.5f);
			glColor3f(0.5f, 0.5f, 0.5f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();

		// 기둥
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

		// 컨베이어
		glPushMatrix();
			glScalef(0.25f, 0.05f, 0.5f);
			glRotatef(Conveyor, 0.0f, 0.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireTorus(5.0, 10.0, 20.0, 20.0);
		glPopMatrix();

		// 다리
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

		// 철봉
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

		// 사람
		glPushMatrix();
			glTranslatef(0.0f, 4.0f, 0.0f);
			glRotatef(Swing, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f, -4.0f, 0.0f);

			// 얼굴
			glPushMatrix();
				glTranslatef(0.0f, 2.0f, 0.0f);
				glScalef(0.1f, 0.1f, 0.1f);
				glColor3f(0.98f, 0.87f, 0.83f);
				glutSolidCube(7.0);
				glColor3f(0.0f, 0.0f, 0.0f);
				glutWireCube(7.0);
			glPopMatrix();

			// 팔
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

			// 몸통
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

		// 바닥
		glPushMatrix();
			glScalef(0.8f, 0.1f, 0.5f);
			glColor3f(0.5f, 0.5f, 0.5f);
			glutSolidCube(7.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(7.0);
		glPopMatrix();

		// 기둥
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

		// 바벨
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

		// 앞
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

		// 오
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

		// 뒤
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

		// 왼
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

		// 위
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

		// 아래
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

		// 몸통
		glPushMatrix();
			glScalef(0.8f, 1.0f, 0.5f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glutSolidCube(3.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(3.0);
		glPopMatrix();

		// 머리
		glPushMatrix();
			glTranslatef(0.0f, 2.0f, 0.0f);
			glScalef(0.8f, 1.0f, 0.5f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glutSolidCube(2.0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(2.0);
		glPopMatrix();

		// 코
		glPushMatrix();
			glTranslatef(0.0f, 2.0f, 0.5f);
			glScalef(0.8f, 1.0f, 0.5f);
			glColor3f(0.95f, 0.38f, 0.65f);
			glutSolidCube(0.5);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(0.5);
		glPopMatrix();

		// 왼팔
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

		// 오른팔
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

		// 왼다리
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

		// 오른다리
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