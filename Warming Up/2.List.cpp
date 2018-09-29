#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct StoreList {
	char x = 0, y = 0, z = 0;
	float dst = 0;
};

int func_compare(const void*, const void*);

int main(void)
{
	StoreList list[10] = { 0, };
	char input[20];

	printf("+ x y z : 리스트의 맨 위에 입력\n");
	printf("- : 리스트의 맨 위에서 출력\n");
	printf("e x y z : 리스트의 맨 아래에 입력\n");
	printf("d : 리스트의 맨 아래에서 출력\n");
	printf("l : 리스트의 길이를 출력\n");
	printf("c : 리스트를 비움\n");
	printf("m : 원점에서 가장 먼 거리에 있는 점의 좌표값을 출력\n");
	printf("n : 원점에서 가장 가까운 거리에 있는 점의 좌표값을 출력\n");
	printf("q : 프로그램 종료\n\n");

	while (1)
	{
		int command = 0;
		int space = 0;

		printf("명령어 입력 : ");
		gets_s(input, sizeof(input));

		if (input[0] == '+')
			command = 1;
		else if (input[0] == '-')
			command = 2;
		else if (input[0] == 'e')
			command = 3;
		else if (input[0] == 'd')
			command = 4;
		else if (input[0] == 'c')
			command = 5;
		else if (input[0] == 'l')
			command = 6;
		else if (input[0] == 'm')
			command = 7;
		else if (input[0] == 'n')
			command = 8;
		else if (input[0] == 'q')
			command = 9;
		else
			command = 10;

		for (int i = 0; i < 20; ++i)
		{
			if (input[i] == ' ')
			{
				space++;
			}
		}

		if ((command == 1 || command == 3) && space < 3)
			command = 10;

		switch (command)
		{
		case 1:
		{
			int idx = 0;

			while (idx < 10)
			{
				if (list[idx].x == 0)
				{
					list[idx].x = input[2];
					list[idx].y = input[4];
					list[idx].z = input[6];

					list[idx].dst = sqrt((atoi(&input[2]) * atoi(&input[2])) + (atoi(&input[4]) * atoi(&input[4]))
						+ (atoi(&input[6]) * atoi(&input[6])));

					break;
				}
				else
					idx++;
			}
			break;
		}

		case 2:
		{
			int idx = 0;

			while (idx < 10)
			{
				if (list[idx].x == 0)
				{
					list[idx - 1].x = 0;
					list[idx - 1].y = 0;
					list[idx - 1].z = 0;
					list[idx - 1].dst = 0;

					break;
				}
				else
					idx++;
			}
			break;
		}

		case 3:
		{
			for (int i = 8; i >= 0; --i)
			{
				list[i + 1].x = list[i].x;
				list[i + 1].y = list[i].y;
				list[i + 1].z = list[i].z;
				list[i + 1].dst = list[i].dst;
			}

			list[0].x = input[2];
			list[0].y = input[4];
			list[0].z = input[6];

			list[0].dst = sqrt((atoi(&input[2]) * atoi(&input[2])) + (atoi(&input[4]) * atoi(&input[4]))
				+ (atoi(&input[6]) * atoi(&input[6])));

			break;
		}

		case 4:
		{
			int idx = 0;

			while (idx < 10)
			{
				if (list[idx].x != 0)
				{
					list[idx].x = 0;
					list[idx].y = 0;
					list[idx].z = 0;
					list[idx].dst = 0;

					break;
				}
				else
					idx++;
			}

			break;
		}

		case 5:
		{
			int idx = 0;

			while (idx < 10)
			{
				if (list[idx].x != 0)
				{
					list[idx].x = 0;
					list[idx].y = 0;
					list[idx].z = 0;
					list[idx].dst = 0;
				}

				++idx;
			}

			break;
		}

		case 6:
		{
			int idx = 0;
			int tmp = 0;

			while (idx < 10)
			{
				if (list[idx].x != 0)
					tmp++;

				idx++;
			}

			printf("length of list : %d\n", tmp);

			break;
		}

		case 7:
		{
			int tmp = 0;
			int idx = 0;
			float distance[10] = { 0, };

			while (idx < 10)
			{
				if (list[idx].x != 0)
				{
					distance[idx] = list[idx].dst;
				}
					
				idx++;
			}
			
			qsort((int*)distance, sizeof(distance)/sizeof(int), sizeof(int), func_compare);

			printf("%f\n", distance[9]);

			break;
		}

		case 8:
		{
			int tmp = 0;
			int idx = 0;
			float distance[10] = { 0, };

			while (idx < 10)
			{
				if (list[idx].x != 0)
				{
					distance[idx] = list[idx].dst;
				}

				idx++;
			}

			qsort((int*)distance, sizeof(distance) / sizeof(int), sizeof(int), func_compare);

			for (int i = 0; i < 10; ++i)
			{
				if (distance[i] != 0)
				{
					printf("%f\n", distance[i]);
					break;
				}
			}

			break;
		}

		case 9:
		{
			return 0;
		}

		default:
		{
			printf("잘못된 명령어입니다.\n");
			break;
		}
		}

		if (command > 0 && command < 6)
		{
			for (int i = 9; i >= 0; --i)
			{
				printf("%d : ", i);
				printf("%c ", list[i].x);
				printf("%c ", list[i].y);
				printf("%c\n", list[i].z);
			}
		}
		printf("\n");
	}
}

int func_compare(const void * first, const void * second)
{
	if (*(int*)first > *(int *)second)
		return 1;
	else if (*(int*)first < *(int *)second)
		return -1;
	else
		return 0;
}