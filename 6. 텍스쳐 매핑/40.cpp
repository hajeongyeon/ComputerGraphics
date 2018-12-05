#include <GL/freeglut.h>
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
void TimerFunction2(int);

void DrawPlain();
void DrawBigPyramid(int, int, int);
void DrawPyramid(float, float, float);
void DrawMoon();
void DrawBackground();
void DrawPillar();
void DrawSnow();

void DivideTriangle(float*, float*, float*, int);
void DrawTriangle(float*, float*, float*);

int degree;
float yRot;
bool nflight1, nflight2, plight, isSnow;

GLfloat AmbientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat DiffuseLight1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat SpecularLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos1[] = { 10.0f, 10.0f, 0.0f, 1.0f };
GLfloat gray1[] = { 0.25f, 0.25f, 0.25f, 1.0f };

GLfloat DiffuseLight2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat SpecularLight2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos2[] = { -10.0f, 10.0f, 0.0f, 1.0f };
GLfloat gray2[] = { 0.25f, 0.25f, 0.25f, 1.0f };

GLfloat DiffuseLightP[] = { 1.0f, 1.0f, 0.0f, 1.0f };
GLfloat SpecularLightP[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPosP[] = { 0.0f, 20.0f, 0.0f, 1.0f };
GLfloat SpotDirection[] = { 0, -1, 0 };
GLfloat SpotCutoff[] = { 20.0f };
GLfloat SpotExponent[] = { 10.0f };

GLfloat SpecularLightSnow[30][30][4] = { 0.1f, 0.1f, 0.1f, 0.1f };

GLubyte * LoadDIBitmap(const char*, BITMAPINFO**);
void LoadTexture();

GLuint texture[6];
GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수

float x;

SNOW snow[100];

GLfloat triangle1[3][3] = { { 0.0, 15.0, 0.0 },{ -3.0, 0.0, 3.0 },{ 3.0, 0.0, 3.0 } };
GLfloat triangle2[3][3] = { { 0.0, 15.0, 0.0 },{ -3.0, 0.0, 3.0 },{ -3.0, 0.0, -3.0 } };
GLfloat triangle3[3][3] = { { 0.0, 15.0, 0.0 },{ -3.0, 0.0, -3.0 },{ 3.0, 0.0, -3.0 } };
GLfloat triangle4[3][3] = { { 0.0, 15.0, 0.0 },{ 3.0, 0.0, -3.0 },{ 3.0, 0.0, 3.0 } };

int level;

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 40"); // 윈도우 생성 (윈도우 이름)
	SetupRC(); // 상태 변수 초기화 함수
	LoadTexture();
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutTimerFunc(1000, TimerFunction2, 2);
	glutMainLoop();
}

void SetupRC()
{
	degree = 0;
	yRot = 0.0f;
	nflight1 = false, nflight2 = false, plight = false, isSnow = false;

	for (int i = 0; i < 100; ++i)
	{
		snow[i].x = rand() % 30 - 15;
		snow[i].y = rand() % 20 + 10;
		snow[i].z = rand() % 30 - 15;
	}

	level = 1;
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

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray1);
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

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray2);
		glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLight2);
		glMateriali(GL_FRONT, GL_SHININESS, 64);

		glEnable(GL_LIGHT1);
	}
	else
		glDisable(GL_LIGHT1);

	// 바닥
	DrawBackground();
	DrawPlain();

	// 피라미드
	glPushMatrix();
		if (plight)
		{
			// 조명을 사용하도록 설정 
			glEnable(GL_LIGHTING);
	
			// 조명 설정
			glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLightP);
			glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLightP);
			glLightfv(GL_LIGHT2, GL_POSITION, lightPosP);
	
			glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, SpotDirection);
			glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, SpotCutoff);
			glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, SpotExponent);
	
			glEnable(GL_LIGHT2);
		}
		else
			glDisable(GL_LIGHT2);
		//DrawBigPyramid(0, 15, 0);
		DivideTriangle(triangle1[0], triangle1[1], triangle1[2], level);
		DivideTriangle(triangle2[0], triangle2[1], triangle2[2], level);
		DivideTriangle(triangle3[0], triangle3[1], triangle3[2], level);
		DivideTriangle(triangle4[0], triangle4[1], triangle4[2], level);
	glPopMatrix();

	DrawPyramid(-12, 6, -12);
	DrawPyramid(12, 6, -12);
	DrawPyramid(-12, 6, 12);
	DrawPyramid(12, 6, 12);

	if (!nflight1 && !nflight2 && !plight)
		glDisable(GL_TEXTURE_2D);

	// 달
	DrawMoon();

	// 기둥
	DrawPillar();

	// 눈
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
		if (nflight1)
		{
			nflight1 = false;
		}
		else
		{
			nflight1 = true;

			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		break;

	case '2':
		if (nflight2)
		{
			nflight2 = false;
		}
		else
		{
			nflight2 = true;

			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
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

	case 's': case 'S':
		if (!isSnow) isSnow = true;
		else isSnow = false;
		break;

	case 'l': case 'L':
		if (plight)
		{
			plight = false;
		}
		else
		{
			plight = true;

			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
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

	x += 0.1f;
	if (x >= 1.f)
		x = 0.f;

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
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void TimerFunction2(int value)
{
	level++;

	if (level > 5)
		level = 1;

	glutPostRedisplay();
	glutTimerFunc(1000, TimerFunction2, 2);
}

void DrawPlain()
{
	glPushMatrix();
	for (int i = -15; i < 15; ++i)
	{
		for (int j = -15; j < 15; ++j)
		{
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray1);
			glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLightSnow[i + 15][j + 15]);
			glMateriali(GL_FRONT, GL_SHININESS, 64);

			glTranslatef(i, 0.0f, j);
			glScalef(1.0f, 0.0f, 1.0f);
			glutSolidCube(1.0f);
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void DrawBigPyramid(int x, int y, int z)
{
	glPushMatrix();
	// 바닥
	glBegin(GL_POLYGON);
	glVertex3f(x - 3, 0, z - 3);
	glVertex3f(x + 3, 0, z - 3);
	glVertex3f(x + 3, 0, z + 3);
	glVertex3f(x - 3, 0, z + 3);
	glEnd();

	// 옆
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_POLYGON);
	glVertex3f(x - 3, 0, z - 3);
	glVertex3f(x + 3, 0, z - 3);
	glVertex3f(x, y, z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_POLYGON);
	glVertex3f(x + 3, 0, z - 3);
	glVertex3f(x + 3, 0, z + 3);
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + 3, 0, z + 3);
	glVertex3f(x - 3, 0, z + 3);
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x - 3, 0, z + 3);
	glVertex3f(x - 3, 0, z - 3);
	glVertex3f(x, y, z);
	glEnd();
	glPopMatrix();
}

void DrawPyramid(float x, float y, float z)
{
	glPushMatrix();
	// 바닥
	glBegin(GL_POLYGON);
	glVertex3f(x - 3, 0, z - 3);
	glVertex3f(x + 3, 0, z - 3);
	glVertex3f(x + 3, 0, z + 3);
	glVertex3f(x - 3, 0, z + 3);
	glEnd();

	// 옆
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(x - 3, 0, z - 3);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + 3, 0, z - 3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(x + 3, 0, z - 3);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + 3, 0, z + 3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(x + 3, 0, z + 3);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x - 3, 0, z + 3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(x - 3, 0, z + 3);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x - 3, 0, z - 3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z);
	glEnd();
	glPopMatrix();
}

void DrawMoon()
{
	glPushMatrix();
	// 자동 매핑 설정 
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	// 구 매핑
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTranslatef(5.0f * cos(degree * RADIAN), 15, 5.0f * sin(degree * RADIAN));
	glutSolidSphere(2.0, 10, 10);

	// 자동 매핑 해제
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glPopMatrix();
}

void DrawBackground()
{
	// 텍스처를 객체에 맵핑
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-250.0f, -250.0f, -250.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-250.0f, 250.0f, -250.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(250.0f, 250.0f, -250.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(250.0f, -250.0f, -250.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-250.0f, -250.0f, 250.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-250.0f, 250.0f, 250.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(250.0f, 250.0f, 250.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(250.0f, -250.0f, 250.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-250.0f, -250.0f, -250.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-250.0f, 250.0f, -250.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-250.0f, 250.0f, 250.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-250.0f, -250.0f, 250.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(250.0f, -250.0f, -250.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(250.0f, 250.0f, -250.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(250.0f, 250.0f, 250.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(250.0f, -250.0f, 250.0f);
	glEnd();

	glColor3f(1.f, 1.f, 0.f);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-250.0f, -250.0f, -250.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-250.0f, -250.0f, 250.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(250.0f, -250.0f, 250.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(250.0f, -250.0f, -250.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-250.0f, 250.0f, -250.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-250.0f, 250.0f, 250.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(250.0f, 250.0f, 250.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(250.0f, 250.0f, -250.0f);
	glEnd();
}

void DrawPillar()
{
	glPushMatrix();
	glTranslatef(0.0f, 10.0f, -7.0f);

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f + x, 0.5f);
	glVertex3f(-3.0f, -10.0f, 3.0f);
	glTexCoord2f(0.25f + x, 0.5f);
	glVertex3f(3.0f, -10.0f, 3.0f);
	glTexCoord2f(0.25f + x, 0.75f);
	glVertex3f(3.0f, 10.0f, 3.0f);
	glTexCoord2f(0.0f + x, 0.75f);
	glVertex3f(-3.0f, 10.0f, 3.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.25f + x, 0.75f);
	glVertex3f(3.0f, -10.0f, 3.0f);
	glTexCoord2f(0.5f + x, 0.75f);
	glVertex3f(3.0f, 10.0f, 3.0f);
	glTexCoord2f(0.5f + x, 1.0f);
	glVertex3f(3.0f, 10.0f, -3.0f);
	glTexCoord2f(0.25f + x, 1.0f);
	glVertex3f(3.0f, -10.0f, -3.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f + x, 0.5f);
	glVertex3f(-3.0f, -10.0f, -3.0f);
	glTexCoord2f(0.25f + x, 0.5f);
	glVertex3f(-3.0f, 10.0f, -3.0f);
	glTexCoord2f(0.25f + x, 0.75f);
	glVertex3f(3.0f, 10.0f, -3.0f);
	glTexCoord2f(0.0f + x, 0.75f);
	glVertex3f(3.0f, -10.0f, -3.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.25f + x, 0.75f);
	glVertex3f(-3.0f, -10.0f, -3.0f);
	glTexCoord2f(0.75f + x, 0.75f);
	glVertex3f(-3.0f, 10.0f, -3.0f);
	glTexCoord2f(0.75f + x, 1.0f);
	glVertex3f(-3.0f, 10.0f, 3.0f);
	glTexCoord2f(0.25f + x, 1.0f);
	glVertex3f(-3.0f, -10.0f, 3.0f);
	glEnd();
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

void DivideTriangle(float *a, float *b, float *c, int level)
{
	GLfloat v[3][3];
	int j;
	if (level > 0)
	{
		for (j = 0; j < 3; j++) 
		{
			v[0][j] = (a[j] + b[j]) / 2;
		}
		for (j = 0; j < 3; j++) 
		{
			v[1][j] = (a[j] + c[j]) / 2;
		}
		for (j = 0; j < 3; j++) 
		{
			v[2][j] = (b[j] + c[j]) / 2;
		}

		DivideTriangle(a, v[0], v[1], level - 1);
		DivideTriangle(v[0], b, v[2], level - 1);
		DivideTriangle(v[1], v[2], c, level - 1);
	}
	else 
	{
		DrawTriangle(a, b, c);
	}
}

void DrawTriangle(float *a, float *b, float *c)
{
	glBegin(GL_TRIANGLES);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}

GLubyte * LoadDIBitmap(const char* filename, BITMAPINFO** info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	// 바이너리 읽기 모드로 파일을 연다 
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;

	// 비트맵 파일 헤더를 읽는다. 
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
	{
		fclose(fp);
		return NULL;
	}

	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB')
	{
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
	{
		fclose(fp);
		exit(0);
		return NULL;
	}

	// 비트맵 인포 헤더를 읽는다. 
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize)
	{
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 *  abs((*info)->bmiHeader.biHeight);

	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL)
	{
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize)
	{
		free(*info);
		free(bits);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return bits;
}

void LoadTexture()
{
	glGenTextures(6, texture);

	// 1
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	pBytes = LoadDIBitmap("35-1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 194, 194, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 2
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	pBytes = LoadDIBitmap("35-2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 225, 225, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 3
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	pBytes = LoadDIBitmap("35-3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 279, 279, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 4
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	pBytes = LoadDIBitmap("37.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 683, 341, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// background
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	pBytes = LoadDIBitmap("background.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 743, 525, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 캐릭터
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	pBytes = LoadDIBitmap("rainicorn.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 500, 260, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
}