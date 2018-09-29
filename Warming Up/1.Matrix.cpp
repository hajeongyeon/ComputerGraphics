#include <iostream>
#include <time.h>
using namespace std;

int main(void)
{
	int matrix1[3][3];
	int matrix2[3][3];

	char idx;

	srand((unsigned int)time(NULL));

	cout << "M/m : 행렬의 곱셈" << endl;
	cout << "A/a : 행렬의 덧셈" << endl;
	cout << "D/d : 행렬의 뺄셈" << endl;
	cout << "R/r : 행렬식의 값" << endl;
	cout << "H/h : 3x3 행렬을 4x4 행렬로 변환" << endl;

	while (1)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				matrix1[i][j] = rand() % 2;
				matrix2[i][j] = rand() % 2;
			}
		}

		cout << "명령어를 입력해주세요 : ";
		cin >> idx;

		switch (idx)
		{
		case 'm': case 'M':
		{
			int mul[3][3];

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					int tmp[3];

					for (int k = 0; k < 3; ++k)
					{
						tmp[k] = matrix1[i][k] * matrix2[k][j];
					}

					mul[i][j] = tmp[0] + tmp[1] + tmp[2];
				}
			}

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					cout << matrix1[i][j] << " ";
				}

				if (i == 1)
					cout << "  *  ";
				else
					cout << "     ";

				for (int j = 0; j < 3; ++j)
				{
					cout << matrix2[i][j] << " ";
				}

				if (i == 1)
					cout << "  =  ";
				else
					cout << "     ";

				for (int j = 0; j < 3; ++j)
				{
					cout << mul[i][j] << " ";
				}

				cout << endl;
			}

			cout << endl;

			break;
		}

		case 'a': case 'A':
		{
			int add[3][3];

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					add[i][j] = matrix1[i][j] + matrix2[i][j];
				}
			}

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					cout << matrix1[i][j] << " ";
				}

				if(i == 1)
					cout << "  +  ";
				else
					cout << "     ";

				for (int j = 0; j < 3; ++j)
				{
					cout << matrix2[i][j] << " ";
				}

				if (i == 1)
					cout << "  =  ";
				else
					cout << "     ";

				for (int j = 0; j < 3; ++j)
				{
					cout << add[i][j] << " ";
				}

				cout << endl;
			}

			cout << endl;

			break;
		}

		case 'd': case 'D':
		{
			int subtract[3][3];

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					subtract[i][j] = matrix1[i][j] - matrix2[i][j];
				}
			}

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					cout << matrix1[i][j] << " ";
				}

				if (i == 1)
					cout << "  -  ";
				else
					cout << "     ";

				for (int j = 0; j < 3; ++j)
				{
					cout << matrix2[i][j] << " ";
				}

				if (i == 1)
					cout << "  =  ";
				else
					cout << "     ";

				for (int j = 0; j < 3; ++j)
				{
					cout << subtract[i][j] << " ";
				}

				cout << endl;
			}

			cout << endl;

			break;
		}

		case 'r': case 'R':
		{
			int det;

			det = matrix1[0][0] * ((matrix1[1][1] * matrix1[2][2]) - (matrix1[1][2] * matrix1[2][1]))
				- matrix1[0][1] * ((matrix1[1][0] * matrix1[2][2]) - (matrix1[1][2] * matrix1[2][0]))
				+ matrix1[0][2] * ((matrix1[1][0] * matrix1[2][1]) - (matrix1[1][1] * matrix1[2][0]));

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					cout << matrix1[i][j] << " ";
				}

				if (i == 1)
					cout << "  =  " << det << endl;
				else
					cout << endl;
			}

			cout << endl;

			break;
		}

		case 'h': case 'H':
		{
			int fxf[4][4];

			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					if (i == 3 && j == 3)
						fxf[i][j] = 1;
					else if (i == 3 || j == 3)
						fxf[i][j] = 0;
					else
						fxf[i][j] = matrix1[i][j];
				}
			}

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					if (i == 4)
						continue; 

					cout << matrix1[i][j] << " ";
				}

				if (i == 1)
					cout << "  =  ";
				else
					cout << "     ";

				for (int j = 0; j < 4; ++j)
				{
					cout << fxf[i][j] << " ";
				}

				cout << endl;
			}

			cout << "           ";
			for (int i = 0; i < 4; ++i)
				cout << fxf[3][i] << " ";

			cout << endl << endl;

			break;
		}

		default:
		{
			cout << "잘못된 명령어입니다." << endl << endl;

			break;
		}
		}
	}
}