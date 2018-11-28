//	34
//	실습 33에 로봇을 추가한다
//	실습 27의 로봇을 추가하여 키보드 명령으로 좌우앞뒤 이동하도록 한다
//	로봇 위에 스포트라이트를 넣는다.항상 로봇 머리 위에 스포트라이트가 있다
//	스포트라이트 설정
//	- 스포트라이트를 사용하기 위해서는 glLight 함수에서 다음의 속성을 설정한다.
//	GL_POSITION : 마지막 인자를 1로 설정한다.
//		GL_SPOT_DIRECTION : 스포트라이트의 방향 벡터
//		GL_SPOT_CUTOFF : 스포트라이트의 확산 각도
//		CL_SPOT_EXPONENT : 스포트라이트 지수
//		- 바닥에 스포트라이트의 모양을 만들기 윟서 바닥을 작은 사각형의 메쉬로 그린다.
//		로봇이 장애물에 부딪히면 파티클이 생기고 이동하지 못한다.

#include <GL/freeglut.h>
#include <random>
#include <iostream>
using namespace std;

#define RADIAN 0.0174532

typedef struct {
	float x, y, z;
} SNOW;

typedef struct {
	float x, y, z;
	float cnt;
} PARTICLE;

void SetupRC();
GLvoid drawScene(GLvoid);
void Reshape(int w, int h);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void DrawPyramid(float, float, float);
void DrawMoon();
void DrawSnow();
void DrawRobot();
void Particle();

void Collide();

int MoonDegree, LightDegree;
float yRot;
bool nflight1, nflight2, isNormal, isSnow, LightMove;

int RobotDir, RobotRot;						// 로봇 방향, 각도
float LLeg, RLeg, LArm, RArm;				// 팔 다리 각도
int LLegDir, RLegDir, LArmDir, RArmDir;		// 팔 다리 방향
float MoveX, MoveZ, Jump;					// 이동

SNOW snow[100];
PARTICLE particle[60];

GLfloat AmbientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat DiffuseLight1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat SpecularLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos1[] = { 10.0f, 10.0f, 0.0f, 1.0f };
GLfloat gray[] = { 0.25f, 0.25f, 0.25f, 1.0f };

GLfloat DiffuseLight2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat SpecularLight2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos2[] = { -10.0f, 10.0f, 0.0f, 1.0f };

GLfloat SpecularLightSnow[30][30][4] = { 0.1f, 0.1f, 0.1f, 0.1f };

GLfloat DiffuseLightRobot[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat SpecularLightRobot[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPosRobot[] = { 0.0f, 7.0f, 0.0f, 1.0f };
GLfloat SpotDirection[] = { 0, -1, 0 };
GLfloat SpotCutoff[] = { 40.0f };
GLfloat SpotExponent[] = { 5.0f };

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 34"); // 윈도우 생성 (윈도우 이름)
	SetupRC(); // 상태 변수 초기화 함수
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}

void SetupRC()
{
	MoonDegree = 0, LightDegree = 0;
	yRot = 0.0f;
	nflight1 = false, nflight2 = false, isNormal = true, isSnow = true, LightMove = true;

	RobotDir = 0, RobotRot = 0;
	LLeg = 0.0f, RLeg = 0.0f, LArm = 0.0f, RArm = 0.0f;
	LLegDir = 1, RLegDir = -1, LArmDir = -1, RArmDir = 1;
	MoveX = -10.0f, MoveZ = 0.0f, Jump = 0.0f;

	for (int i = 0; i < 100; ++i)
	{
		snow[i].x = rand() % 30 - 15;
		snow[i].y = rand() % 20 + 10;
		snow[i].z = rand() % 30 - 15;
	}

	lightPosRobot[0] = MoveX;
	lightPosRobot[2] = MoveZ;
}

GLvoid drawScene(GLvoid)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기

	glLoadIdentity();

	glTranslatef(0.0f, -10.0f, 0.0f);
	glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// 전역 주변광
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	// 1번 조명
	glPushMatrix();
	glPushMatrix();
	glTranslatef(lightPos1[0], lightPos1[1], lightPos1[2]);
	glutSolidSphere(1.0, 10, 10);
	glPopMatrix();

	if (nflight1)
	{
		// 조명을 사용하도록 설정 
		glEnable(GL_LIGHTING);

		// 조명 설정
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight1);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight1);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
		glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLight1);
		glMateriali(GL_FRONT, GL_SHININESS, 64);

		glEnable(GL_LIGHT0);
	}
	else
		glDisable(GL_LIGHT0);

	// 2번 조명
	glPushMatrix();
	glTranslatef(lightPos2[0], lightPos2[1], lightPos2[2]);
	glutSolidSphere(1.0, 10, 10);
	glPopMatrix();

	if (nflight2)
	{
		// 조명을 사용하도록 설정 
		glEnable(GL_LIGHTING);

		// 조명 설정
		glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight2);
		glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight2);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
		glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLight2);
		glMateriali(GL_FRONT, GL_SHININESS, 64);

		glEnable(GL_LIGHT1);
	}
	else
		glDisable(GL_LIGHT1);
	glPopMatrix();

	// 바닥
	for (int i = -15; i < 15; ++i)
	{
		for (int j = -15; j < 15; ++j)
		{
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
			glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLightSnow[i + 15][j + 15]);
			glMateriali(GL_FRONT, GL_SHININESS, 64);

			glTranslatef(i, 0.0f, j);
			glScalef(1.0f, 0.0f, 1.0f);
			glutSolidCube(1.0f);
			glPopMatrix();
		}
	}

	// 피라미드
	DrawPyramid(0, 15, 0);
	DrawPyramid(-12, 6, -12);
	DrawPyramid(12, 6, -12);
	DrawPyramid(-12, 6, 12);
	DrawPyramid(12, 6, 12);

	// 달
	DrawMoon();

	// 눈
	if (isSnow) DrawSnow();

	// 로봇
	glPushMatrix();
		// 조명을 사용하도록 설정 
		glEnable(GL_LIGHTING);

		// 조명 설정
		glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLightRobot);
		glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLightRobot);
		glLightfv(GL_LIGHT2, GL_POSITION, lightPosRobot);

		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, SpotDirection);
		glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, SpotCutoff);
		glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, SpotExponent);

		glEnable(GL_LIGHT2);

		DrawRobot();
	glPopMatrix();

	Collide();

	if (RobotDir == 4) Particle();

	glutSwapBuffers(); // 결과 출력
}

void Reshape(int w, int h)
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

	case 'm':
		for (int i = 0; i < 4; ++i)
		{
			AmbientLight[i] += 0.1f;
		}
		break;

	case 'M':
		for (int i = 0; i < 4; ++i)
		{
			AmbientLight[i] -= 0.1f;
		}
		break;

	case 'f':
		for (int i = 0; i < 4; ++i)
		{
			DiffuseLight1[i] += 0.1f;
			DiffuseLight2[i] += 0.1f;
		}
		break;

	case 'F':
		for (int i = 0; i < 4; ++i)
		{
			DiffuseLight1[i] -= 0.1f;
			DiffuseLight2[i] -= 0.1f;
		}
		break;

	case 'e':
		for (int i = 0; i < 4; ++i)
		{
			SpecularLight1[i] += 0.1f;
			SpecularLight2[i] += 0.1f;
		}
		break;

	case 'E':
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

	case 'b': case 'B':
		if (!isSnow) isSnow = true;
		else isSnow = false;
		break;

	case 'l': case 'L':
		if (!LightMove) LightMove = true;
		else LightMove = false;
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
	MoonDegree += 20;
	LightDegree += 10;

	if (LightMove)
	{
		lightPos1[0] = 10.0f * cos(LightDegree * RADIAN);
		lightPos1[2] = 10.0f * sin(LightDegree * RADIAN);

		lightPos2[0] = 10.0f * -cos(LightDegree * RADIAN);
		lightPos2[2] = 10.0f * -sin(LightDegree * RADIAN);
	}

	if (isSnow)
	{
		for (int i = 0; i < 100; ++i)
		{
			snow[i].y -= 0.1f;

			if (snow[i].y < 0)
			{
				snow[i].x = rand() % 30 - 15;
				snow[i].y = rand() % 20 + 10;
				snow[i].z = rand() % 30 - 15;

				int tmpx = snow[i].x + 15;
				int tmpz = snow[i].z + 15;

				if (SpecularLightSnow[tmpx][tmpz][0] < 1.0f)
				{
					SpecularLightSnow[tmpx][tmpz][0] += 0.1f;
					SpecularLightSnow[tmpx][tmpz][1] += 0.1f;
					SpecularLightSnow[tmpx][tmpz][2] += 0.1f;
					SpecularLightSnow[tmpx][tmpz][3] += 0.1f;
				}
			}
		}
	}

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
	}

	lightPosRobot[0] = MoveX;
	lightPosRobot[2] = MoveZ;

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
	// 바닥
	glBegin(GL_POLYGON);
	glVertex3f(x - 3, 0, z - 3);
	glVertex3f(x + 3, 0, z - 3);
	glVertex3f(x + 3, 0, z + 3);
	glVertex3f(x - 3, 0, z + 3);
	glEnd();

	// 옆
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
	glTranslatef(5.0f * cos(MoonDegree * RADIAN), 15, 5.0f * sin(MoonDegree * RADIAN));
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();
}

void DrawSnow()
{
	for (int i = 0; i < 100; ++i)
	{
		glPushMatrix();
		glTranslatef(snow[i].x, snow[i].y, snow[i].z);
		glColor3f(1.0f, 1.0f, 1.0f);
		glutSolidSphere(0.1, 10, 10);
		glPopMatrix();
	}
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

void Collide()
{
	if (MoveZ > -3.5 && MoveZ < 3.5 && MoveX > -3.5 && MoveX < 3.5) RobotDir = 4;

	if (RobotDir == 3 && MoveZ > 8.0 && MoveX > 8.0) RobotDir = 4;
	else if (RobotDir == 0 && MoveZ > 8.0 && MoveX > 8.0) RobotDir = 4;

	if (RobotDir == 2 && MoveZ > 8.0 && MoveX < -8.0) RobotDir = 4;
	else if (RobotDir == 0 && MoveZ > 8.0 && MoveX < -8.0) RobotDir = 4;

	if (RobotDir == 3 && MoveZ < -8.0 && MoveX > 8.0) RobotDir = 4;
	else if (RobotDir == 1 && MoveZ < -8.0 && MoveX > 8.0) RobotDir = 4;

	if (RobotDir == 2 && MoveZ < -8.0 && MoveX < -8.0) RobotDir = 4;
	else if (RobotDir == 1 && MoveZ < -8.0 && MoveX < -8.0) RobotDir = 4;

	if (RobotDir == 4)
	{
		for (int i = 0; i < 10; ++i)
		{
			particle[i].x = MoveX + cos(i * 36 * RADIAN) * particle[0].cnt;
			particle[i].y = sin(i * 36 * RADIAN) * particle[0].cnt;
			particle[i].z = MoveZ;
		}
		for (int i = 10; i < 20; ++i)
		{
			particle[i].x = MoveX + cos((i - 10) * 36 * RADIAN) * particle[0].cnt;
			particle[i].y = sin((i - 10) * 36 * RADIAN) * particle[0].cnt;
			particle[i].z = MoveZ;
		}
		for (int i = 20; i < 30; ++i)
		{
			particle[i].x = MoveX + cos((i - 20) * 36 * RADIAN) * particle[0].cnt;
			particle[i].y = sin((i - 20) * 36 * RADIAN) * particle[0].cnt;
			particle[i].z = MoveZ;
		}
		for (int i = 30; i < 40; ++i)
		{
			particle[i].x = MoveX + cos((i - 30) * 36 * RADIAN) * particle[0].cnt;
			particle[i].y = sin((i - 30) * 36 * RADIAN) * particle[0].cnt;
			particle[i].z = MoveZ;
		}
		particle[0].cnt += 0.3f;

		if (particle[0].cnt == 20)
			particle[0].cnt = 0;
	}
	else
	{
		for (int i = 0; i < 40; ++i)
		{
			particle[i].x = -100;
			particle[i].y = -100;
			particle[i].z = -100;
		}
		particle[0].cnt = 0;
	}
}

float particleRot = 0.0f;

void Particle()
{
	for (int i = 0; i < 40; ++i)
	{
		glPushMatrix();
			if (i >= 10 && i < 20)
			{
				particleRot = 45.0f;
			}
			else if (i >= 20 && i < 30)
			{
				particleRot = 90.0f;
			}
			else if (i >= 30 && i < 40)
			{
				particleRot = 135.0f;
			}
			glTranslatef(MoveX, 1.5f, MoveZ);
			glRotatef(particleRot, 0.0f, 1.0f, 0.0f);
			glTranslatef(-MoveX, 1.5f, -MoveZ);
			glTranslatef(particle[i].x, particle[i].y, particle[i].z);
			glutSolidCube(0.5f);
		glPopMatrix();
	}
}