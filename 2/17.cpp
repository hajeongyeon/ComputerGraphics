#include <GL/freeglut.h>
#include <iostream>
using namespace std;

#define RADIAN 0.0174532
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

void SetupRC();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void MenuFunc(int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void DrawSun();
void DrawEarth();
void DrawJupiter();
void DrawNeptune();
void DrawMoon();
void DrawEuropa();
void DrawTriton();

//
bool isSolid;

int EarthDegree, JupiterDegree, NeptuneDegree;
float EarthX, EarthZ;
float JupiterX, JupiterZ;
float NeptuneX, NeptuneZ; 
float MoonX, MoonZ;
float EuropaX, EuropaZ;
float TritonX, TritonZ;

bool isPerspective;

void main(int argc, char *argv[])
{
	int SolidMenu, WireMenu;

	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 800); // 윈도우의 크기 지정
	glutCreateWindow("실습 17"); // 윈도우 생성 (윈도우 이름)
	SetupRC(); // 상태 변수 초기화 함수

	glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Solid", 1);
	glutAddMenuEntry("Wire", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glutMainLoop();
}

// 초기화 함수
void SetupRC()
{
	isSolid = true;

	EarthDegree = 0, JupiterDegree = 0, NeptuneDegree = 0;
	EarthX = 10.0f, EarthZ = 0.0f;
	JupiterX = 10.0f, JupiterZ = 0.0f;
	NeptuneX = 10.0f, NeptuneZ = 0.0f;
	MoonX = 2.5f, MoonZ = 0.0f;
	EuropaX = 2.5f, EuropaZ = 0.0f;
	TritonX = 2.5f, TritonZ = 0.0f;

	isPerspective = true;
}

// 메뉴
void MenuFunc(int button)
{
	switch (button)
	{
	case 1:
		isSolid = true;
		break;

	case 2:
		isSolid = false;
		break;
	}

	glutPostRedisplay();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	printf("%d\n", isPerspective);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

		if (!isPerspective)
		{
			float halfY = 20 * sqrt(1 + (WINDOW_HEIGHT / WINDOW_WIDTH) * (WINDOW_HEIGHT / WINDOW_WIDTH)) / 2.0f * RADIAN;
			float top = -150 * tan(halfY);
			float right = top * tan(halfY) * WINDOW_WIDTH / WINDOW_HEIGHT;
			glOrtho(-right, right, -top, top, -400, 400);
			glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
			//glRotatef(5.0f, 1.0f, 1.0f, 0.0f);
			//glScalef(1.9f, 1.9f, 1.9f);
		}
		else
		{
			gluPerspective(60.0f, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0, 1000.0);
			glTranslatef(0.0, 0.0, -30.0);
		}
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
	
		DrawSun();
		DrawEarth();
		DrawJupiter();
		DrawNeptune();
	glPopMatrix();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	// 관측 변환: 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능)
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p': case 'P':
		if (isPerspective)
			isPerspective = false;
		else
			isPerspective = true;
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	EarthX = 10.0f * cos(EarthDegree * RADIAN);
	EarthZ = 10.0f * sin(EarthDegree * RADIAN);
	JupiterX = 10.0f * cos(JupiterDegree * RADIAN);
	JupiterZ = 10.0f * sin(JupiterDegree * RADIAN);
	NeptuneX = 10.0f * cos(NeptuneDegree * RADIAN);
	NeptuneZ = 10.0f * sin(NeptuneDegree * RADIAN);

	MoonX = 2.5f * cos(EarthDegree * 10 * RADIAN);
	MoonZ = 2.5f * sin(EarthDegree * 10 * RADIAN);
	EuropaX = 2.5f * cos(JupiterDegree * 10 * RADIAN);
	EuropaZ = 2.5f * sin(JupiterDegree * 10 * RADIAN);
	TritonX = 2.5f * cos(NeptuneDegree * 10 * RADIAN);
	TritonZ = 2.5f * sin(NeptuneDegree * 10 * RADIAN);

	EarthDegree += 5;
	JupiterDegree += 3;
	NeptuneDegree += 1;

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawSun()
{
	glPushMatrix();
		glColor3f(0.85f, 0.0f, 0.0f);
		if (isSolid)
			glutSolidSphere(3.0, 20.0, 20.0);
		else
			glutWireSphere(3.0, 20.0, 20.0);
	glPopMatrix();
}

void DrawEarth()
{
	glPushMatrix();
		glColor3f(0.0f, 0.85f, 0.0f);

		// 행성 궤도
		glPushMatrix();
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < 360; i++)
			{
				float angle = i * RADIAN;
				glVertex3f(10.0f * cos(angle), 0.0f, 10.0f * sin(angle));
			}
			glEnd();
		glPopMatrix();
	
		// 행성
		glPushMatrix();
			glTranslatef(EarthX, 0.0f, EarthZ);
			if (isSolid)
				glutSolidSphere(2.0, 20.0, 20.0);
			else
				glutWireSphere(2.0, 20.0, 20.0);
			DrawMoon();
		glPopMatrix();
	glPopMatrix();
}

void DrawJupiter()
{
	glPushMatrix();
		glColor3f(0.6f, 0.5f, 0.1f);
		glRotatef(45.0f, 1.0f, 0.0f, 1.0f);
	
		// 궤도
		glPushMatrix();
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < 360; i++)
			{
				float angle = i * RADIAN;
				glVertex3f(10.0f * cos(angle), 0.0f, 10.0f * sin(angle));
			}
			glEnd();
		glPopMatrix();
	
		// 행성
		glPushMatrix();
			glTranslatef(JupiterX, 0.0f, JupiterZ);
			if (isSolid)
				glutSolidSphere(2.0, 20.0, 20.0);
			else
				glutWireSphere(2.0, 20.0, 20.0);
			DrawEuropa();
		glPopMatrix();
	glPopMatrix();
}

void DrawNeptune()
{
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.85f);
		glRotatef(-45.0f, 1.0f, 0.0f, 1.0f);
	
		// 궤도
		glPushMatrix();
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < 360; i++)
			{
				float angle = i * RADIAN;
				glVertex3f(10.0f * cos(angle), 0.0f, 10.0f * sin(angle));
			}
			glEnd();
		glPopMatrix();
	
		// 행성
		glPushMatrix();
			glTranslatef(NeptuneX, 0.0f, NeptuneZ);
			if (isSolid) 
				glutSolidSphere(2.0, 20.0, 20.0);
			else 
				glutWireSphere(2.0, 20.0, 20.0);
			DrawTriton();
		glPopMatrix();
	glPopMatrix();
}

void DrawMoon()
{
	glColor3f(0.5f, 0.5f, 0.5f);

	// 위성 궤도
	glPushMatrix();
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 360; i++)
		{
			float angle = i * RADIAN;
			glVertex3f(2.5f * cos(angle), 0.0f, 2.5f * sin(angle));
		}
		glEnd();
	glPopMatrix();
	
	// 위성
	glPushMatrix();
		glTranslatef(MoonX, 0.0f, MoonZ);
		if (isSolid)
			glutSolidSphere(0.5, 20.0, 20.0);
		else
			glutWireSphere(0.5, 20.0, 20.0);
	glPopMatrix();
}

void DrawEuropa()
{
	glColor3f(0.0f, 0.5f, 0.35f);

	// 위성 궤도
	glPushMatrix();
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 360; i++)
		{
			float angle = i * RADIAN;
			glVertex3f(2.5f * cos(angle), 0.0f, 2.5f * sin(angle));
		}
		glEnd();
	glPopMatrix();

	// 위성
	glPushMatrix();
		glTranslatef(EuropaX, 0.0f, EuropaZ);
		if (isSolid)
			glutSolidSphere(0.5, 20.0, 20.0);
		else
			glutWireSphere(0.5, 20.0, 20.0);
	glPopMatrix();
}

void DrawTriton()
{
	glColor3f(1.0f, 1.5f, 0.5f);

	// 위성 궤도
	glPushMatrix();
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 360; i++)
		{
			float angle = i * RADIAN;
			glVertex3f(2.5f * cos(angle), 0.0f, 2.5f * sin(angle));
		}
		glEnd();
	glPopMatrix();

	// 위성
	glPushMatrix();
		glTranslatef(TritonX, 0.0f, TritonZ);
		if (isSolid)
			glutSolidSphere(0.5, 20.0, 20.0);
		else
			glutWireSphere(0.5, 20.0, 20.0);
	glPopMatrix();
}