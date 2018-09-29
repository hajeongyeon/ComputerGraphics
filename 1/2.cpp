// �ǽ� 2 : �ٵ��� ��� �׸���
// ������ �ʱ�ȭ �ϴ� �Լ��� �����.
// Reshape �Լ����� �������� ��ǥ�� ������ �����ϴ� �Լ��� ȣ���Ѵ�.
// ���ο� ���θ� Ư�� ������ ���� Ư�� ������ ���������� ��ȭ�Ǵ� ���·� ���� �����Ѵ�.
// Ư�� ������ ���� �����ϰ� �����Ѵ�. ������ ������ ������ ���� �ٸ��� ��Ÿ����.

#include <GL/freeglut.h>
#include <stdio.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 2"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	
	srand((unsigned int)time(NULL));

	float random1 = rand() % 256;
	float random2 = rand() % 256;
	float random3 = rand() % 128;

	float num = rand() % 6 + 5;

	float x = 400 / num;
	float y = 300 / num;

	for (int i = -num; i < num; ++i)
	{
		for (int j = num; j > -num; --j)
		{
			if(random2 > 50 && random2 < 211)
				glColor3f(random1 / 256.0f, (random2 + i * 5) / 256.0f, (random3 + j * 5) / 256.0f);
			else
				glColor3f(random1 / 256.0f, (random2 - j * 5) / 256.0f, (random3 - i * 5) / 256.0f);

			glRectf(i * x, j * y, (i * x) + x, (j * y) - y);
		}
	}

	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400, 400, -300, 300, -1, 1);
}