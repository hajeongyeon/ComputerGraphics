// 실습 2 : 바둑판 모양 그리기
// 윈도우 초기화 하는 함수를 만든다.
// Reshape 함수에서 윈도우의 좌표계 범위를 조절하는 함수를 호출한다.
// 가로와 세로를 특정 개수로 나눠 특정 색에서 점차적으로 변화되는 형태로 색을 배정한다.
// 특정 개수와 색은 랜덤하게 설정한다. 실행할 때마다 개수와 색은 다르게 나타난다.

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
	glutCreateWindow("실습 2"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	
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

	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400, 400, -300, 300, -1, 1);
}