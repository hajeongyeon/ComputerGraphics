#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Rect {
	int x, y, z, w;
	int width, length;
};

struct Circle {
	int x, y;
	int r;
};

void CollideRect(Rect r1, Rect r2);
void CollideCircle(Circle r1, Circle r2);

int main(void)
{
	Rect rect[2];
	Circle circle[2];
	int InputShape;

	printf("1 (rectangle X rectangle) / 2 (circle X circle) / 3 (rectangle X circle\n");
	printf("Command : a(left) / d(right) / s(down) / w(up)\n");

	printf("Input Shape Combination : ");
	scanf("%d", &InputShape);
	getchar();
	
	if (InputShape == 1)
	{
		rect[0].x = 100;
		rect[0].y = 100;
		rect[0].z = 300;
		rect[0].w = 300;

		rect[1].x = 400;
		rect[1].y = 400;
		rect[1].z = 500;
		rect[1].w = 500;

		rect[0].width = rect[0].y - rect[0].x;
		rect[0].length = rect[0].w - rect[0].z;
		rect[1].width = rect[1].y - rect[1].x;
		rect[1].length = rect[1].w - rect[1].z;

		printf("Shape 1 : (%d, %d) (%d, %d)\n", rect[0].x, rect[0].y, rect[0].z, rect[0].w);
		printf("Shape 2 : (%d, %d) (%d, %d)\n\n", rect[1].x, rect[1].y, rect[1].z, rect[1].w);
	}
	else if (InputShape == 2)
	{
		circle[0].x = 100;
		circle[0].y = 100;

		circle[1].x = 300;
		circle[1].y = 300;

		circle[0].r = 50;
		circle[1].r = 100;

		printf("Shape 1 : (%d, %d) 반지름 %d\n", circle[0].x, circle[0].y, circle[0].r);
		printf("Shape 2 : (%d, %d) 반지름 %d\n\n", circle[1].x, circle[1].y, circle[1].r);
	}

	while (1)
	{
		char Command;
		int idx;

		printf("Command : ");
		scanf("%c", &Command);
		getchar();

		if (Command == 'a')
			idx = 1;
		else if (Command == 'd')
			idx = 2;
		else if (Command == 's')
			idx = 3;
		else if (Command == 'w')
			idx = 4;
		else if (Command == 'q')
			idx = 5;
		else
			idx = 6;

		if (InputShape == 1)
		{
			switch (idx)
			{
			case 1:
			{
				rect[1].x -= 50;
				rect[1].z -= 50;

				printf("Shape 1 : (%d, %d) (%d, %d)\n", rect[0].x, rect[0].y, rect[0].z, rect[0].w);
				printf("Shape 2 : (%d, %d) (%d, %d)\n", rect[1].x, rect[1].y, rect[1].z, rect[1].w);

				break;
			}

			case 2:
			{
				rect[1].x += 50;
				rect[1].z += 50;

				printf("Shape 1 : (%d, %d) (%d, %d)\n", rect[0].x, rect[0].y, rect[0].z, rect[0].w);
				printf("Shape 2 : (%d, %d) (%d, %d)\n", rect[1].x, rect[1].y, rect[1].z, rect[1].w);

				break;
			}

			case 3:
			{
				rect[1].y -= 50;
				rect[1].w -= 50;

				printf("Shape 1 : (%d, %d) (%d, %d)\n", rect[0].x, rect[0].y, rect[0].z, rect[0].w);
				printf("Shape 2 : (%d, %d) (%d, %d)\n", rect[1].x, rect[1].y, rect[1].z, rect[1].w);

				break;
			}

			case 4:
			{
				rect[1].y += 50;
				rect[1].w += 50;

				printf("Shape 1 : (%d, %d) (%d, %d)\n", rect[0].x, rect[0].y, rect[0].z, rect[0].w);
				printf("Shape 2 : (%d, %d) (%d, %d)\n", rect[1].x, rect[1].y, rect[1].z, rect[1].w);

				break;
			}

			case 5:
			{
				return 0;
			}

			default:
			{
				printf("잘못된 명령어입니다.\n");
				break;
			}
			}

			CollideRect(rect[0], rect[1]);
		}
		else if (InputShape == 2)
		{
			switch (idx)
			{
			case 1:
			{
				circle[1].x -= 50;

				printf("Shape 1 : (%d, %d) 반지름 %d\n", circle[0].x, circle[0].y, circle[0].r);
				printf("Shape 2 : (%d, %d) 반지름 %d\n", circle[1].x, circle[1].y, circle[1].r);

				break;
			}

			case 2:
			{
				circle[1].x += 50;

				printf("Shape 1 : (%d, %d) 반지름 %d\n", circle[0].x, circle[0].y, circle[0].r);
				printf("Shape 2 : (%d, %d) 반지름 %d\n", circle[1].x, circle[1].y, circle[1].r);

				break;
			}

			case 3:
			{
				circle[1].y -= 50;

				printf("Shape 1 : (%d, %d) 반지름 %d\n", circle[0].x, circle[0].y, circle[0].r);
				printf("Shape 2 : (%d, %d) 반지름 %d\n", circle[1].x, circle[1].y, circle[1].r);

				break;
			}

			case 4:
			{
				circle[1].y += 50;

				printf("Shape 1 : (%d, %d) 반지름 %d\n", circle[0].x, circle[0].y, circle[0].r);
				printf("Shape 2 : (%d, %d) 반지름 %d\n", circle[1].x, circle[1].y, circle[1].r);

				break;
			}

			case 5:
			{
				return 0;
			}

			default:
			{
				printf("잘못된 명령어입니다.\n");
				break;
			}
			}

			CollideCircle(circle[0], circle[1]);
		}
		printf("\n");
	}
}

void CollideRect(Rect r1, Rect r2)
{
	if (r1.x < r2.z && r1.z > r2.x && r1.y < r2.w && r1.w > r2.y)
		printf("Rectangle 1 & Rectangle 2 Collide!!\n");
}

void CollideCircle(Circle r1, Circle r2)
{
	if (sqrt(((r2.x - r1.x) * (r2.x - r1.x)) + ((r2.y - r1.y) * (r2.y - r1.y))) < (r1.r + r2.r))
		printf("Circle 1 & Circle 2 Collide!!\n");
}