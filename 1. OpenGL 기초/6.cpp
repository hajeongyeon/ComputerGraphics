#include <GL/freeglut.h>
#include "456.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char, int, int);
void SpecialKeyboard(int, int, int);
void Mouse(int, int, int, int);
void TimerFunction(int);

void DrawRectangle(int, int, int, int);
void Collision(Shape*);

vector<Shape> shape;
vector<Shape>::iterator iter;

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 6"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
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

	srand((unsigned int)time(NULL));

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		R = (rand() % 256) / 256.0f;
		G = (rand() % 256) / 256.0f;
		B = (rand() % 256) / 256.0f;

		DrawRectangle(iter->x, iter->y, iter->width, iter->length);
	}

	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 0, 600, -1, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
		for (iter = shape.begin(); iter != shape.end(); ++iter)
			iter->allstop = true;
		break;

	case 'p':
		for (iter = shape.begin(); iter != shape.end(); ++iter)
			iter->allstop = false;
		break;

	case '1':
		if (!shape[0].isRot)
		{
			shape[0].SaveX = shape[0].x;
			shape[0].SaveY = shape[0].y;
			shape[0].stop = true;
			shape[0].isRot = true;
		}
		break;

	case '2':
		if (!shape[1].isRot)
		{
			shape[1].SaveX = shape[1].x;
			shape[1].SaveY = shape[1].y;
			shape[1].stop = true;
			shape[1].isRot = true;
		}
		break;

	case '3':
		if (!shape[2].isRot)
		{
			shape[2].SaveX = shape[2].x;
			shape[2].SaveY = shape[2].y;
			shape[2].stop = true;
			shape[2].isRot = true;
		}
		break;

	case '4':
		if (!shape[3].isRot)
		{
			shape[3].SaveX = shape[3].x;
			shape[3].SaveY = shape[3].y;
			shape[3].stop = true;
			shape[3].isRot = true;
		}
		break;

	case '5':
		if (!shape[4].isRot)
		{
			shape[4].SaveX = shape[4].x;
			shape[4].SaveY = shape[4].y;
			shape[4].stop = true;
			shape[4].isRot = true;
		}
		break;

	case '6':
		if (!shape[5].isRot)
		{
			shape[5].SaveX = shape[5].x;
			shape[5].SaveY = shape[5].y;
			shape[5].stop = true;
			shape[5].isRot = true;
		}
		break;

	case '7':
		if (!shape[6].isRot)
		{
			shape[6].SaveX = shape[6].x;
			shape[6].SaveY = shape[6].y;
			shape[6].stop = true;
			shape[6].isRot = true;
		}
		break;

	case '8':
		if (!shape[7].isRot)
		{
			shape[7].SaveX = shape[7].x;
			shape[7].SaveY = shape[7].y;
			shape[7].stop = true;
			shape[7].isRot = true;
		}
		break;

	case '9':
		if (!shape[8].isRot)
		{
			shape[8].SaveX = shape[8].x;
			shape[8].SaveY = shape[8].y;
			shape[8].stop = true;
			shape[8].isRot = true;
		}
		break;

	case '0':
		for (iter = shape.begin(); iter != shape.end(); ++iter)
		{
			if (!iter->isRot)
			{
				iter->SaveX = iter->x;
				iter->SaveY = iter->y;
				iter->stop = true;
				iter->isRot = true;
			}
		}
		break;

	default:
		break;
	}
}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		for (iter = shape.begin(); iter != shape.end(); ++iter)
		{
			if (iter->speed < 11)
				++(iter->speed);
		}
	}
	else if (key == GLUT_KEY_DOWN)
	{
		for (iter = shape.begin(); iter != shape.end(); ++iter)
		{
			if (iter->speed > 1)
				--(iter->speed);
		}
	}
}

void Mouse(int button, int state, int x, int y)
{
	srand((unsigned int)time(NULL));

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Shape s;

		int X = rand() % 2;
		int Y = rand() % 2;

		s.x = x;
		s.y = 600 - y;
		s.width = rand() % 40 + 30;
		s.length = rand() % 40 + 30;
		s.shapeSize = 1;
		if (X == 1) s.xdir = 1;
		else s.xdir = -1;
		if (Y == 1) s.ydir = 1;
		else s.ydir = -1;
		s.speed = rand() % 10 + 1;
		s.ForR = rand() % 2;

		shape.push_back(s);

		if (shape.size() == 10) shape.erase(shape.begin());
	}
}

void TimerFunction(int value)
{
	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		if (!iter->allstop && !iter->stop)
		{
			iter->width += iter->shapeSize;
			iter->length += iter->shapeSize;

			if (iter->width < 30 || iter->width > 70 || iter->length < 30 || iter->length > 70)
				iter->shapeSize *= -1;
		}
	}

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		if (iter->isRot && !iter->allstop)
		{
			if (iter->ForR == 0)
			{
				if ((iter->x - iter->width) <= 0 && iter->y >= iter->SaveY)
				{
					iter->x += MoveX;
					iter->xRot = 1;
				}

				if ((iter->x - iter->width) >= 0 && (iter->x + iter->width) <= 800)
					iter->x += MoveX * iter->xRot;
				else if ((iter->y - iter->length) >= 0 && (iter->y + iter->length) <= 600)
					iter->y -= MoveY * iter->yRot;
				else if ((iter->x + iter->width) >= 800)
				{
					iter->x -= MoveX;
					iter->xRot = -1;
				}
				else if ((iter->x - iter->width) <= 0 && (iter->y - iter->length) <= 0)
				{
					iter->y += MoveY;
					iter->yRot = -1;
					iter->rot = true;
				}

				if (iter->rot && iter->x >= iter->SaveX && iter->y >= iter->SaveY)
				{
					iter->xRot = 1;
					iter->yRot = 1;
					iter->rot = false;

					iter->isRot = false;
					iter->stop = false;
					continue;
				}
			}
			else
			{
				if ((iter->x + iter->width) >= 800 && iter->y >= iter->SaveY)
				{
					iter->x -= MoveX;
					iter->xRot = 1;
				}

				if ((iter->x - iter->width) >= 0 && (iter->x + iter->width) <= 800)
					iter->x -= MoveX * iter->xRot;
				else if ((iter->y - iter->length) >= 0 && (iter->y + iter->length) <= 600)
					iter->y -= MoveY * iter->yRot;
				else if ((iter->x - iter->width) <= 0)
				{
					iter->x += MoveX;
					iter->xRot = -1;
				}
				else if ((iter->x + iter->width) >= 800 && (iter->y - iter->length) <= 0)
				{
					iter->y += MoveY;
					iter->yRot = -1;
					iter->rot = true;
				}

				if (iter->rot && iter->x <= iter->SaveX && iter->y >= iter->SaveY)
				{
					iter->xRot = 1;
					iter->yRot = 1;
					iter->rot = false;

					iter->isRot = false;
					iter->stop = false;
					continue;
				}
			}
		}
	}

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		if (!iter->allstop && !iter->stop)
		{
			iter->x += (iter->speed * iter->xdir);
			iter->y += (iter->speed * iter->ydir);
		}
	}

	for (iter = shape.begin(); iter != shape.end(); ++iter)
	{
		if (!iter->allstop && !iter->stop)
		{
			Collision(&(*iter));
		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawRectangle(int x, int y, int width, int length)
{
	glColor3f(R, G, B);

	glRectf(x - width, y - length, x + width, y + length);
}

void Collision(Shape* shape)
{
	if ((shape->x - shape->width) <= 0)
		shape->xdir = 1;
	if ((shape->x + shape->width) >= 800)
		shape->xdir = -1;
	if ((shape->y - shape->length) <= 0)
		shape->ydir = 1;
	if ((shape->y + shape->length) >= 600)
		shape->ydir = -1;
}