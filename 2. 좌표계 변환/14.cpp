//	14. 이동 회전 신축하기
//		- 화면에 마우스를 클릭하면 그 자리에 임의의 도형이 그려진다
//			glut 라이브러리에서 지원하는 3차원 객체를 그려본다.
//			다른 색, 다른 크기로 그린다.
//		- 그 도형이 임의의 축에 대하여 회전하며 점점 작아진다.
//			크기가 0이 되면 삭제된다.
//		- 다른 곳에 클릭하면 또 다른 도형이 그려지고 회전하며 점점 작아진다.
//		- 특정 키보드를 누르면 도형들이 반대 방향으로 회전한다.
//		- 종료 명령을 입력할 때까지 계속된다.
//			최대 20개까지 그리도록 한다.

#include <GL/freeglut.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

typedef struct
{
	int type;							// 도형 타입
	float r, g, b;						// 색
	float x, y;							// 위치
	int axis;							// 회전축
	int rot;							// 회전 각도
	float shapesize;					// 도형 크기

	double base, height;				// 원뿔
	int slices, stacks;					// 원뿔, 구
	double size;						// 육면체, 주전자
	double radius;						// 구
	double innerradius, outerradius;	// 토러스
	int sides, rings;					// 토러스
} Shape;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);
void TimerFunction(int);

vector<Shape> shape;
vector<Shape>::iterator iter;

int dir = 1;

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 14"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	glMatrixMode(GL_MODELVIEW);

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		glLoadIdentity();
	
		glTranslatef(iter->x, iter->y, 0.0f);

		printf("%d %d\n", iter->type, iter->axis);

		if (iter->axis == 0)
			glRotatef(iter->rot, 1.0f, 0.0f, 0.0f);
		else if (iter->axis == 1)
			glRotatef(iter->rot, 0.0f, 1.0f, 0.0f);
		else if (iter->axis == 2)
			glRotatef(iter->rot, 0.0f, 0.0f, 1.0f);

		glScalef(iter->shapesize, iter->shapesize, iter->shapesize);

		glColor3f(iter->r, iter->g, iter->b);

		if(iter->type == 1)
			glutWireCone(iter->base, iter->height, iter->slices, iter->stacks);
		else if (iter->type == 2)
			glutWireCube(iter->size);
		else if (iter->type == 3)
			glutWireSphere(iter->radius, iter->slices, iter->stacks);
		else if (iter->type == 4)
			glutWireTorus(iter->innerradius, iter->outerradius, iter->sides, iter->rings);
		else if (iter->type == 5)
			glutWireTeapot(iter->size);
	}

	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -400.0, 400.0);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		dir *= -1;
		break;

	case 'q': case 'Q':
		glutLeaveMainLoop();
		break;

	default:
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	srand((unsigned int)time(NULL));

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Shape s;

		s.type = rand() % 5 + 1;
		s.r = (rand() % 256) / 256.0f;
		s.g = (rand() % 256) / 256.0f;
		s.b = (rand() % 256) / 256.0f;
		s.x = (float)(x - 400) / 400;
		s.y = (float)(300 - y) / 300;
		s.axis = rand() % 3;
		s.rot = 0;
		s.shapesize = 1.0f;

		if (s.type == 1)
		{
			s.base = (rand() % 3 + 1) / 10.0;
			s.height = (rand() % 3 + 1) / 10.0;
			s.slices = rand() % 10 + 10;
			s.stacks = rand() % 10 + 10;
		}
		else if (s.type == 3)
		{
			s.radius = (rand() % 3 + 1) / 10.0;
			s.slices = rand() % 10 + 10;
			s.stacks = rand() % 10 + 10;
		}
		else if (s.type == 4)
		{
			s.innerradius = (rand() % 6 + 5) / 100.0;
			s.outerradius = (rand() % 2 + 1) / 10.0;
			s.sides = rand() % 10 + 10;
			s.rings = rand() % 10 + 10;
		}
		else
		{
			s.size = (rand() % 5 + 1) / 10.0;
		}

		shape.push_back(s);

		if (shape.size() == 20) shape.erase(shape.begin());
	}
}

void TimerFunction(int value)
{
	for (iter = shape.begin(); iter != shape.end();)
	{
		iter->rot += 5 * dir;
		iter->shapesize -= 0.005f;

		if (iter->shapesize <= 0.0f)
			iter = shape.erase(iter);
		else
			++iter;
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}