#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
using namespace std;

enum BlendFunc
{
	ONEALPHA,
	ZEROALPHA,
	ONECOLOR,
	ZEROCOLOR,
	ONE_SRCALPHA,
	SRCALPHA,
	SRCCOLOR,
	ONE_DSRCOLOR,
	ONE_SRCCOLOR
};

void SetupRC();
GLvoid drawScene(GLvoid);
void Reshape(int w, int h);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void DrawObjects(double, double, BlendFunc, BlendFunc, int);
void DrawRectangle();
float Blend(BlendFunc);

GLfloat ambientLignt[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat Red[] = { 1.0,0.0,0.0 };
GLfloat Blue[] = { 0.0,0.0,1.0 };
GLfloat Green[] = { 0.0,1.0,0.0 };

GLfloat Dir[] = { 1,-1,0 };
GLfloat Pos[] = { -100,100,0 };

GLfloat Rect[] = { 150,150,0 };
GLfloat Alpha[9][3];
int g_selectedTag{ 4 };
double g_TagAlpha[3];

char *blendname[9];
int len;

int main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 38"); // 윈도우 생성 (윈도우 이름)
	SetupRC(); // 상태 변수 초기화 함수
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}

void SetupRC()
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 9; ++i)
	{
		Alpha[i][0] = (rand() % 10 + 1) / 10.0f;
		Alpha[i][1] = (rand() % 10 + 1) / 10.0f;
		Alpha[i][2] = (rand() % 10 + 1) / 10.0f;
	}

	blendname[0] = "GL_ONE, GL_ZERO";
	blendname[1] = "GL_ZERO, GL_ONE";
	blendname[2] = "GL_ONE, GL_ONE";
	blendname[3] = "GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA";
	blendname[4] = "GL_SRC_ALPHA, GL_ONE";
	blendname[5] = "GL_ZERO, GL_SRC_COLOR";
	blendname[6] = "GL_ONE_MINUS_DST_ALPHA, GL_ZERO";
	blendname[7] = "GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA";
	blendname[8] = "GL_ONE, GL_ONE";
}

//윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기

	glLoadIdentity();

	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLignt);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Dir);
	glLightfv(GL_LIGHT0, GL_POSITION, Pos);
	glEnable(GL_LIGHT0);

	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(18.0f, 10.0f); // 문자 출력할 위치 설정 
	len = (int)strlen(blendname[0]);
	for (int j = 0; j < len; j++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, blendname[0][j]);

	glRasterPos2f(118.0f, 10.0f); // 문자 출력할 위치 설정 
	len = (int)strlen(blendname[1]);
	for (int j = 0; j < len; j++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, blendname[1][j]);

	glRasterPos2f(220.0f, 10.0f); // 문자 출력할 위치 설정 
	len = (int)strlen(blendname[2]);
	for (int j = 0; j < len; j++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, blendname[2][j]);

	glRasterPos2f(5.0f, 100.0f); // 문자 출력할 위치 설정 
	len = (int)strlen(blendname[3]);
	for (int j = 0; j < len; j++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, blendname[3][j]);

	glRasterPos2f(105.0f, 85.0f); // 문자 출력할 위치 설정 
	int len = (int)strlen(blendname[4]);
	for (int j = 0; j < len; j++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, blendname[4][j]);

	glRasterPos2f(200.0f, 100.0f); // 문자 출력할 위치 설정 
	len = (int)strlen(blendname[5]);
	for (int j = 0; j < len; j++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, blendname[5][j]);

	glRasterPos2f(5.0f, 200.0f); // 문자 출력할 위치 설정 
	len = (int)strlen(blendname[6]);
	for (int j = 0; j < len; j++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, blendname[6][j]);

	glRasterPos2f(85.0f, 185.0f); // 문자 출력할 위치 설정 
	len = (int)strlen(blendname[7]);
	for (int j = 0; j < len; j++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, blendname[7][j]);

	glRasterPos2f(220.0f, 200.0f); // 문자 출력할 위치 설정 
	len = (int)strlen(blendname[8]);
	for (int j = 0; j < len; j++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, blendname[8][j]);

	DrawObjects(50, 250, ONEALPHA, ZEROALPHA, 0);
	DrawObjects(150, 250, ZEROCOLOR, ONECOLOR, 1);
	DrawObjects(250, 250, ONEALPHA, ONEALPHA, 2);

	DrawObjects(50, 150, SRCALPHA, ONE_SRCALPHA, 3);
	DrawObjects(150, 150, SRCALPHA, ONEALPHA, 4);
	DrawObjects(250, 150, ZEROCOLOR, SRCCOLOR, 5);

	DrawObjects(50, 50, ONE_DSRCOLOR, ZEROALPHA, 6);
	DrawObjects(150, 50, SRCALPHA, ONE_SRCCOLOR, 7);
	DrawObjects(250, 50, ONEALPHA, ONEALPHA, 8);

	DrawRectangle();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, 300.0, 0.0, 300.0, -300.0, 300.0);

	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		if (Rect[1] != 250) { Rect[1] += 100; g_selectedTag -= 3; }
		break;

	case 'a':
		if (Rect[0] != 50) { Rect[0] -= 100; g_selectedTag -= 1; }
		break;

	case 'd':
		if (Rect[0] != 250) { Rect[0] += 100; g_selectedTag += 1; }
		break;

	case 's':
		if (Rect[1] != 50) { Rect[1] -= 100; g_selectedTag += 3; }
		break;

	case 'i':
		g_TagAlpha[0] -= 0.1;
		break;

	case 'o':
		g_TagAlpha[0] += 0.1;
		break;

	case 'k':
		g_TagAlpha[1] -= 0.1;
		break;

	case 'l':
		g_TagAlpha[1] += 0.1;
		break;

	case 'n':
		g_TagAlpha[2] -= 0.1;
		break;

	case 'm':
		g_TagAlpha[2] += 0.1;
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
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawObjects(double x, double y, BlendFunc b1, BlendFunc b2, int tag)
{
	if (tag == g_selectedTag)
	{
		Alpha[tag][0] += g_TagAlpha[0];      Alpha[tag][1] += g_TagAlpha[1];      Alpha[tag][2] += g_TagAlpha[2];
		g_TagAlpha[0] = 0;
		g_TagAlpha[1] = 0;
		g_TagAlpha[2] = 0;
	}

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 64);

	glBlendFunc(Blend(b1), Blend(b2));

	// 원뿔
	glColor4f(Green[0], Green[1], Green[2], Alpha[tag][0]);
	glPushMatrix();
		glTranslated(x + 15, y + 5, 50);
		glRotated(-90, 1, 0, 0);
		glutSolidCone(20.0, 25, 10, 10);
	glPopMatrix();

	// 구
	glColor4f(Blue[0], Blue[1], Blue[2], Alpha[tag][1]);
	glPushMatrix();
		glTranslated(x + 5, y - 10, 0);
		glutSolidSphere(20.0, 30, 30);
	glPopMatrix();

	// 주전자
	glColor4f(Red[0], Red[1], Red[2], Alpha[tag][2]);
	glPushMatrix();
		glTranslated(x - 5, y, -50);
		glutSolidTeapot(20.0);
	glPopMatrix();
}

void DrawRectangle()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glTranslated(Rect[0], Rect[1], Rect[2]);
		glutWireCube(95.0);
	glPopMatrix();
}

float Blend(BlendFunc b)
{
	switch (b)
	{
	case ONEALPHA:
		return  GL_ONE;
		break;

	case   ZEROALPHA:
		return GL_ZERO;
		break;

	case   ONE_SRCALPHA:
		return GL_ONE_MINUS_SRC_ALPHA;
		break;

	case   SRCALPHA:
		return GL_SRC_ALPHA;
		break;

	case   SRCCOLOR:
		return GL_SRC_COLOR;
		break;

	case   ONE_DSRCOLOR:
		return GL_ONE_MINUS_DST_COLOR;
		break;

	case ONE_SRCCOLOR:
		return GL_ONE_MINUS_SRC_COLOR;
		break;
	}
}