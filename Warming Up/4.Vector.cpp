#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct InputVector {
	int x = 0, y = 0, z = 0;
};

int func_compare(const void*, const void*);

int main(void)
{
	InputVector vec[2] = { 0, };
	char input[2][20];

	printf("+ : 두 벡터의 합\n");
	printf("- : 두 벡터의 차\n");
	printf("d : 두 벡터의 내적\n");
	printf("c : 두 벡터의 외적\n");
	printf("l : 두 벡터의 각각의 크기\n");
	printf("q : 프로그램 종료\n\n");

	printf("input vector1 : ");
	gets_s(input[0], sizeof(input[0]));
	printf("input vector2 : ");
	gets_s(input[1], sizeof(input[1]));
	printf("\n");

	vec[0].x = atoi(&input[0][0]);
	vec[0].y = atoi(&input[0][2]);
	vec[0].z = atoi(&input[0][4]);

	vec[1].x = atoi(&input[1][0]);
	vec[1].y = atoi(&input[1][2]);
	vec[1].z = atoi(&input[1][4]);

	while (1)
	{
		char Command;
		int idx;
		int space1 = 0, space2 = 0;

		printf("Command : ");
		scanf("%c", &Command);
		getchar();

		if (Command == '+')
			idx = 1;
		else if (Command == '-')
			idx = 2;
		else if (Command == 'd')
			idx = 3;
		else if (Command == 'c')
			idx = 4;
		else if (Command == 'l')
			idx = 5;
		else if (Command == 'q')
			idx = 6;
		else
			idx = 7;

		for (int i = 0; i < 20; ++i)
		{
			if (input[0][i] == ' ')
			{
				space1++;
			}
			if (input[1][i] == ' ')
			{
				space2++;
			}
		}

		if (space1 < 2 || space2 < 2)
			idx = 7;

		switch (idx)
		{
		case 1:	// 덧셈
		{
			int add[3] = { 0, };

			add[0] = vec[0].x + vec[1].x;
			add[1] = vec[0].y + vec[1].y;
			add[2] = vec[0].z + vec[1].z;

			printf("+ : (%d, %d, %d) + (%d, %d, %d) = (%d, %d, %d)\n", vec[0].x, vec[0].y, vec[0].z, vec[1].x, vec[1].y, vec[1].z, add[0], add[1], add[2]);

			break;
		}

		case 2:	// 뺄셈
		{
			int subtract[3] = { 0, };

			subtract[0] = vec[0].x - vec[1].x;
			subtract[1] = vec[0].y - vec[1].y;
			subtract[2] = vec[0].z - vec[1].z;

			printf("- : (%d, %d, %d) - (%d, %d, %d) = (%d, %d, %d)\n", vec[0].x, vec[0].y, vec[0].z, vec[1].x, vec[1].y, vec[1].z, subtract[0], subtract[1], subtract[2]);

			break;
		}

		case 3:	// 내적
		{
			int dot = 0;

			dot = (vec[0].x * vec[1].x) + (vec[0].y * vec[1].y) + (vec[0].z * vec[1].z);

			printf("d : (%d, %d, %d) · (%d, %d, %d) = %d\n", vec[0].x, vec[0].y, vec[0].z, vec[1].x, vec[1].y, vec[1].z, dot);

			break;
		}

		case 4:	// 외적
		{
			int cross[3] = { 0, };

			cross[0] = (vec[0].y * vec[1].z) - (vec[0].z * vec[1].y);
			cross[1] = (vec[0].z * vec[1].x) - (vec[0].x * vec[1].z);
			cross[2] = (vec[0].x * vec[1].y) - (vec[0].y * vec[1].x);

			printf("c : (%d, %d, %d) - (%d, %d, %d) = (%d, %d, %d)\n", vec[0].x, vec[0].y, vec[0].z, vec[1].x, vec[1].y, vec[1].z, cross[0], cross[1], cross[2]);

			break;
		}

		case 5:	// 크기
		{
			float size[2] = { 0, };

			size[0] = sqrt((vec[0].x * vec[0].x) + (vec[0].y * vec[0].y) + (vec[0].z * vec[0].z));
			size[1] = sqrt((vec[1].x * vec[1].x) + (vec[1].y * vec[1].y) + (vec[1].z * vec[1].z));

			printf("l : root(%d, %d, %d) = %f, root(%d, %d, %d) = %f\n"
				, vec[0].x, vec[0].y, vec[0].z, size[0], vec[1].x, vec[1].y, vec[1].z, size[1]);

			break;
		}

		case 6:
		{
			return 0;
		}

		default:
		{
			printf("잘못된 명령어입니다.\n");
			break;
		}
		}
		printf("\n");
	}
}