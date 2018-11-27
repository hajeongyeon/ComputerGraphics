// �ǽ� 1 : ȭ�鿡 ������ ���� �簢�� �׸���
// - ��ġ (100, 100)�� ũ�� 800*600�� �����츦 ����.
// - �߾ӿ� �ﰢ��, �¿���Ͽ� �簢���� �׸���. ���� �ٸ� ������ �����Ѵ�.
// - ȭ�� �߾ӿ� 2���� �������� ��ǥ�踦 �׸���.

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
	glutCreateWindow("�ǽ� 1"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	srand((unsigned int)time(NULL));
								  
	// ��
	GLint p1[2] = { -300, 0 };
	GLint p2[2] = { 300, 0 };
	GLint p3[2] = { 0, -400 };
	GLint p4[2] = { 0, 400 };

	glBegin(GL_LINES);
	glVertex2iv(p1);
	glVertex2iv(p2);
	glVertex2iv(p3); 
	glVertex2iv(p4);
	glEnd();

	// �ﰢ��
	float random1 = (rand() % 256) / 256.0f;
	float random2 = (rand() % 256) / 256.0f;
	float random3 = (rand() % 256) / 256.0f;

	glColor3f(random1, random2, random3);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0.1);
	glVertex2f(0.1, -0.1);
	glVertex2f(-0.1, -0.1);
	glEnd();

	// �簢��
	random1 = (rand() % 256) / 256.0f;
	random2 = (rand() % 256) / 256.0f;
	random3 = (rand() % 256) / 256.0f;	
	glColor3f(random1, random2, random3);
	glRectf(-1, 1, -0.8, 0.8);

	random1 = (rand() % 256) / 256.0f;
	random2 = (rand() % 256) / 256.0f;
	random3 = (rand() % 256) / 256.0f;	
	glColor3f(random1, random2, random3);
	glRectf(1, 1, 0.8, 0.8);

	random1 = (rand() % 256) / 256.0f;
	random2 = (rand() % 256) / 256.0f;
	random3 = (rand() % 256) / 256.0f;
	glColor3f(random1, random2, random3);
	glRectf(-1, -1, -0.8, -0.8);

	random1 = (rand() % 256) / 256.0f;
	random2 = (rand() % 256) / 256.0f;
	random3 = (rand() % 256) / 256.0f;
	glColor3f(random1, random2, random3);
	glRectf(1, -1, 0.8, -0.8);

	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}