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
int num, tmp, dir1, dir2, dir3;					// tmp : ������ ��ǥ ���� ���� ����� ����
GLfloat ctrlpoints[10][3][3];
bool isQ, isWave, isAll;

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 29"); // ������ ���� (������ �̸�)
	SetupRC(); // ���� ���� �ʱ�ȭ �Լ�
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������, ���� ���� Ŭ���� �ϱ�

	glLoadIdentity();

	// ���� ��ȯ
	if (isQ)
	{
		glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	}
	else
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	// ��ǥ��
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

	// �� �� ����� �� ������ ��� �׸���
	if (isAll)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		// ��� ������ ���� 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// �׸��带 �̿��� ��� ����� 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// ���� �̿��Ͽ� �׸��� ���� 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glDisable(GL_MAP2_VERTEX_3);

		// ��� ������ ���� 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[2][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// �׸��带 �̿��� ��� ����� 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// ���� �̿��Ͽ� �׸��� ���� 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glDisable(GL_MAP2_VERTEX_3);

		// ��� ������ ���� 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[4][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// �׸��带 �̿��� ��� ����� 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// ���� �̿��Ͽ� �׸��� ���� 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glDisable(GL_MAP2_VERTEX_3);

		// ��� ������ ���� 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[6][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// �׸��带 �̿��� ��� ����� 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// ���� �̿��Ͽ� �׸��� ���� 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glDisable(GL_MAP2_VERTEX_3);
	}

	// ���콺�� ���� �κп� ���� �׸���.
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

	// �簢�� �׸���
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

	glutSwapBuffers(); // ��� ���
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 
	// ���� ����
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

	case 'v': case 'V':					// ���ͺ�� ���� ��ȯ
		if (isAll)						// �� �׷��� ����
		{
			if (isQ) isQ = false;
			else isQ = true;
		}
		break;

	case 'w': case 'W':					// ����
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