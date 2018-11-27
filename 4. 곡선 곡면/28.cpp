#include <GL/freeglut.h>
#include <iostream>
using namespace std;

void SetupRC();
GLvoid drawScene(GLvoid);
void Reshape(int w, int h);
void Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);
void Motion(int, int);

bool right_button;
int num;
GLfloat ctrlpoints[19][3];

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 28"); // 윈도우 생성 (윈도우 이름)
	SetupRC(); // 상태 변수 초기화 함수
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();
}

void SetupRC() 
{
	right_button = false;

	num = 0;

	for (int i = 0; i < 19; ++i)
	{
		ctrlpoints[i][0] = 0;
		ctrlpoints[i][1] = 0;
		ctrlpoints[i][2] = 0;
	}
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	
	// 곡선 제어점 설정: 매개변수 u의 최소값은 0, 최대값은 1,
	// 제어점간의 데이터 개수는 3, 제어점은 4개를 사용
	if (num > 1)
	{
		for (int i = 0; i < num; i += 3)
		{
			int n = num;
			if (num > 3) n = 4;
			glColor3f(1.0f, 1.0f, 0.0f);
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, n, &ctrlpoints[i][0]);
			glEnable(GL_MAP1_VERTEX_3);
			// 제어점 사이의 곡선위의 점들을 계산한다. 제어점 사이를 10개로 나누어 그 점들을 연결한다. -> 곡선위의 점 계산
			glMapGrid1f(10.0, 0.0, 1.0); // 매개변수 0~1 사이를 10개로 나눔
			glEvalMesh1(GL_LINE, 0, 10); // 선분으로 나눈 부분 0~10까지 선으로 그림
			glDisable(GL_MAP1_VERTEX_3);
		}
	}

	// 제어점에 점을 그린다.
	glPointSize(5.0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POINTS); 
	for (int i = 0; i < num; i++) 
		glVertex3fv(&ctrlpoints[i][0]);
	glEnd();

	glutSwapBuffers(); // 결과 출력
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r': case 'R':
		SetupRC();
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = num; i < 22; ++i)
		{
			ctrlpoints[i][0] = x;
			ctrlpoints[i][1] = y;
			ctrlpoints[i][2] = 0;
		}

		++num;
		if (num > 19) num = 0;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		right_button = true;
	}
	else right_button = false;
}

void Motion(int x , int y)
{
	if (right_button)
	{
		for (int i = 0; i < num; ++i)
		{
			if (ctrlpoints[i][0] > x - 5 && ctrlpoints[i][0] < x + 5 
				&& ctrlpoints[i][1] > y - 5 && ctrlpoints[i][1] < y + 5)
			{
				ctrlpoints[i][0] = x;
				ctrlpoints[i][1] = y;
			}
		}
	}
}