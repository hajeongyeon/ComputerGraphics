#include <GL/freeglut.h>
#include <iostream>
using namespace std;

#define RADIAN 0.0174532

void SetupRC();
GLvoid drawScene(GLvoid);
void Reshape(int w, int h);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

int degree;
bool nflight1, nflight2, isRev;

GLfloat AmbientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat DiffuseLight1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat SpecularLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos1[] = { 10.0f, 0.0f, 0.0f, 1.0f };
GLfloat gray1[] = { 0.25f, 0.25f, 0.25f, 1.0f };

GLfloat DiffuseLight2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat SpecularLight2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos2[] = { -10.0f, 0.0f, 0.0f, 1.0f };
GLfloat gray2[] = { 0.25f, 0.25f, 0.25f, 1.0f };

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 31"); // 윈도우 생성 (윈도우 이름)
	SetupRC(); // 상태 변수 초기화 함수
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}

void SetupRC()
{
	degree = 0;
	nflight1 = false, nflight2 = false, isRev = false;
}

GLvoid drawScene(GLvoid)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기

	glLoadIdentity();

	// 전역 주변광
	glEnable(GL_LIGHTING); 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0); 
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

	glutSolidSphere(5.0, 20, 20);

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
		lightPos1[0] = 10.0f * cos(degree * RADIAN);
		lightPos1[2] = 10.0f * sin(degree * RADIAN);
		lightPos2[0] = -10.0f * cos(degree * RADIAN);
		lightPos2[2] = -10.0f * sin(degree * RADIAN);

		degree += 1;
		break;

	case 'Y':
		lightPos1[0] = 10.0f * cos(degree * RADIAN);
		lightPos1[2] = 10.0f * sin(degree * RADIAN);
		lightPos2[0] = -10.0f * cos(degree * RADIAN);
		lightPos2[2] = -10.0f * sin(degree * RADIAN);

		degree += 1;
		break;

	case 'a':
		isRev = true;
		break;

	case 'A':
		isRev = false;
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
	if (isRev)
	{
		lightPos1[0] = 10.0f * cos(degree * RADIAN);
		lightPos1[2] = 10.0f * sin(degree * RADIAN);
		lightPos2[0] = -10.0f * cos(degree * RADIAN);
		lightPos2[2] = -10.0f * sin(degree * RADIAN);

		degree += 5;
	}							
	
	glutPostRedisplay();		
	glutTimerFunc(100, TimerFunction, 1);
}