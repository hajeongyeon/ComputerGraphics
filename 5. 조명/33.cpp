//	33
//	실습 32에서 두개의 조명을 중심의 y축을 기준으로 시계반대방향으로 회전시킨다.
//	눈 내리는 애니메이션을 추가한다.
//	- 바닥은 처음에는 짙은 색이다.
//	- 바닥에 눈이 닿으면 바닥의 색이 부분부분으로 점점 하얘진다.
//	- 눈을 멈추기 / 내리기 할 수 있도록 명령어 추가

#include <GL/freeglut.h>
#include <random>
#include <iostream>
using namespace std;

#define RADIAN 0.0174532

typedef struct {
	float x, y, z;
} SNOW;

void SetupRC();
GLvoid drawScene(GLvoid);
void Reshape(int w, int h);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void DrawPyramid(float, float, float);
void DrawMoon();
void DrawSnow();

int MoonDegree, LightDegree;
float yRot;
bool nflight1, nflight2, isNormal, isSnow;

SNOW snow[100];

GLfloat AmbientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat DiffuseLight1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat SpecularLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos1[] = { 10.0f, 10.0f, 0.0f, 1.0f };
GLfloat gray[] = { 0.25f, 0.25f, 0.25f, 1.0f };

GLfloat DiffuseLight2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat SpecularLight2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos2[] = { -10.0f, 10.0f, 0.0f, 1.0f };

GLfloat SpecularLightSnow[30][30][4] = { 0.1f, 0.1f, 0.1f, 0.1f };

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 33"); // 윈도우 생성 (윈도우 이름)
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
	nflight1 = false, nflight2 = false, isNormal = true, isSnow = true;

	for (int i = 0; i < 100; ++i)
	{
		snow[i].x = rand() % 30 - 15;
		snow[i].y = rand() % 20 + 10;
		snow[i].z = rand() % 30 - 15;
	}
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

	if (isSnow) DrawSnow();

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

	case 'a':
		for (int i = 0; i < 4; ++i)
		{
			AmbientLight[i] += 0.1f;
		}
		break;

	case 'A':
		for (int i = 0; i < 4; ++i)
		{
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

	case 'b': case 'B':
		if (!isSnow) isSnow = true;
		else isSnow = false;
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

	lightPos1[0] = 10.0f * cos(LightDegree * RADIAN);
	lightPos1[2] = 10.0f * sin(LightDegree * RADIAN);

	lightPos2[0] = 10.0f * -cos(LightDegree * RADIAN);
	lightPos2[2] = 10.0f * -sin(LightDegree * RADIAN);

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