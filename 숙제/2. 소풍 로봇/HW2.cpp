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
	srand((unsigned int)time(NULL));

	xRot = 0.0f, yRot = 0.0f, zoom = 45.0f;

	isOrtho = true, isEdit = true;

	for (int i = 0; i < 10; ++i)
	{
		obj[i].x = rand() % 400 - 200;
		obj[i].y = 0;
		obj[i].z = rand() % 400 - 200;
	}
	num = 0;
	for (int i = 0; i < 9; ++i)
	{
		ctrlpoints[i][0] = -1000;
		ctrlpoints[i][1] = rand() % 100 - 50;
		ctrlpoints[i][2] = -1000;
	}

	WeatherType = 1;
	for (int i = 0; i < 100; ++i)
	{
		weather[i].x = rand() % 400 - 200;
		weather[i].y = rand() % 200 + 100;
		weather[i].z = rand() % 400 - 200;
	}
}

GLvoid drawScene(GLvoid)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기

	glLoadIdentity();

	gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

	if (isOrtho)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	}

	glRotatef(-xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
		glTranslatef(0.0f, -100.0f, 0.0f);
	
		// 바닥
		glPushMatrix();
			glScalef(1.0f, 0.01f, 1.0f);
			glColor3f(0.5f, 0.5f, 0.5f);
			glutSolidCube(500.0f);
		glPopMatrix();
	
		DrawTree();
	glPopMatrix();

	if (num > 1)
	{
		for (int i = 0; i < num; i += 3)
		{
			int n = num;
			if (num > 3) n = 4;
			glColor3f(1.0f, 1.0f, 0.0f);
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, n, &ctrlpoints[i][0]);
			glEnable(GL_MAP1_VERTEX_3);
			glMapGrid1f(10.0, 0.0, 1.0);
			glEvalMesh1(GL_LINE, 0, 10);
			glDisable(GL_MAP1_VERTEX_3);
		}
	}

	if (isEdit)
	{
		glPointSize(5.0);
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POINTS);
		for (int i = 0; i < num; i++)
			glVertex3fv(&ctrlpoints[i][0]);
		glEnd();
	}

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
		if (!isEdit) WeatherType = 1;
		break;

	case '2':
		if (!isEdit) WeatherType = 2;
		break;

	case '3':
		if (!isEdit) WeatherType = 3;
		break;

	case '-':
		if (isEdit)
		{
			if (isOrtho) isOrtho = false;
			else isOrtho = true;
		}
		break;

	case 'z':
		if (!isEdit)
		{
			zoom += 10;
			Reshape(800, 600);
		}
		break;
		
	case 'Z':
		if (!isEdit)
		{
			zoom -= 10;
			Reshape(800, 600);
		}
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

	case 13:				// 엔터 키
		if (num > 8)
		{
			isEdit = false;
			isOrtho = false;
			Reshape(800, 600);
		}
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
		if (isOrtho && num < 9)
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
						ctrlpoints[i][2] = y - 300;

						if (num > 7)
						{
							ctrlpoints[i][0] = ctrlpoints[0][0];
							ctrlpoints[i][1] = ctrlpoints[0][1];
							ctrlpoints[i][2] = ctrlpoints[0][2];
						}
					}

					++num;
				}
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
		if (isEdit)
		{
			if (isOrtho)
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
			else
			{
				if (x - 400 < 250 && x - 400 > -250 && y - 300 < 100)
				{
					for (int i = 1; i < num - 1; ++i)
					{
						if (ctrlpoints[i][0] > (x - 400) - 5 && ctrlpoints[i][0] < (x - 400) + 5
							&& -ctrlpoints[i][1] > (y - 300) - 5 && -ctrlpoints[i][1] < (y - 300) + 5)
						{
							ctrlpoints[i][1] = -(y - 300);
						}
					}
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
			weather[i].y -= 3.0f;

			if (weather[i].y < -100.0f)
			{
				weather[i].x = rand() % 400 - 200;
				weather[i].y = rand() % 200 + 100;
				weather[i].z = rand() % 400 - 200;
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}


////////////////////////////////////////////////////////

void DrawTree()
{
	for (int i = 0; i < 10; ++i)
	{
		glPushMatrix();
			glTranslatef(obj[i].x, obj[i].y + 35.0f, obj[i].z);
			glPushMatrix();
				glScalef(1.0f, 7.0f, 1.0f);
				glColor3f(0.43f, 0.0f, 0.0f);
				glutSolidCube(10.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 35.0f, 0.0f);
				glColor3f(0.0f, 1.0f, 0.0f);
				glutSolidSphere(15.0, 20, 20);
			glPopMatrix();
		glPopMatrix();
	}
}

void DrawRobot()
{
}

void DrawWeather()
{
	if (WeatherType == 2)
	{
		for (int i = 0; i < 100; ++i)
		{
			glPushMatrix();
				glTranslatef(weather[i].x, weather[i].y, weather[i].z);
				glColor3f(1.0f, 1.0f, 1.0f);
				glutSolidSphere(0.3, 10, 10);
			glPopMatrix();
		}
	}
	else if (WeatherType == 3)
	{
		for (int i = 0; i < 100; ++i)
		{
			glPushMatrix();
				glTranslatef(weather[i].x, weather[i].y, weather[i].z);
				glScalef(0.1f, 5.0f, 0.1f);
				glColor3f(1.0f, 1.0f, 1.0f);
				glutSolidCube(1.0);
			glPopMatrix();
		}
	}
}