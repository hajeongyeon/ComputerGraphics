#include <GL/freeglut.h>
#include <windows.h>	 // ��Ʈ�� ���� ���� �ڷ� ����
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
GLubyte *pBytes; // �����͸� ����ų ������
BITMAPINFO *info; // ��Ʈ�� ��� ������ ��tn

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ� 35"); // ������ ���� (������ �̸�)
	SetupRC(); // ���� ���� �ʱ�ȭ �Լ�
	LoadTexture();
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������, ���� ���� Ŭ���� �ϱ�

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

	glutSwapBuffers(); // ��� ���
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// ���� ����
	gluPerspective(60.0f, w / h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -30.0);

	// ���� ����
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

	// ���̳ʸ� �б� ���� ������ ���� 
	if ( (fp = fopen (filename, "rb")) == NULL ) 
		return NULL;

	// ��Ʈ�� ���� ����� �д´�. 
	if ( fread (&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1 ) 
	{
		fclose(fp); 
		return NULL; 
	}

	// ������ BMP �������� Ȯ���Ѵ�.
	if ( header.bfType != 'MB' )
	{
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER ��ġ�� ����.
	infosize = header.bfOffBits - sizeof (BITMAPFILEHEADER);

	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ( (*info = (BITMAPINFO *)malloc(infosize)) == NULL )
	{ 
		fclose(fp); 
		exit (0); 
		return NULL;
	}

	// ��Ʈ�� ���� ����� �д´�. 
	if ( fread (*info, 1, infosize, fp) < (unsigned int)infosize )
	{ 
		free (*info);
		fclose(fp);
		return NULL;
	}

	// ��Ʈ���� ũ�� ����
	if ( (bitsize = (*info)->bmiHeader.biSizeImage) == 0 )
		bitsize = (  (*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount+7) / 8.0 *  abs((*info)->bmiHeader.biHeight);
	
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.
	if ( (bits = (unsigned char *)malloc(bitsize) ) == NULL )
	{ 
		free (*info);
		fclose(fp); 
		return NULL; 
	}

	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�.
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