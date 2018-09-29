// 실습 1 : 화면에 윈도우 띄우고 사각형 그리기
// - 위치 (100, 100)에 크기 800*600의 윈도우를 띄운다.
// - 중앙에 삼각형, 좌우상하에 사각형을 그린다. 각각 다른 색으로 설정한다.
// - 화면 중앙에 2개의 직선으로 좌표계를 그린다.

#include <GL/freeglut.h>
#include <stdio.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 1"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	srand((unsigned int)time(NULL));
								  
	// 선
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

	// 삼각형
	float random1 = (rand() % 256) / 256.0f;
	float random2 = (rand() % 256) / 256.0f;
	float random3 = (rand() % 256) / 256.0f;

	glColor3f(random1, random2, random3);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0.1);
	glVertex2f(0.1, -0.1);
	glVertex2f(-0.1, -0.1);
	glEnd();

	// 사각형
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

	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}