#include <iostream>
using namespace std;

struct Rect {
	int x, y, z, w;
};

int map[30][30];
Rect rect;

void Init();
void Print();

void InputCoordValue(char);

void Rectangle();

void MoveLeft();
void MoveRight();
void MoveTop();
void MoveBottom();

void ExpandXY();
void ReductXY();
void ExpandX();
void ReductX();
void ExpandY();
void ReductY();

int main(void)
{
	char command;

	cout << "1 : 사각형" << endl;
	cout << "x/X : x축 양/음으로 한 칸 이동" << endl;
	cout << "y/Y : y축 양/음으로 한 칸 이동" << endl;
	cout << "s/S : 한 칸 확대/축소" << endl;
	cout << "i/j : x축 한 칸 확대/축소" << endl;
	cout << "k/l : y축 한 칸 확대/축소" << endl;
	cout << "r : 모든 것을 리셋하고 다시 좌표값을 입력받는다." << endl;
	cout << "q : 종료" << endl << endl;

	Init();
	InputCoordValue(command);
	Print();

	while (1)
	{
		cout << "input order : ";
		cin >> command;

		if (command == 'x')
		{
			if (rect.x > 1)
			{
				Init();
				MoveLeft();
			}
			else
				command = 9;
		}
		else if (command == 'X')
		{
			if (rect.z < 30)
			{
				Init();
				MoveRight();
			}
			else
				command = 9;
		}
		else if (command == 'y')
		{
			if (rect.y > 1)
			{
				Init();
				MoveTop();
			}
			else
				command = 9;
		}
		else if (command == 'Y')
		{
			if (rect.w < 30)
			{
				Init();
				MoveBottom();
			}
			else
				command = 9;
		}
		else if (command == 's')
		{
			if (rect.x > 1 && rect.z < 30 && rect.y > 1 && rect.w < 30)
			{
				Init();
				ExpandXY();
			}
			else
				command = 8;
		}
		else if (command == 'S')
		{
			if ((rect.x + 1 >= rect.z) || (rect.y + 1 >= rect.w))
				command = 7;
			else
			{
				Init();
				ReductXY();
			}
		}
		else if (command == 'i')
		{
			if (rect.z < 30)
			{
				Init();
				ExpandX();
			}
			else
				command = 8;
		}
		else if (command == 'j')
		{
			if (rect.x < rect.z + 1)
			{
				Init();
				ReductX();
			}
			else
				command = 7;
		}
		else if (command == 'k')
		{
			if (rect.w < 30)
			{
				Init();
				ExpandY();
			}
			else
				command = 8;
		}
		else if (command == 'l')
		{
			if (rect.y + 1 < rect.w)
			{
				Init();
				ReductY();
			}
			else
				command = 7;
		}
		else if (command == 'r')
		{
			Init();
			Print();
			InputCoordValue(command);
		}
		else if (command == 'q')
		{
			return 0;
		}
		else
		{
			cout << "잘못된 명령어입니다." << endl;
			continue;
		}
		
		if (command == 9)
			cout << "더 이상 움직일 수 없습니다." << endl;
		else if (command == 8)
			cout << "더 이상 확대할 수 없습니다." << endl;
		else if (command == 7)
			cout << "더 이상 축소할 수 없습니다." << endl;
		else 
			Print();
	}
}

void Init()
{
	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			map[i][j] = 1;
		}
	}
}

void Print()
{
	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			if (map[i][j] == 1)
				cout << ".    ";
			else if (map[i][j] == 2)
				cout << "0    ";
		}
		cout << endl;
	}
}

void InputCoordValue(char command)
{
	while (1)
	{
		cout << "input coord value : ";
		cin >> command;
		cin >> rect.x;
		cin >> rect.y;
		cin >> rect.z;
		cin >> rect.w;

		if ((rect.x >= rect.z) || (rect.y >= rect.w) || rect.x == 0 || rect.y == 0 || rect.z == 0 || rect.w == 0)
		{
			cout << "잘못된 좌표입니다." << endl << endl;
			continue;
		}

		if (command == '1')
		{
			Rectangle();

			break;
		}
		else
			cout << "잘못된 입력입니다." << endl << endl;
	}
}

void Rectangle()
{
	for (int i = rect.y - 1; i < rect.w; ++i)
	{
		for (int j = rect.x - 1; j < rect.z; ++j)
		{
			map[i][j] = 2;
		}
	}
}

void MoveLeft()
{
	for (int i = rect.y - 1; i < rect.w; ++i)
	{
		for (int j = rect.x - 2; j < rect.z - 1; ++j)
		{
			map[i][j] = 2;
		}
	}

	rect.x -= 1;
	rect.z -= 1;
}

void MoveRight()
{
	for (int i = rect.y - 1; i < rect.w; ++i)
	{
		for (int j = rect.x; j < rect.z + 1; ++j)
		{
			map[i][j] = 2;
		}
	}

	rect.x += 1;
	rect.z += 1;
}

void MoveTop()
{
	for (int i = rect.y - 2; i < rect.w - 1; ++i)
	{
		for (int j = rect.x - 1; j < rect.z; ++j)
		{
			map[i][j] = 2;
		}
	}

	rect.y -= 1;
	rect.w -= 1;
}

void MoveBottom()
{
	for (int i = rect.y; i < rect.w + 1; ++i)
	{
		for (int j = rect.x - 1; j < rect.z; ++j)
		{
			map[i][j] = 2;
		}
	}

	rect.y += 1;
	rect.w += 1;
}

void ExpandXY()
{
	for (int i = rect.y - 1; i < rect.w + 1; ++i)
	{
		for (int j = rect.x - 1; j < rect.z + 1; ++j)
		{
			map[i][j] = 2;
		}
	}

	rect.z += 1;
	rect.w += 1;
}

void ReductXY()
{
	for (int i = rect.y - 1; i < rect.w - 1; ++i)
	{
		for (int j = rect.x - 1; j < rect.z - 1; ++j)
		{
			map[i][j] = 2;
		}
	}

	rect.z -= 1;
	rect.w -= 1;
}

void ExpandX()
{
	for (int i = rect.y - 1; i < rect.w; ++i)
	{
		for (int j = rect.x - 1; j < rect.z + 1; ++j)
		{
			map[i][j] = 2;
		}
	}

	rect.z += 1;
}

void ReductX()
{
	for (int i = rect.y - 1; i < rect.w; ++i)
	{
		for (int j = rect.x - 1; j < rect.z - 1; ++j)
		{
			map[i][j] = 2;
		}
	}

	rect.z -= 1;
}

void ExpandY()
{
	for (int i = rect.y - 1; i < rect.w + 1; ++i)
	{
		for (int j = rect.x - 1; j < rect.z; ++j)
		{
			map[i][j] = 2;
		}
	}

	rect.w += 1;
}

void ReductY()
{
	for (int i = rect.y - 1; i < rect.w - 1; ++i)
	{
		for (int j = rect.x - 1; j < rect.z; ++j)
		{
			map[i][j] = 2;
		}
	}

	rect.w -= 1;
}