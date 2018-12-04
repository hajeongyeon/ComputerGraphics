#include <GL/freeglut.h>
#include <windows.h>	 // 비트맵 파일 관련 자료 저장
#include <iostream>
using namespace std;

void SetupRC();
GLvoid drawScene(GLvoid);
void Reshape(int w, int h);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

GLubyte * LoadDIBitmap(const char*, BITMAPINFO**);
void LoadTexture();

int yRot;

GLuint texture[6];
GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변tn

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습 35"); // 윈도우 생성 (윈도우 이름)
	SetupRC(); // 상태 변수 초기화 함수
	LoadTexture();
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}

void SetupRC()
{
	yRot = 0;
}

GLvoid drawScene(GLvoid)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기

	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.0f, 3.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.0f, -3.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.0f, -3.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.0f, 3.0f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.0f, 3.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.0f, -3.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.0f, -3.0f, -6.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.0f, 3.0f, -6.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.0f, 3.0f, -6.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.0f, -3.0f, -6.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.0f, -3.0f, -6.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.0f, 3.0f, -6.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.0f, -3.0f, -6.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.0f, 3.0f, -6.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.0f, 3.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.0f, -3.0f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.0f, 3.0f, -6.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.0f, 3.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.0f, 3.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.0f, 3.0f, -6.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.0f, -3.0f, -6.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.0f, -3.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.0f, -3.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.0f, -3.0f, -6.0f);
	glEnd();

	glutSwapBuffers(); // 결과 출력
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 원근 투영
	gluPerspective(60.0f, w / h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -30.0);

	// 직각 투영
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
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

void TimerFunction(int value)
{
	++yRot;

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

GLubyte * LoadDIBitmap(const char* filename, BITMAPINFO** info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize; 
	BITMAPFILEHEADER header;

	// 바이너리 읽기 모드로 파일을 연다 
	if ( (fp = fopen (filename, "rb")) == NULL ) 
		return NULL;

	// 비트맵 파일 헤더를 읽는다. 
	if ( fread (&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1 ) 
	{
		fclose(fp); 
		return NULL; 
	}

	// 파일이 BMP 파일인지 확인한다.
	if ( header.bfType != 'MB' )
	{
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof (BITMAPFILEHEADER);

	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ( (*info = (BITMAPINFO *)malloc(infosize)) == NULL )
	{ 
		fclose(fp); 
		exit (0); 
		return NULL;
	}

	// 비트맵 인포 헤더를 읽는다. 
	if ( fread (*info, 1, infosize, fp) < (unsigned int)infosize )
	{ 
		free (*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵의 크기 설정
	if ( (bitsize = (*info)->bmiHeader.biSizeImage) == 0 )
		bitsize = (  (*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount+7) / 8.0 *  abs((*info)->bmiHeader.biHeight);
	
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ( (bits = (unsigned char *)malloc(bitsize) ) == NULL )
	{ 
		free (*info);
		fclose(fp); 
		return NULL; 
	}

	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if ( fread(bits, 1, bitsize, fp) < (unsigned int)bitsize )
	{ 
		free (*info);
		free (bits);
		fclose(fp); 
		return NULL;
	}

	fclose(fp); 
	return bits;
}

void LoadTexture()
{
	glGenTextures(3, texture);

	// 1
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	pBytes = LoadDIBitmap("35-1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 194, 194, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 2
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	pBytes = LoadDIBitmap("35-2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 225, 225, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 3
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	pBytes = LoadDIBitmap("35-3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 279, 279, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
}