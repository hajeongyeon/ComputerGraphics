#include <iostream>
#include <random>
#include <time.h>
using namespace std;

void Init();
void Print();
void MakeMaze();

int map[25][25];

void main()
{
	while (1) {
		char num;
		cout << "a : 미로 만들기" << endl;
		cout << "q : 프로그램 종료" << endl;
		cout << "명령어 입력 : ";
		cin >> num;

		system("cls");

		if (num == 'a')
			MakeMaze();
		else if (num == 'q')
			break;
	}
}

void Init()
{
	for (int i = 0; i < 25; ++i)
		for (int j = 0; j < 25; ++j)
			map[i][j] = 2;
	map[0][0] = 1;
}

void Print()
{
	for (int i = 0; i < 25; ++i) 
	{
		for (int j = 0; j < 25; ++j) 
		{
			if (map[i][j] == 1)        // 길
				cout << "1  ";
			else if (map[i][j] == 2)   // 벽
				cout << "0  ";
		}
		cout << endl;
	}
}

void MakeMaze()
{
	Init();

	default_random_engine dre;
	uniform_int<> ui(2, 4);
	dre.seed(time(NULL));

	int x{ 0 }, y{ 0 };

	while (1) 
	{
		int num{ ui(dre) };

		if (map[y][x] == 1 && map[y + 1][x] == 1 && map[y + 2][x] == 1 && map[y + 3][x] == 1 && map[y + 4][x] == 1)
			num = 3;
		else if (map[y][x] == 1 && map[y][x + 1] == 1 && map[y][x + 2] == 1 && map[y][x + 3] == 1 && map[y][x + 4] == 1)
			num = 2;
		else if (map[y][x] == 1 && map[y][x - 1] == 1 && map[y][x - 2] == 1 && map[y][x - 3] == 1 && map[y][x - 4] == 1)
			num = 2;

		if (y == 24)
			num = 3;

		if (num == 1 && map[y - 1][x] == 2) 
		{   
			// Up
			if (y - 1 >= 0 && y - 1 < 25)
			{
				y -= 1;
				map[y][x] = 1;
			}
		}
		else if (num == 2 && map[y + 1][x] == 2) 
		{   
			// Down
			if (y + 1 >= 0 && y + 1 < 25)
			{
				y += 1;
				map[y][x] = 1;
			}
		}
		else if (num == 3 && map[y][x + 1] == 2) 
		{   
			// Right
			if (x + 1 >= 0 && x + 1 < 25)
			{
				x += 1;
				map[y][x] = 1;
			}
		}
		else if (num == 4 && map[y][x - 1] == 2) 
		{   
			// Left
			if (x - 1 >= 0 && x - 1 < 25) 
			{
				x -= 1;
				map[y][x] = 1;
			}
		}

		if (x == 24 && y == 24)
			break;
	}

	Print();
}