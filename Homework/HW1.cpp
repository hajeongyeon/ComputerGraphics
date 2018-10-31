#include "HW1.h"

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("숙제 1"); // 윈도우 생성 (윈도우 이름)
	SetupRC(); // 상태 변수 초기화 함수
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutTimerFunc(1000, TimerFunction, 1);
	glutTimerFunc(100, TimerFunction2, 2);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();
}

// 초기화 함수
void SetupRC()
{
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	DrawGrid();

	for (iter = triangle.begin(); iter != triangle.end(); ++iter)
	{
		glPushMatrix();
			if (iter->isRot == true)
			{
				glTranslatef(iter->x, iter->y, 0.0f);
				glRotatef(iter->rot, 0.0f, 0.0f, 1.0f);
				glTranslatef(-iter->x, -iter->y, 0.0f);
			}
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_LINE_LOOP);
			glVertex2f(iter->p1[0], iter->p1[1]);
			glVertex2f(iter->p2[0], iter->p2[1]);
			glVertex2f(iter->p3[0], iter->p3[1]);
			glEnd();
		glPopMatrix();
	}

	for (iter2 = rect.begin(); iter2 != rect.end(); ++iter2)
	{
		glPushMatrix();
			if(!iter2->isRot) glRectf(375.0f, iter2->y - 25.0f, 425.0f, iter2->y + 25.0f);
			else
			{
				glColor3f(1.0f, 1.0f, 1.0f);
				glBegin(GL_POLYGON);
				glVertex2f(375.0f, iter2->y);
				glVertex2f(400.0f, iter2->y + 25.0f);
				glVertex2f(425.0f, iter2->y);
				glVertex2f(400.0f, iter2->y - 25.0f);
				glEnd();
			}
		glPopMatrix();
	}

	if (Lslicetri.size() != 0 || Rslicetri.size() != 0)
	{
		DrawSliceTriangle();
	}

	DrawStar();

	glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y)
{ 
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseX[0] = x;
		mouseY[0] = 600 - y;

		left_button = true;

		for (iter3 = Lslicetri.begin(); iter3 != Lslicetri.end(); ++iter3)
		{
			if ((x > iter3->p1[0] && x < iter3->p2[0]) && (y > iter3->p3[1] || y < iter3->p2[1]) && iter3->isStar == false)
			{
				iter3->isPush = true;

				iter3->p1[0] = x - 25.0f;
				iter3->p1[1] = 600 - y;
				iter3->p2[0] = x;
				iter3->p2[1] = 600 - y + 25.0f;
				iter3->p3[0] = x;
				iter3->p3[1] = 600 - y - 25.0f;
			}
		}

		for (iter4 = Rslicetri.begin(); iter4 != Rslicetri.end(); ++iter4)
		{
			if ((x > iter4->p2[0] && x < iter4->p1[0]) && (y > iter4->p3[1] || y < iter4->p2[1]))
			{
				iter4->isPush = true;

				iter4->p1[0] = x + 25.0f;
				iter4->p1[1] = 600 - y;
				iter4->p2[0] = x;
				iter4->p2[1] = 600 - y + 25.0f;
				iter4->p3[0] = x;
				iter4->p3[1] = 600 - y - 25.0f;
			}
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		mouseX[1] = x;
		mouseY[1] = 600 - y;

		left_button = false;

		for (iter3 = Lslicetri.begin(); iter3 != Lslicetri.end(); ++iter3)
		{
			if (iter3->isPush == true)
			{
				iter3->x = x;
				iter3->y = 600 - y;
				iter3->isPush = false;
			}
		}

		for (iter4 = Rslicetri.begin(); iter4 != Rslicetri.end(); ++iter4)
		{
			if (iter4->isPush == true)
			{
				iter4->x = x;
				iter4->y = 600 - y;
				iter4->isPush = false;
			}
		}
	}
}

void Motion(int x, int y)
{ 
	if (left_button == true)
	{
		for (iter3 = Lslicetri.begin(); iter3 != Lslicetri.end(); ++iter3)
		{
			if ((x > iter3->p1[0] && x < iter3->p2[0]) && (y > iter3->p3[1] || y < iter3->p2[1]) && iter3->isStar == false)
			{
				iter3->isPush = true;

				iter3->p1[0] = x - 25.0f;
				iter3->p1[1] = 600 - y;
				iter3->p2[0] = x;
				iter3->p2[1] = 600 - y + 25.0f;
				iter3->p3[0] = x;
				iter3->p3[1] = 600 - y - 25.0f;
			}
		}

		for (iter4 = Rslicetri.begin(); iter4 != Rslicetri.end(); ++iter4)
		{
			if ((x > iter4->p2[0] && x < iter4->p1[0]) && (y > iter4->p3[1] || y < iter4->p2[1]))
			{
				iter4->isPush = true;

				iter4->p1[0] = x + 25.0f;
				iter4->p1[1] = 600 - y;
				iter4->p2[0] = x;
				iter4->p2[1] = 600 - y + 25.0f;
				iter4->p3[0] = x;
				iter4->p3[1] = 600 - y - 25.0f;
			}
		}
	}
}

void TimerFunction(int value)
{
	srand((unsigned int)time(NULL));

	// 삼각형 생성
	Triangle t;

	t.x = 0.0f;
	t.rot = 0.0f;
	t.isRot = true;
	t.p1[0] = t.x;
	t.p1[1] = t.y + 21.65f;
	t.p2[0] = t.x - 25.0f;
	t.p2[1] = t.y - 21.65f;
	t.p3[0] = t.x + 25.0f;
	t.p3[1] = t.y - 21.65f;

	triangle.push_back(t);

	for (iter = triangle.begin(); iter != triangle.end();)
	{
		if (iter->x >= 800.0f)
			iter = triangle.erase(triangle.begin());
		else
			++iter;
	}

	// 사각형 생성
	if (rect.size() == 0)
	{
		Rect r;

		r.y = 0.0f;
		if (rand() % 2 == 0) r.isRot = false;
		else r.isRot = true;

		rect.push_back(r);
	}

	/*for (iter2 = rect.begin(); iter2 != rect.end();)
	{
		if (iter2->y > 600.0f || isSlice)
		{
			if (isSlice)
			{
				LeftSliceTriangle lst;
				RightSliceTriangle rst;

				lst.y = iter2->y;
				lst.FallTime = 0.0f;
				lst.degree = 0.0f;

				rst.y = iter2->y;
				rst.FallTime = 0.0f;
				rst.degree = 0.0f;

				Lslicetri.push_back(lst);
				Rslicetri.push_back(rst);

				isSlice = false;
			}

			iter2 = rect.erase(iter2);
			isSlice = false;
		}
		else ++iter2;
	}*/

	glutPostRedisplay();
	glutTimerFunc(2500, TimerFunction, 1);
}

void TimerFunction2(int value)
{
	srand((unsigned int)time(NULL));

	for (iter = triangle.begin(); iter != triangle.end(); ++iter)
	{
		if (iter->isRot)
		{
			iter->x += 5.0f;
			iter->p1[0] = iter->x;
			iter->p1[1] = iter->y + 21.65f;
			iter->p2[0] = iter->x - 25.0f;
			iter->p2[1] = iter->y - 21.65f;
			iter->p3[0] = iter->x + 25.0f;
			iter->p3[1] = iter->y - 21.65f;
			iter->rot += 5.0f;
		}
	}

	for (iter2 = rect.begin(); iter2 != rect.end();)
	{
		iter2->y += 5.0f;

		// 드래그 체크
		if ((mouseX[0] > 380 && mouseX[0] < 420) && (mouseY[0] > iter2->y + 50 || mouseY[0] < iter2->y + 100))
		{
			if ((mouseX[1] > 380 && mouseX[1] < 420) && (mouseY[1] > iter2->y - 100 || mouseY[1] < iter2->y - 50))
			{
				isSlice = true;

				mouseX[0] = 0, mouseY[0] = 0;
				mouseX[1] = 0, mouseY[1] = 0;
			}
		}
		if ((mouseX[0] > 200 && mouseX[0] < 350) && (mouseY[0] > iter2->y - 30 || mouseY[0] < iter2->y + 30))
		{
			if ((mouseX[1] > 450 && mouseX[1] < 600) && (mouseY[1] > iter2->y - 30 || mouseY[1] < iter2->y + 30))
			{
				isSlice = true;

				mouseX[0] = 0, mouseY[0] = 0;
				mouseX[1] = 0, mouseY[1] = 0;
			}
		}

		if (iter2->y > 600.0f || isSlice)
		{
			if (isSlice)
			{
				LeftSliceTriangle lst;
				RightSliceTriangle rst;

				lst.y = iter2->y;
				lst.FallTime = 0.0f;
				lst.degree = 0.0f;

				rst.y = iter2->y;
				rst.FallTime = 0.0f;
				rst.degree = 0.0f;

				Lslicetri.push_back(lst);
				Rslicetri.push_back(rst);

				isSlice = false;
			}

			iter2 = rect.erase(iter2);
			isSlice = false;
		}
		else ++iter2;
	}

	for (iter3 = Lslicetri.begin(); iter3 != Lslicetri.end();)
	{
		if (iter3->isPush == false && iter3->isStar == false)
		{
			iter3->FallTime += 0.3f;
			iter3->degree++;
			iter3->p1[0] = iter3->x - 35.0f - iter3->FallTime * 5.0f;
			iter3->p1[1] = iter3->y + FreeFall(iter3->FallTime, iter3->degree);
			iter3->p2[0] = iter3->x - 10.0f - iter3->FallTime * 5.0f;
			iter3->p2[1] = iter3->y + FreeFall(iter3->FallTime, iter3->degree) + 25.0f;
			iter3->p3[0] = iter3->x - 10.0f - iter3->FallTime * 5.0f;
			iter3->p3[1] = iter3->y + FreeFall(iter3->FallTime, iter3->degree) - 25.0f;
		}

		if(iter3->p2[1] < 0.0f)
			iter3 = Lslicetri.erase(iter3);
		else 
			++iter3;
	}

	for (iter4 = Rslicetri.begin(); iter4 != Rslicetri.end();)
	{
		if (iter4->isPush == false)
		{
			iter4->FallTime += 0.3f;
			iter4->degree++;
			iter4->p1[0] = iter4->x + 35.0f + iter4->FallTime * 5.0f;
			iter4->p1[1] = iter4->y + FreeFall(iter4->FallTime, iter4->degree);
			iter4->p2[0] = iter4->x + 10.0f + iter4->FallTime * 5.0f;
			iter4->p2[1] = iter4->y + FreeFall(iter4->FallTime, iter4->degree) + 25.0f;
			iter4->p3[0] = iter4->x + 10.0f + iter4->FallTime * 5.0f;
			iter4->p3[1] = iter4->y + FreeFall(iter4->FallTime, iter4->degree) - 25.0f;
		}
		
		if (iter4->p2[1] < 0.0f)
			iter4 = Rslicetri.erase(iter4);
		else ++iter4;
	}

	for (iter5 = star.begin(); iter5 != star.end(); ++iter5)
	{
		if (iter5->size >= 2.0f)
			iter5->dir = -1;
		else if (iter5->size < 1.0f)
			iter5->dir = 1;

		iter5->size += 0.1f * iter5->dir;

		iter5->r = (rand() % 254) / 254.0f;
		iter5->g = (rand() % 254) / 254.0f;
		iter5->b = (rand() % 254) / 254.0f;

		if (iter5->colX != iter5->posX)
		{
			if (iter5->colX > iter5->posX)
			{
				iter5->colX -= (iter5->colX - iter5->posX) / 20;
				iter5->colY -= (iter5->colY - iter5->posY) / 20;

				if (iter5->colX < iter5->posX && iter5->colY < iter5->posY)
				{
					iter5->colX = iter5->posX;
					iter5->colY = iter5->posY;
				}
			}
			else
			{
				iter5->colX += (iter5->colX + iter5->posX) / 20;
				iter5->colY -= (iter5->colY - iter5->posY) / 20;

				if (iter5->colX > iter5->posX && iter5->colY < iter5->posY)
				{
					iter5->colX = iter5->posX;
					iter5->colY = iter5->posY;
				}
			}

			iter5->p1[0] = iter5->colX;
			iter5->p1[1] = iter5->colY + 25;
			iter5->p2[0] = iter5->colX - 25;
			iter5->p2[1] = iter5->colY - 15;
			iter5->p3[0] = iter5->colX + 25;
			iter5->p3[1] = iter5->colY - 15;
			iter5->p4[0] = iter5->colX;
			iter5->p4[1] = iter5->colY - 25;
			iter5->p5[0] = iter5->colX - 25;
			iter5->p5[1] = iter5->colY + 15;
			iter5->p6[0] = iter5->colX + 25;
			iter5->p6[1] = iter5->colY + 15;
		}
	}

	Collision();

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction2, 2);
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

void DrawGrid()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(800.0f, 500.0f);
	glVertex2f(0.0f, 500.0f);
	glEnd();

	// 세로
	for (int i = 1; i < 15; ++i)
	{
		if (i < 8)
		{
			glBegin(GL_LINES);
			glVertex2f(50.0f * i, 150.0f);
			glVertex2f(50.0f * i, 0.0f);
			glEnd();
		}
		else
		{
			glBegin(GL_LINES);
			glVertex2f(50.0f * i + 50, 150.0f);
			glVertex2f(50.0f * i + 50, 0.0f);
			glEnd();
		}
	}

	// 가로
	for (int i = 1; i < 4; ++i)
	{
		glBegin(GL_LINES);
		glVertex2f(0.0f, 50.0f * i);
		glVertex2f(350.0f, 50.0f * i);
		glVertex2f(450.0f, 50.0f * i);
		glVertex2f(800.0f, 50.0f * i);
		glEnd();
	}
	
	// 대각선
	for (int i = 0; i < 19; ++i)
	{
		if (i < 10)
		{
			glBegin(GL_LINES);
			if (i < 4) glVertex2f(0.0f, 50.0f * (-i + 3));
			else glVertex2f(50.0f * (i - 3), 0.0f);
			if (i > 7) glVertex2f(350.0f, 50.0f * (-i + 10));
			else glVertex2f(50.0f * i, 150.0f);
			glEnd();
		}
		else
		{
			glBegin(GL_LINES);
			if (i < 13) glVertex2f(450.0f, 50.0f * (-i + 12));
			else glVertex2f(50.0f * (i - 3), 0.0f);
			if (i > 16) glVertex2f(800.0f, 50.0f * (-i + 19));
			else glVertex2f(50.0f * i, 150.0f);
			glEnd();
		}
	}
}

void DrawSliceTriangle()
{
	for (iter3 = Lslicetri.begin(); iter3 != Lslicetri.end(); ++iter3)
	{
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_TRIANGLES);
			glVertex2f(iter3->p1[0], iter3->p1[1]);
			glVertex2f(iter3->p2[0], iter3->p2[1]);
			glVertex2f(iter3->p3[0], iter3->p3[1]);
			glEnd();
		glPopMatrix();
	}

	for (iter4 = Rslicetri.begin(); iter4 != Rslicetri.end(); ++iter4)
	{
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_TRIANGLES);
			glVertex2f(iter4->p1[0], iter4->p1[1]);
			glVertex2f(iter4->p2[0], iter4->p2[1]);
			glVertex2f(iter4->p3[0], iter4->p3[1]);
			glEnd();
		glPopMatrix();
	}
}

float FreeFall(float falltime, float degree)
{
	float y = tan(degree * RADIAN) * falltime - 9.8f / (2 * 2 * 2 * cos(degree * RADIAN) * cos(degree * RADIAN)) * falltime * falltime;

	return y;
}

void Collision()
{
	for (iter = triangle.begin(); iter != triangle.end();)
	{
		for (iter3 = Lslicetri.begin(); iter3 != Lslicetri.end();)
		{
			if ((iter->p2[0] < iter3->x || iter3->x > iter->p3[0]) && (525.0f < iter3->y && iter3->y < 575.0f))
			{
				iter3->isStar = true;
				iter->isRot = false;

				colX = iter->x;
				colY = iter->y;

				iter3 = Lslicetri.erase(iter3);
				iter->p1[0] = 0.0f, iter->p1[1] = 0.0f;
				iter->p2[0] = 0.0f, iter->p2[1] = 0.0f;
				iter->p3[0] = 0.0f, iter->p3[1] = 0.0f;

				MakeStar();
			}
			else
			{
				++iter3;
			}
		}

		for (iter4 = Rslicetri.begin(); iter4 != Rslicetri.end();)
		{
			if ((iter->p2[0] < iter4->x || iter4->x > iter->p3[0]) && (525.0f < iter4->y && iter4->y < 575.0f))
			{
				iter4->isStar = true;
				iter->isRot = false;

				colX = iter->x;
				colY = iter->y;

				iter4 = Rslicetri.erase(iter4);
				iter->p1[0] = 0.0f, iter->p1[1] = 0.0f;
				iter->p2[0] = 0.0f, iter->p2[1] = 0.0f;
				iter->p3[0] = 0.0f, iter->p3[1] = 0.0f;

				MakeStar();
			}
			else
			{
				++iter4;
			}
		}

		if (iter->isRot == false)
		{
			iter = triangle.erase(iter);
		}
		else
			++iter;
	}
}

void MakeStar()
{
	srand((unsigned int)time(NULL));

	Star s;

	s.posX = (rand() % 60) * 10 + 100;
	s.posY = (rand() % 15) * 10 + 250;
	s.colX = colX;
	s.colY = colY;

	s.p1[0] = colX;
	s.p1[1] = colY + 25;
	s.p2[0] = colX - 25;
	s.p2[1] = colY - 15;
	s.p3[0] = colX + 25;
	s.p3[1] = colY - 15;
	s.p4[0] = colX;
	s.p4[1] = colY - 25;
	s.p5[0] = colX - 25;
	s.p5[1] = colY + 15;
	s.p6[0] = colX + 25;
	s.p6[1] = colY + 15;

	s.r = (rand() % 254) / 254.0f;
	s.g = (rand() % 254) / 254.0f;
	s.b = (rand() % 254) / 254.0f;
	s.Rot = 0.0f;
	s.size = 1.0f;
	s.dir = 1;

	star.push_back(s);
}

void DrawStar()
{
	int test = 0;

	for (iter5 = star.begin(); iter5 != star.end(); ++iter5)
	{
		glPushMatrix();
			glColor3f(iter5->r, iter5->g, iter5->b);
			glTranslatef(iter5->p1[0], iter5->p1[1] - 25, 0.0f);
			glRotatef(iter5->Rot++, 0.0f, 0.0f, 1.0f);
			glScalef(iter5->size, iter5->size, 0.0f);
			glTranslatef(-iter5->p1[0], -iter5->p1[1] + 25, 0.0f);

			glBegin(GL_TRIANGLES);
			glVertex2f(iter5->p1[0], iter5->p1[1]);
			glVertex2f(iter5->p2[0], iter5->p2[1]);
			glVertex2f(iter5->p3[0], iter5->p3[1]);
			glEnd();
			glBegin(GL_TRIANGLES);
			glVertex2f(iter5->p4[0], iter5->p4[1]);
			glVertex2f(iter5->p5[0], iter5->p5[1]);
			glVertex2f(iter5->p6[0], iter5->p6[1]);
			glEnd(); 
		glPopMatrix();
	}
}