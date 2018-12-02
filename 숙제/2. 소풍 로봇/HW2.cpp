#include "HW2.h"

// ** 마우스 / 키보드 명령어
//	- 마우스 명령어
//		· 왼쪽 클릭 : 롤러코스터 코스 만들기(7번째 클릭에서 곡선이 이어집니다.)
//		· 오른쪽 클릭 : 제어점 위치 변경(첫번째 점과 마지막 점은 변경 불가)
//	- 키보드 명령어
//		· - 키 : XZ 평면, XY 평면 전환
//		· Enter 키 : 편집 완료
//		· 숫자 키 1, 2, 3 : 맑은 날씨, 눈 오는 날씨, 비 오는 날씨
//		· w / a / s / d 키 : 로봇 방향 변경
//		· Space Bar 키 : 총알 발사
//		· x, y 키 : x, y축으로 회전(대문자는 반대방향)
//		· [, { 키: x축으로 이동
//		· ], } 키: y축으로 이동
//		· z 키 : 줌 인 / 아웃
//		· r 키 : 초기화
//		· q 키 : 종료

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

	xTrs = 0.0f, yTrs = 0.0f, xRot = 0.0f, yRot = 0.0f, zoom = 150.0f;

	isOrtho = true, isEdit = true;
	isCP = false;
	isFire = false, BTcollision = false, BPcollision = false;

	for (int i = 0; i < 10; ++i)
	{
		obj[i].x = rand() % 400 - 200;
		obj[i].y = 0;
		obj[i].z = rand() % 400 - 200;
	}
	num = 0;
	for (int i = 0; i < 7; ++i)
	{
		ctrlpoints[i][0] = -1000;
		ctrlpoints[i][1] = -1000;
		ctrlpoints[i][2] = -1000;
	}
	for (int i = 0; i < 6; ++i)
	{
		tmp[i] = rand() % 100 + 50;
	}

	for (int i = 0; i < 2; ++i)
	{
		robot[i].RobotDir = 0, robot[i].RobotRot = 0;
		robot[i].LLeg = 0.0f, robot[i].RLeg = 0.0f, robot[i].LArm = 0.0f, robot[i].RArm = 0.0f;
		robot[i].LLegDir = 1, robot[i].RLegDir = -1, robot[i].LArmDir = -1, robot[i].RArmDir = 1;
		robot[i].MoveX = 0.0f, robot[i].MoveZ = 0.0f;
	}
	for(int k = 0; k < 2; ++k)
		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < 3; ++j)
				robot[k].capepoints[i][j][1] = -70.0f;

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

	glTranslatef(xTrs, 0.0f, 0.0f);
	glTranslatef(0.0f, yTrs, 0.0f);
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
		if (!isEdit)
		{
			DrawRobot();
		}
	glPopMatrix();

	if (num > 1)
	{
		for (int i = 0; i < num - 1; i += 3)
		{
			int n = num;
			if (num > 3) n = 4;
			glColor3f(1.0f, 1.0f, 0.0f);
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, n, &ctrlpoints[i][0]);
			glEnable(GL_MAP1_VERTEX_3);
			glMapGrid1f(10, 0.0f, 1.0f);
			glEvalMesh1(GL_LINE, 0, 10);
			glDisable(GL_MAP1_VERTEX_3);
		}
	}
	if (isEdit)
	{
		glPointSize(5.0);
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POINTS);
		for (int i = 0; i < 7; i++)
		{
			glVertex3fv(&ctrlpoints[i][0]);
		}
		glEnd();
	}
	else
	{
		for (int i = 0; i < 2; ++i)
		{
			DrawPillar(ctrlpoints[i * 3][0], ctrlpoints[i * 3][1], ctrlpoints[i * 3][2]);
		}
		DrawCape();
		DrawBullet();
		ROCollide();
		BOCollide();
		DrawWeather();
	}

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

	case '[':
		xTrs++;
		break;

	case '{':
		xTrs--;
		break;

	case ']':
		yTrs++;
		break;

	case '}':
		yTrs--;
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
		if (num > 6)
		{
			isEdit = false;
			isOrtho = false;

			zoom = 150.0f;

			for (int i = 0; i < 2; ++i)
			{
				robot[i].RobotDir = 0, robot[i].RobotRot = 0;
				robot[i].LLeg = 0.0f, robot[i].RLeg = 0.0f, robot[i].LArm = 0.0f, robot[i].RArm = 0.0f;
				robot[i].LLegDir = 1, robot[i].RLegDir = -1, robot[i].LArmDir = -1, robot[i].RArmDir = 1;
			}

			robot[0].RobotDir = 0, robot[0].RobotRot = 0;
			robot[1].RobotDir = 2, robot[1].RobotRot = 270;
			robot[0].MoveX = 0.0f, robot[0].MoveZ = 0.0f;
			robot[1].MoveX = 100.0f, robot[1].MoveZ = 100.0f;

			Reshape(800, 600);
		}
		break;

	case 32:				// 스페이스바 키
		if (!isEdit) isFire = true;
		break;

	case 'w': case 'W':
		robot[0].RobotDir = 1;
		break;

	case 'a': case 'A':
		robot[0].RobotDir = 2;
		break;

	case 's': case 'S':
		robot[0].RobotDir = 0;
		break;

	case 'd': case 'D':
		robot[0].RobotDir = 3;
		break;

	case 'r': case 'R':
		SetupRC();
		Reshape(800, 600);
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
		if (isOrtho && num < 7)
		{
			if (x - 400 < 250 && x - 400 > -250 && y - 300 < 250 && y - 300 > -250)
			{
				for (int j = 0; j < 10; ++j)
				{
					if (obj[j].x - 10 < x - 400 && obj[j].x + 10 > x - 400 && obj[j].z - 10 < y - 300 && obj[j].z + 10 > y - 300)
						isCP = true;
				}

				if (!isCP)
				{
					for (int i = num; i < 7; i++)
					{
						ctrlpoints[i][0] = x - 400;
						ctrlpoints[i][1] = tmp[num];
						ctrlpoints[i][2] = y - 300;

						if (num > 5)
						{
							ctrlpoints[i][0] = ctrlpoints[0][0];
							ctrlpoints[i][1] = ctrlpoints[0][1];
							ctrlpoints[i][2] = ctrlpoints[0][2];
						}
					}

					++num;
				}

				isCP = false;
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
						if (ctrlpoints[i][0] >(x - 400) - 5 && ctrlpoints[i][0] < (x - 400) + 5
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
				if (x - 400 < 250 && x - 400 > -250 && y - 300 < 100 && y - 300 > -80)
				{
					for (int i = 1; i < num - 1; ++i)
					{
						if (ctrlpoints[i][0] >(x - 400) - 5 && ctrlpoints[i][0] < (x - 400) + 5
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
	if (!isEdit)
	{
		for (int i = 0; i < 2; ++i)
		{
			robot[i].LLeg += 5.0f *robot[i].LLegDir;
			if (robot[i].LLeg > 30.0f || robot[i].LLeg < -30.0f) robot[i].LLegDir *= -1;

			robot[i].RLeg += 5.0f * robot[i].RLegDir;
			if (robot[i].RLeg > 30.0f || robot[i].RLeg < -30.0f) robot[i].RLegDir *= -1;

			robot[i].LArm += 5.0f * robot[i].LArmDir;
			if (robot[i].LArm > 30.0f || robot[i].LArm < -30.0f) robot[i].LArmDir *= -1;

			robot[i].RArm += 5.0f * robot[i].RArmDir;
			if (robot[i].RArm > 30.0f || robot[i].RArm < -30.0f) robot[i].RArmDir *= -1;


			if (robot[i].RobotDir == 0)
			{
				robot[i].RobotRot = 0;
				robot[i].MoveZ += 1.0f;
				if (robot[i].MoveZ > 250.0f) robot[i].MoveZ = 250.0f;
			}
			else if (robot[i].RobotDir == 1)
			{
				robot[i].RobotRot = 180;
				robot[i].MoveZ -= 1.0f;
				if (robot[i].MoveZ < -250.0f) robot[i].MoveZ = -250.0f;
			}
			else if (robot[i].RobotDir == 2)
			{
				robot[i].RobotRot = 270;
				robot[i].MoveX -= 1.0f;
				if (robot[i].MoveX < -250.0f) robot[i].MoveX = -250.0f;
			}
			else if (robot[i].RobotDir == 3)
			{
				robot[i].RobotRot = 90;
				robot[i].MoveX += 1.0f;
				if (robot[i].MoveX > 250.0f) robot[i].MoveX = 250.0f;
			}
		}

		for (iter = bullet.begin(); iter != bullet.end();)
		{
			if (iter->dir == 0)
			{
				iter->z += 10.0f;
				iter->time += 1;
			}
			else if (iter->dir == 1)
			{
				iter->z -= 10.0f;
				iter->time += 1;
			}
			else if (iter->dir == 2)
			{
				iter->x -= 10.0f;
				iter->time += 1;
			}
			else if (iter->dir == 3)
			{
				iter->x += 10.0f;
				iter->time += 1;
			}

			if (iter->time >= 100)
				iter = bullet.erase(bullet.begin());
			else
				++iter;
		}

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
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}


////////////////////////////////////////////////////////

void DrawPillar(float x, float y, float z)
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glTranslatef(0.0f, -150.0f, 0.0f);
		glScalef(1.0f, 30.0f, 1.0f);
		glColor3f(0.5f, 0.5f, 0.0f);
		glutSolidCube(10.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(10.0f);
	glPopMatrix();
}

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
	for (int i = 0; i < 2; ++i)
	{
		glPushMatrix();
		glTranslatef(0.0f, 20.0f, 0.0f);
		glTranslatef(robot[i].MoveX, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, robot[i].MoveZ);
		glRotatef(robot[i].RobotRot, 0.0f, 1.0f, 0.0f);

		if (i == 1)
		{
			// 몸통
			glPushMatrix();
				glScalef(0.8f, 1.0f, 0.5f);
				glColor3f(0.0f, 0.0f, 0.0f);
				glutSolidCube(21.0);
				glColor3f(1.0f, 1.0f, 1.0f);
				glutWireCube(21.0);
			glPopMatrix();
		}
		else
		{
			// 몸통
			glPushMatrix();
				glScalef(0.8f, 1.0f, 0.5f);
				glColor3f(1.0f, 1.0f, 1.0f);
				glutSolidCube(21.0);
				glColor3f(0.0f, 0.0f, 0.0f);
				glutWireCube(21.0);
			glPopMatrix();
		}

		if (i == 1)
		{
			// 머리
			glPushMatrix();
				glTranslatef(0.0f, 14.0f, 0.0f);
				glScalef(0.8f, 1.0f, 0.5f);
				glColor3f(0.0f, 0.0f, 0.0f);
				glutSolidCube(18.0);
				glColor3f(1.0f, 1.0f, 1.0f);
				glutWireCube(18.0);
			glPopMatrix();
		}
		else
		{
			// 머리
			glPushMatrix();
				glTranslatef(0.0f, 14.0f, 0.0f);
				glScalef(0.8f, 1.0f, 0.5f);
				glColor3f(1.0f, 1.0f, 1.0f);
				glutSolidCube(18.0);
				glColor3f(0.0f, 0.0f, 0.0f);
				glutWireCube(18.0);
			glPopMatrix();
		}

		// 코
		glPushMatrix();
		glTranslatef(0.0f, 14.0f, 4.5f);
		glScalef(0.8f, 1.0f, 0.5f);
		glColor3f(0.95f, 0.38f, 0.65f);
		glutSolidCube(4.5);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(4.5);
		glPopMatrix();

		// 왼팔
		glPushMatrix();
		glTranslatef(-9.8f, 0.0f, 0.0f);
		glTranslatef(0.0f, 7.0f, 0.0f);
		glRotatef(robot[i].LArm, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -7.0f, 0.0f);
		glScalef(0.1f, 1.0f, 0.1f);
		glColor3f(0.81f, 0.69f, 1.0f);
		glutSolidCube(22.5);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(22.5);
		glPopMatrix();

		// 오른팔
		glPushMatrix();
		glTranslatef(9.8f, 0.0f, 0.0f);
		glTranslatef(0.0f, 7.0f, 0.0f);
		glRotatef(robot[i].RArm, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -7.0f, 0.0f);
		glScalef(0.1f, 1.0f, 0.1f);
		glColor3f(0.94f, 0.58f, 0.38f);
		glutSolidCube(22.5);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(22.5);
		glPopMatrix();

		// 왼다리
		glPushMatrix();
		glTranslatef(-2.8f, -14.0f, 0.0f);
		glTranslatef(0.0f, 7.0f, 0.0f);
		glRotatef(robot[i].LLeg, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -7.0f, 0.0f);
		glScalef(0.2f, 1.0f, 0.2f);
		glColor3f(0.4f, 0.6f, 1.0f);
		glutSolidCube(15.3);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(15.3);
		glPopMatrix();

		// 오른다리
		glPushMatrix();
		glTranslatef(2.8f, -14.0f, 0.0f);
		glTranslatef(0.0f, 7.0f, 0.0f);
		glRotatef(robot[i].RLeg, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -7.0f, 0.0f);
		glScalef(0.2f, 1.0f, 0.2f);
		glColor3f(0.71f, 0.94f, 0.69f);
		glutSolidCube(15.3);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(15.3);
		glPopMatrix();
		glPopMatrix();
	}
}

void DrawBullet()
{
	if (isFire)
	{
		BULLET b;

		b.x = robot[0].MoveX;
		b.y = -70.0f;
		b.z = robot[0].MoveZ;
		b.time = 0;

		if (robot[0].RobotDir == 0) b.dir = 0;
		else if (robot[0].RobotDir == 1) b.dir = 1;
		else if (robot[0].RobotDir == 2) b.dir = 2;
		else if (robot[0].RobotDir == 3) b.dir = 3;

		bullet.push_back(b);

		isFire = false;
	}

	for (iter = bullet.begin(); iter != bullet.end(); ++iter)
	{
		glPushMatrix();
		glTranslatef(iter->x, 0.0f, 0.0f);
		glTranslatef(0.0f, iter->y, 0.0f);
		glTranslatef(0.0f, 0.0f, iter->z);
		glColor3f(1.0f, 0.0f, 1.0f);
		glutSolidSphere(1.0, 10, 10);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireSphere(1.0, 10, 10);
		glPopMatrix();
	}
}

void MakeCape()
{
	for (int i = 0; i < 2; ++i)
	{
		if (robot[i].RobotDir == 0 || robot[i].RobotDir == 1)
		{
			if (robot[i].RobotDir == 0) robot[i].capeXdir = 1, robot[i].capeZdir = 1;
			else robot[i].capeXdir = 1, robot[i].capeZdir = -1;

			robot[i].capepoints[0][0][0] = robot[i].MoveX - 8.4f * robot[i].capeXdir;
			robot[i].capepoints[0][0][2] = robot[i].MoveZ - 30 * robot[i].capeZdir;
			robot[i].capepoints[0][2][0] = robot[i].MoveX + 8.4f * robot[i].capeXdir;
			robot[i].capepoints[0][2][2] = robot[i].MoveZ - 30 * robot[i].capeZdir;

			robot[i].capepoints[3][0][0] = robot[i].MoveX - 8.4f * robot[i].capeXdir;
			robot[i].capepoints[3][0][2] = robot[i].MoveZ - 20 * robot[i].capeZdir;
			robot[i].capepoints[3][2][0] = robot[i].MoveX + 8.4f * robot[i].capeXdir;
			robot[i].capepoints[3][2][2] = robot[i].MoveZ - 20 * robot[i].capeZdir;

			robot[i].capepoints[6][0][0] = robot[i].MoveX - 8.4f * robot[i].capeXdir;
			robot[i].capepoints[6][0][2] = robot[i].MoveZ - 10 * robot[i].capeZdir;
			robot[i].capepoints[6][2][0] = robot[i].MoveX + 8.4f * robot[i].capeXdir;
			robot[i].capepoints[6][2][2] = robot[i].MoveZ - 10 * robot[i].capeZdir;

			robot[i].capepoints[9][0][0] = robot[i].MoveX - 8.4f *robot[i].capeXdir;
			robot[i].capepoints[9][0][2] = robot[i].MoveZ;
			robot[i].capepoints[9][2][0] = robot[i].MoveX + 8.4f * robot[i].capeXdir;
			robot[i].capepoints[9][2][2] = robot[i].MoveZ;

			for (int j = 0; j < 7; j += 3) {
				robot[i].capepoints[j + 1][0][0] = robot[i].MoveX - 8.4f * robot[i].capeXdir;
				robot[i].capepoints[j + 1][0][2] = robot[i].capepoints[j][0][2] + (robot[i].capepoints[j + 3][0][2] - robot[i].capepoints[j][0][2]) / 3;
				robot[i].capepoints[j + 1][2][0] = robot[i].MoveX + 8.4f * robot[i].capeXdir;
				robot[i].capepoints[j + 1][2][2] = robot[i].capepoints[j][2][2] + (robot[i].capepoints[j + 3][2][2] - robot[i].capepoints[j][2][2]) / 3;

				robot[i].capepoints[j + 2][0][0] = robot[i].MoveX - 8.4f * robot[i].capeXdir;
				robot[i].capepoints[j + 2][0][2] = robot[i].capepoints[j][0][2] + ((robot[i].capepoints[j + 3][0][2] - robot[i].capepoints[j][0][2])) / 3 * 2;
				robot[i].capepoints[j + 2][2][0] = robot[i].MoveX + 8.4f * robot[i].capeXdir;
				robot[i].capepoints[j + 2][2][2] = robot[i].capepoints[j][2][2] + ((robot[i].capepoints[j + 3][2][2] - robot[i].capepoints[j][2][2])) / 3 * 2;
			}

			for (int j = 0; j < 10; ++j) {
				robot[i].capepoints[j][1][0] = robot[i].MoveX;
				robot[i].capepoints[j][1][2] = robot[i].capepoints[j][0][2] + (robot[i].capepoints[j][2][2] - robot[i].capepoints[j][0][2]) / 2;
			}
		}
		else if (robot[i].RobotDir == 2 || robot[i].RobotDir == 3)
		{
			if (robot[i].RobotDir == 3) robot[i].capeXdir = 1, robot[i].capeZdir = -1;
			else robot[i].capeXdir = -1, robot[i].capeZdir = -1;

			robot[i].capepoints[0][0][0] = robot[i].MoveX - 30 * robot[i].capeXdir;
			robot[i].capepoints[0][0][2] = robot[i].MoveZ - 8.4 * robot[i].capeZdir;
			robot[i].capepoints[0][2][0] = robot[i].MoveX - 30 * robot[i].capeXdir;
			robot[i].capepoints[0][2][2] = robot[i].MoveZ + 8.4 * robot[i].capeZdir;

			robot[i].capepoints[3][0][0] = robot[i].MoveX - 20 * robot[i].capeXdir;
			robot[i].capepoints[3][0][2] = robot[i].MoveZ - 8.4 * robot[i].capeZdir;
			robot[i].capepoints[3][2][0] = robot[i].MoveX - 20 * robot[i].capeXdir;
			robot[i].capepoints[3][2][2] = robot[i].MoveZ + 8.4 * robot[i].capeZdir;

			robot[i].capepoints[6][0][0] = robot[i].MoveX - 10 * robot[i].capeXdir;
			robot[i].capepoints[6][0][2] = robot[i].MoveZ - 8.4 * robot[i].capeZdir;
			robot[i].capepoints[6][2][0] = robot[i].MoveX - 10 * robot[i].capeXdir;
			robot[i].capepoints[6][2][2] = robot[i].MoveZ + 8.4 * robot[i].capeZdir;

			robot[i].capepoints[9][0][0] = robot[i].MoveX;
			robot[i].capepoints[9][0][2] = robot[i].MoveZ - 8.4 * robot[i].capeZdir;
			robot[i].capepoints[9][2][0] = robot[i].MoveX;
			robot[i].capepoints[9][2][2] = robot[i].MoveZ + 8.4 * robot[i].capeZdir;

			for (int j = 0; j < 7; j += 3) {
				robot[i].capepoints[j + 1][0][0] = robot[i].capepoints[j][0][0] + (robot[i].capepoints[j + 3][0][0] - robot[i].capepoints[j][0][0]) / 3;
				robot[i].capepoints[j + 1][0][2] = robot[i].MoveZ - 8.4 * robot[i].capeZdir;
				robot[i].capepoints[j + 1][2][0] = robot[i].capepoints[j][2][0] + (robot[i].capepoints[j + 3][2][0] - robot[i].capepoints[j][2][0]) / 3;
				robot[i].capepoints[j + 1][2][2] = robot[i].MoveZ + 8.4 * robot[i].capeZdir;

				robot[i].capepoints[j + 2][0][0] = robot[i].capepoints[j][0][0] + ((robot[i].capepoints[j + 3][0][0] - robot[i].capepoints[j][0][0])) / 3 * 2;
				robot[i].capepoints[j + 2][0][2] = robot[i].MoveZ - 8.4 * robot[i].capeZdir;
				robot[i].capepoints[j + 2][2][0] = robot[i].capepoints[j][2][0] + ((robot[i].capepoints[j + 3][2][0] - robot[i].capepoints[j][2][0])) / 3 * 2;
				robot[i].capepoints[j + 2][2][2] = robot[i].MoveZ + 8.4 * robot[i].capeZdir;
			}

			for (int j = 0; j < 10; ++j) {
				robot[i].capepoints[j][1][0] = robot[i].capepoints[i][0][0] + (robot[i].capepoints[j][2][0] - robot[i].capepoints[j][0][0]) / 2;
				robot[i].capepoints[j][1][2] = robot[i].MoveZ;
			}
		}

		for (int k = 0; k < 10; ++k)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (i % 3 == 0)
				{
					if (j == 0)
						robot[i].capepoints[k][j][1] += 3 * robot[i].capeYdir1;
					else if (j == 1)
						robot[i].capepoints[k][j][1] -= 7 * robot[i].capeYdir2;
					else
						robot[i].capepoints[k][j][1] += 5 * robot[i].capeYdir3;
				}
				else if (i % 3 == 1)
				{
					if (j == 0)
						robot[i].capepoints[k][j][1] -= 3 * robot[i].capeYdir1;
					else if (j == 1)
						robot[i].capepoints[k][j][1] += 7 * robot[i].capeYdir2;
					else
						robot[i].capepoints[k][j][1] -= 5 * robot[i].capeYdir3;
				}
				else
				{
					if (j == 0)
						robot[i].capepoints[k][j][1] += 3 * robot[i].capeYdir1;
					else if (j == 1)
						robot[i].capepoints[k][j][1] += 7 * robot[i].capeYdir2;
					else
						robot[i].capepoints[k][j][1] -= 5 * robot[i].capeYdir3;
				}
			}
		}

		if (robot[i].capepoints[0][0][1] > -60.0f) robot[i].capeYdir1 *= -1;
		else if (robot[i].capepoints[0][0][1] < -80.0f) robot[i].capeYdir1 *= -1;

		if (robot[i].capepoints[0][1][1] > -60.0f) robot[i].capeYdir2 *= -1;
		else if (robot[i].capepoints[0][1][1] < -80.0f) robot[i].capeYdir2 *= -1;

		if (robot[i].capepoints[0][2][1] > -60.0f) robot[i].capeYdir3 *= -1;
		else if (robot[i].capepoints[0][2][1] < -80.0f) robot[i].capeYdir3 *= -1;
	}
}

void DrawCape()
{
	MakeCape();

	for (int i = 0; i < 2; ++i)
	{
		if(i == 0) glColor3f(1.0f, 0.0f, 0.0f);
		else glColor3f(0.0f, 0.0f, 1.0f);

		// 곡면 제어점 설정 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &robot[i].capepoints[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// 선을 이용하여 그리드 연결 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glDisable(GL_MAP2_VERTEX_3);

		// 곡면 제어점 설정 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &robot[i].capepoints[2][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// 선을 이용하여 그리드 연결 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glDisable(GL_MAP2_VERTEX_3);

		// 곡면 제어점 설정 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &robot[i].capepoints[4][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// 선을 이용하여 그리드 연결 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glDisable(GL_MAP2_VERTEX_3);

		// 곡면 제어점 설정 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &robot[i].capepoints[6][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// 선을 이용하여 그리드 연결 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glDisable(GL_MAP2_VERTEX_3);
	}
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


////////////////////////////////////////////////////////

void ROCollide()
{
	for (int i = 0; i < 2; ++i)
	{
		if (robot[i].RobotDir == 0)
		{
			for (int i = 0; i < 10; ++i)
			{
				if (robot[i].MoveZ >= obj[i].z - 6.0f && robot[i].MoveX >= obj[i].x - 6.0f && robot[i].MoveX <= obj[i].x + 6.0f)
				{
					robot[i].RobotDir = 2;
				}
			}
		}
		else if (robot[i].RobotDir == 1)
		{
			for (int i = 0; i < 10; ++i)
			{
				if (robot[i].MoveZ <= obj[i].z + 6.0f && robot[i].MoveX >= obj[i].x - 6.0f && robot[i].MoveX <= obj[i].x + 6.0f)
					robot[i].RobotDir = 3;
			}
		}
		else if (robot[i].RobotDir == 2)
		{
			for (int i = 0; i < 10; ++i)
			{
				if (robot[i].MoveZ >= obj[i].z - 6.0f && robot[i].MoveZ <= obj[i].z + 6.0f && robot[i].MoveX <= obj[i].x + 6.0f)
					robot[i].RobotDir = 0;
			}
		}
		else if (robot[i].RobotDir == 3)
		{
			for (int i = 0; i < 10; ++i)
			{
				if (robot[i].MoveZ >= obj[i].z - 6.0f && robot[i].MoveZ <= obj[i].z + 6.0f && robot[i].MoveX >= obj[i].x - 6.0f)
					robot[i].RobotDir = 2;
			}
		}
	}
}

void BOCollide()
{
	for (iter = bullet.begin(); iter != bullet.end();)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (iter->z >= obj[i].z - 6.0f && iter->z <= obj[i].z + 6.0f && iter->x >= obj[i].x - 6.0f && iter->x <= obj[i].x + 6.0f)
				BTcollision = true;
		}

		if (BTcollision) iter = bullet.erase(iter);
		else iter++;

		BTcollision = false;
	}

	for (iter = bullet.begin(); iter != bullet.end();)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (iter->z >= ctrlpoints[i * 3][2] - 6.0f && iter->z <= ctrlpoints[i * 3][2] + 6.0f && iter->x >= ctrlpoints[i * 3][0] - 6.0f && iter->x <= ctrlpoints[i * 3][0] + 6.0f)
				BPcollision = true;
		}

		if (BPcollision) iter = bullet.erase(iter);
		else iter++;

		BPcollision = false;
	}
}