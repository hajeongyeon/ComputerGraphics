#include "HW2.h"

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("숙제 2"); // 윈도우 생성 (윈도우 이름)
	SetupRC(); // 상태 변수 초기화 함수
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}

void SetupRC()
{
	xRot = 0.0f, yRot = 0.0f;

	isOrtho = true, isEdit = true;

	for (int i = 0; i < 10; ++i)
	{
		obj[i].x = rand() % 400 - 200;
		obj[i].y = 0;
		obj[i].z = rand() % 400 - 200;
	}
	num = 0;
	for (int i = 0; i < 5; ++i)
	{
		ctrlpoints[i][0] = -1000;
		ctrlpoints[i][1] = -1000;
		ctrlpoints[i][2] = -1000;
	}

	WeatherType = 1;
	for (int i = 0; i < 100; ++i)
	{
		weather[i].x = rand() % 30 - 15;
		weather[i].y = rand() % 20 + 10;
		weather[i].z = rand() % 30 - 15;
	}
}

GLvoid drawScene(GLvoid)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기

	glLoadIdentity();

	if (isOrtho)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	}
	else
	{
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	}

	glRotatef(-xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glTranslatef(0.0f, -100.0f, 0.0f);

	// 바닥
	glPushMatrix();
		glScalef(1.0f, 0.01f, 1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glutSolidCube(500.0f);
	glPopMatrix();

	// 장애물
	for (int i = 0; i < 10; ++i)
	{
		glPushMatrix();
			glTranslatef(obj[i].x, obj[i].y + 10.0f, obj[i].z);
			glScalef(1.0f, 3.0f, 1.0f);
			glColor3f(0.43f, 0.0f, 0.0f);
			glutSolidCube(10.0f);
		glPopMatrix();
	}
	glPopMatrix();

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

	DrawWeather();

	glutSwapBuffers(); // 결과 출력
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (isOrtho)
	{
		// 직각 투영
		glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
	}
	else
	{
		// 원근 투영
		gluPerspective(60.0f, w / h, 1.0, 1000.0);
		glTranslatef(0.0, 0.0, -30.0);
	}

	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		WeatherType = 1;
		break;

	case '2':
		WeatherType = 2;
		break;

	case '3':
		WeatherType = 3;
		break;

	case '-':
		if (isOrtho) isOrtho = false;
		else isOrtho = true;
		break;

	case 'z':
		break;
		
	case 'Z':
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

	case 'w': case 'W':
		break;

	case 'a': case 'A':
		break;

	case 's': case 'S':
		break;

	case 'd': case 'D':
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

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (x - 400 < 250 && x - 400 > -250 && y - 300 < 250 && y - 300 > -250)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (obj[j].x - 5 < x - 400 && obj[j].x + 5 > x - 400 && obj[j].z - 5 < y - 300 && obj[j].z + 5 > y - 300)
					isCP = true;
			}

			if (!isCP)
			{
				for (int i = num; i < 10; ++i)
				{
					ctrlpoints[i][0] = x - 400;
					ctrlpoints[i][1] = 0;
					ctrlpoints[i][2] = y - 300;

					if (num > 7)
					{
						ctrlpoints[i][0] = ctrlpoints[0][0];
						ctrlpoints[i][1] = 0;
						ctrlpoints[i][2] = ctrlpoints[0][2];
					}
				}

				++num;
				if (num > 9) num = 0;						// edit 종료
			}
		}
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		right_button = true;
	}
	else right_button = false;
}

void Motion(int x, int y)
{
	if (right_button)
	{
		if (x - 400 < 250 && x - 400 > -250 && y - 300 < 250 && y - 300 > -250)
		{
			for (int i = 1; i < num - 1; ++i)
			{
				if (ctrlpoints[i][0] > (x - 400) - 5 && ctrlpoints[i][0] < (x - 400) + 5
					&& ctrlpoints[i][2] > (y - 300) - 5 && ctrlpoints[i][2] < (y - 300) + 5)
				{
					ctrlpoints[i][0] = x - 400;
					ctrlpoints[i][2] = y - 300;
				}
			}
		}
	}
}

void TimerFunction(int value)
{
	if (WeatherType == 2 || WeatherType == 3)
	{
		for (int i = 0; i < 100; ++i)
		{
			weather[i].y -= 0.5f;

			if (weather[i].y < 0)
			{
				weather[i].x = rand() % 30 - 15;
				weather[i].y = rand() % 20 + 10;
				weather[i].z = rand() % 30 - 15;
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}


////////////////////////////////////////////////////////
void DrawWeather()
{
	if (WeatherType == 2)
	{
		for (int i = 0; i < 100; ++i)
		{
			glPushMatrix();
				glTranslatef(weather[i].x, weather[i].y, weather[i].z);
				glColor3f(1.0f, 1.0f, 1.0f);
				glutSolidSphere(0.1, 10, 10);
			glPopMatrix();
		}
	}
	else if (WeatherType == 3)
	{
		for (int i = 0; i < 100; ++i)
		{
			glPushMatrix();
				glTranslatef(weather[i].x, weather[i].y, weather[i].z);
				glScalef(0.01f, 1.0f, 0.01f);
				glColor3f(1.0f, 1.0f, 1.0f);
				glutSolidCube(1.0);
			glPopMatrix();
		}
	}
}