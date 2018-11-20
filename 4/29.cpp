#include <GL/freeglut.h>
#include <iostream>
using namespace std;

void SetupRC();
GLvoid drawScene(GLvoid);
void Reshape(int w, int h);
void Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);
void TimerFunction(int);

int xRot, yRot, zRot;
int num, tmp, dir1, dir2, dir3;					// tmp : 제어점 좌표 비우기 위해 사용한 변수
GLfloat ctrlpoints[10][3][3];
bool isQ, isWave, isAll;

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 29"); // 윈도우 생성 (윈도우 이름)
	SetupRC(); // 상태 변수 초기화 함수
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}

void SetupRC()
{
	xRot = 0, yRot = 0, zRot = 0;
	num = 0, tmp = 0, dir1 = 1, dir2 = 1, dir3 = 1;

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			ctrlpoints[i][j][0] = -1000;
			ctrlpoints[i][j][1] = -1000;
			ctrlpoints[i][j][2] = -1000;
		}
	}

	isQ = false, isWave = false, isAll = false;
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기

	glLoadIdentity();

	// 각도 변환
	if (isQ)
	{
		glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	}
	else
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	// 좌표축
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-500.0f, 0.0f, 0.0f);
	glVertex3f(500.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -500.0f, 0.0f);
	glVertex3f(0.0f, 500.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -500.0f);
	glVertex3f(0.0f, 0.0f, 500.0f);
	glEnd();

	// 점 다 찍었을 때 베지에 곡면 그리기
	if (isAll)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		// 곡면 제어점 설정 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// 선을 이용하여 그리드 연결 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glDisable(GL_MAP2_VERTEX_3);

		// 곡면 제어점 설정 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[2][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// 선을 이용하여 그리드 연결 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glDisable(GL_MAP2_VERTEX_3);

		// 곡면 제어점 설정 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[4][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// 선을 이용하여 그리드 연결 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glDisable(GL_MAP2_VERTEX_3);

		// 곡면 제어점 설정 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[6][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// 선을 이용하여 그리드 연결 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glDisable(GL_MAP2_VERTEX_3);
	}

	// 마우스로 찍은 부분에 점을 그린다.
	glPointSize(5.0);
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			glVertex3fv(ctrlpoints[i][j]);
		}
	}
	glEnd();

	// 사각형 그리기
	if (!isAll)
	{
		if (num > 3)
		{
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);
			glVertex2f(ctrlpoints[0][0][0], ctrlpoints[0][0][2]);
			glVertex2f(ctrlpoints[0][2][0], ctrlpoints[0][2][2]);
			glVertex2f(ctrlpoints[3][2][0], ctrlpoints[3][2][2]);
			glVertex2f(ctrlpoints[3][0][0], ctrlpoints[3][0][2]);
			glEnd();
		}
		if (num > 6)
		{
			glBegin(GL_QUADS);
			glVertex2f(ctrlpoints[3][2][0], ctrlpoints[3][2][2]);
			glVertex2f(ctrlpoints[3][0][0], ctrlpoints[3][0][2]);
			glVertex2f(ctrlpoints[6][0][0], ctrlpoints[6][0][2]);
			glVertex2f(ctrlpoints[6][2][0], ctrlpoints[6][2][2]);
			glEnd();
		}
	}

	glutSwapBuffers(); // 결과 출력
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 
	// 직각 투영
	glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);

	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r': case 'R':
		SetupRC();
		break;

	case 'v': case 'V':					// 쿼터뷰로 시점 변환
		if (isAll)						// 다 그렸을 때만
		{
			if (isQ) isQ = false;
			else isQ = true;
		}
		break;

	case 'w': case 'W':					// 물결
		if (isWave) isWave = false;
		else isWave = true;
		break;

	case 'x':
		xRot++;
		break;

	case 'X':
		xRot--;
		break;

	case 'y':
		yRot++;
		break;

	case 'Y':
		yRot--;
		break;

	case 'z':
		zRot++;
		break;

	case 'Z':
		zRot--;
		break;

	case 'q': case 'Q':
		PostQuitMessage(0);
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
		if (num < 12)
		{
			if (tmp == 0)
			{
				ctrlpoints[num][0][0] = x - 400;
				ctrlpoints[num][0][1] = 0;
				ctrlpoints[num][0][2] = 300 - y;
			}
			else
			{
				ctrlpoints[num][2][0] = x - 400;
				ctrlpoints[num][2][1] = 0;
				ctrlpoints[num][2][2] = 300 - y;
			}

			tmp = (tmp + 1) % 2;

			if (tmp == 0)
				num += 3;
		}

		if (num == 12 && !isAll)
		{
			for (int i = 0; i < 7; i += 3) {
				ctrlpoints[i + 1][0][0] = ctrlpoints[i][0][0] + (ctrlpoints[i + 3][0][0] - ctrlpoints[i][0][0]) / 3;
				ctrlpoints[i + 1][0][1] = 0;
				ctrlpoints[i + 1][0][2] = ctrlpoints[i][0][2] + (ctrlpoints[i + 3][0][2] - ctrlpoints[i][0][2]) / 3;
				ctrlpoints[i + 1][2][0] = ctrlpoints[i][2][0] + (ctrlpoints[i + 3][2][0] - ctrlpoints[i][2][0]) / 3;
				ctrlpoints[i + 1][2][2] = ctrlpoints[i][2][2] + (ctrlpoints[i + 3][2][2] - ctrlpoints[i][2][2]) / 3;

				ctrlpoints[i + 2][0][0] = ctrlpoints[i][0][0] + ((ctrlpoints[i + 3][0][0] - ctrlpoints[i][0][0]) / 3) * 2;
				ctrlpoints[i + 2][0][2] = ctrlpoints[i][0][2] + ((ctrlpoints[i + 3][0][2] - ctrlpoints[i][0][2]) / 3) * 2;
				ctrlpoints[i + 2][2][0] = ctrlpoints[i][2][0] + ((ctrlpoints[i + 3][2][0] - ctrlpoints[i][2][0]) / 3) * 2;
				ctrlpoints[i + 2][2][1] = 0;
				ctrlpoints[i + 2][2][2] = ctrlpoints[i][2][2] + ((ctrlpoints[i + 3][2][2] - ctrlpoints[i][2][2]) / 3) * 2;
			}

			for (int i = 0; i < 10; ++i) {
				ctrlpoints[i][1][0] = ctrlpoints[i][0][0] + (ctrlpoints[i][2][0] - ctrlpoints[i][0][0] / 2);
				ctrlpoints[i][1][2] = ctrlpoints[i][0][2] + (ctrlpoints[i][2][2] - ctrlpoints[i][0][2] / 2);
				ctrlpoints[i][1][1] = 0;
			}

			for (int i = 0; i < 10; ++i)
				for (int j = 0; j < 3; ++j)
					ctrlpoints[i][j][1] = 0;

			isAll = true;
		}
	}
}

void TimerFunction(int value)
{
	if (isAll && isWave)
	{
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (i % 3 == 0)
				{
					if (j == 0)
						ctrlpoints[i][j][1] += 3 * dir1;
					else if (j == 1)
						ctrlpoints[i][j][1] -= 7 * dir2;
					else
						ctrlpoints[i][j][1] += 5 * dir3;
				}
				else if (i % 3 == 1)
				{
					if (j == 0)
						ctrlpoints[i][j][1] -= 3 * dir1;
					else if (j == 1)
						ctrlpoints[i][j][1] += 7 * dir2;
					else
						ctrlpoints[i][j][1] -= 5 * dir3;
				}
				else
				{
					if (j == 0)
						ctrlpoints[i][j][1] += 3 * dir1;
					else if (j == 1)
						ctrlpoints[i][j][1] += 7 * dir2;
					else
						ctrlpoints[i][j][1] -= 5 * dir3;
				}
			}
		}

		if (ctrlpoints[0][0][1] > 70.0f) dir1 *= -1;
		else if (ctrlpoints[0][0][1] < -70.0f) dir1 *= -1;

		if (ctrlpoints[0][1][1] > 70.0f) dir2 *= -1;
		else if (ctrlpoints[0][1][1] < -70.0f) dir2 *= -1;

		if (ctrlpoints[0][2][1] > 70.0f) dir3 *= -1;
		else if (ctrlpoints[0][2][1] < -70.0f) dir3 *= -1;
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}