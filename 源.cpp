#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
/*注意！需要C99支持*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

#define FrameX 6                                                              /*游戏区域左上角横坐标*/
#define FrameY 4                                                              /*游戏区域左上角纵坐标*/
#define FrameHigh 25                                                          /*游戏区域高度*/
#define FrameWidth 35                                                         /*游戏区域宽度*/

struct Snake                                                                  /*定义蛇结构体*/
{
	int x[50];                                                                /*蛇身体横坐标*/
	int y[50];                                                                /*蛇身体纵坐标*/
	int length;                                                               /*蛇的长度*/
	int speed;                                                                /*蛇当前速度*/
	int count;                                                                /*已吃食物数*/
	int score;                                                                /*当前分数*/
	int grade;                                                                /*当前等级*/
}snake;

struct  Food
{
	int FoodX;
	int FoodY;
}food;

void gotoxy(int x, int y);                                                      /*获取光标位置*/
void MoveSnake(int *x, int *y);                                                /*蛇的移动*/
void Print(int *x, int *y);                                                    /*打印蛇*/
void GameArea();                                                               /*绘制游戏区域*/
void InitializeSnake();                                                        /*初始化蛇*/
void MakeFood();                                                               /*产生食物*/
void GameInformation();                                                        /*游戏信息*/
int StartGame();                                                               /*开始游戏*/
int GameOver();                                                                /*结束游戏*/
void EatFood();                                                                /*吃食物*/
bool Dead();                                                                   /*判断是否死亡*/

int main()
{
	StartGame();
	GameOver();
	system("pause");
	return 0;
}

/*开始游戏*/
int StartGame()
{
	char ch = 77;
	InitializeSnake();
	MakeFood();
	while (1)
	{
		if (kbhit())
			ch = getch();
		switch (ch)
		{
		case 72:
			MoveSnake(snake.x, snake.y);
			snake.y[snake.length - 1]--;
			break;
		case 80:
			MoveSnake(snake.x, snake.y);
			snake.y[snake.length - 1]++;
			break;
		case 77:
			MoveSnake(snake.x, snake.y);
			snake.x[snake.length - 1] += 2;
			break;
		case 75:
			MoveSnake(snake.x, snake.y);
			snake.x[snake.length - 1] -= 2;
			break;
		default:
			continue;
		}
		EatFood();
		Print(snake.x, snake.y);
		if (Dead())
			return 0;
		Sleep(snake.speed);
		GameInformation();
		GameArea();
	}
}

/*结束游戏*/
int GameOver()
{
	gotoxy(10, 20);
	printf("游戏结束！");
	return 0;
}

/*吃食物*/
void EatFood()
{
	if (snake.x[snake.length - 1] == food.FoodX && snake.y[snake.length - 1] == food.FoodY)
	{
		snake.length++;
		snake.count++;
		if (snake.count % 5 == 0)
		{
			snake.grade++;
			snake.score += 20;
			snake.speed -= 40;
			if (snake.speed < 10)
				snake.speed = 10;
		}
		else
			snake.score += 10;
		MakeFood();
		for (int i = snake.length - 1; i >= 1; i--)
		{
			snake.x[i] = snake.x[i - 1];
			snake.y[i] = snake.y[i - 1];
		}
	}
}

/*判断是否死亡*/
bool Dead()
{
	for (int i = 0; i < snake.length - 1; i++)
		if (snake.x[snake.length - 1] == snake.x[i] && snake.y[snake.length - 1] == snake.y[i])
			return true;
	for (int i = FrameX + 1; i < FrameX + FrameWidth - 1; i++)                                  /*上边框*/
		if (snake.x[snake.length - 1] == i && snake.y[snake.length - 1] == FrameY)
			return true;
	for (int i = FrameX + 1; i < FrameX + FrameWidth - 1; i++)                                  /*下边框*/
		if (snake.x[snake.length - 1] == i && snake.y[snake.length - 1] == FrameY + FrameHigh)
			return true;
	for (int i = FrameY + 1; i < FrameY + FrameHigh - 1; i++)                                   /*左边框*/
		if (snake.y[snake.length - 1] == i && snake.x[snake.length - 1] == FrameX)
			return true;
	for (int i = FrameY + 1; i < FrameY + FrameHigh - 1; i++)                                    /*右边框*/
		if (snake.y[snake.length - 1] == i && snake.x[snake.length - 1] == FrameX + FrameWidth - 1)
			return true;
	return false;
}

/*获取光标位置*/
void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };                             // 光标信息
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);        // 设置光标隐藏	
}

/*绘制游戏区域*/
void GameArea()
{
	for (int i = FrameX; i <= FrameWidth + FrameX; i++)
	{
		for (int j = FrameY; j <= FrameHigh + FrameY; j++)
		{
			if (i == FrameX && j == FrameY)
			{
				gotoxy(i, j);
				printf("┏");
			}
			else if (j < FrameHigh + FrameY && j != FrameY)
			{
				if (i == FrameX)
				{
					gotoxy(i, j);
					printf("┃");
				}
				if (i == FrameWidth + FrameX - 1)
				{
					gotoxy(i, j);
					printf("┃");
				}
			}
			else if (i == FrameX && j == FrameHigh + FrameY)
			{
				gotoxy(i, j);
				printf("┗");
			}
			else if (i > FrameX && i < FrameWidth + FrameX - 1)
			{
				if (j == FrameY)
				{
					gotoxy(i, j);
					printf("━");
				}
				if (j == FrameHigh + FrameY)
				{
					gotoxy(i, j);
					printf("━");
				}
			}
			else if (i == FrameWidth + FrameX - 1 && j == FrameY)
			{
				gotoxy(i, j);
				printf("┓");
			}
			else if (i == FrameWidth + FrameX - 1 && j == FrameHigh + FrameY)
			{
				gotoxy(i, j);
				printf("┛");
			}
			else
				continue;
		}
	}
}

/*初始化蛇*/
void InitializeSnake()
{
	snake.x[0] = 10;
	snake.y[0] = 10;
	snake.length = 3;
	snake.speed = 280;
	snake.count = 0;
	snake.grade = 1;
	snake.score = 0;
	for (int i = 1; i < snake.length; i++)
	{
		snake.x[i] = snake.x[i - 1] + 2;
		snake.y[i] = snake.y[i - 1];
	}
}

/*游戏信息*/
void GameInformation()
{
	gotoxy(FrameX + 15, FrameY - 2);
	printf("贪吃蛇");
	gotoxy(FrameX + FrameWidth + 3, FrameY + 1);
	printf("蛇的长度：%d", snake.length);
	gotoxy(FrameX + FrameWidth + 3, FrameY + 5);
	printf("食物的坐标(%2d,%2d)", food.FoodX, food.FoodY);
	gotoxy(FrameX + FrameWidth + 3, FrameY + 9);
	printf("蛇头的坐标(%2d,%2d)", snake.x[snake.length - 1], snake.y[snake.length - 1]);
	gotoxy(FrameX + FrameWidth + 3, FrameY + 13);
	printf("已吃食物数量：%d", snake.count);
	gotoxy(FrameX + FrameWidth + 3, FrameY + 17);
	printf("当前分数：%d", snake.score);
	gotoxy(FrameX + FrameWidth + 3, FrameY + 21);
	printf("当前等级：%d", snake.grade);
	gotoxy(FrameX + FrameWidth + 3, FrameY + 25);
	printf("当前速度：%d ms", snake.speed);
}

/*产生食物*/
void MakeFood()
{
	int flag;
	srand((unsigned)time(NULL));
	while (1)
	{
		flag = 0;
		food.FoodX = rand() % (FrameWidth - 3) + FrameX + 2;
		food.FoodY = rand() % (FrameHigh - 1) + FrameY + 1;
		for (int i = 0; i < snake.length; i++)
		{
			if ((food.FoodX == snake.x[i] && food.FoodY == snake.y[i]) || food.FoodX % 2 != 0)
			{/*由于字符占位的原因，所以食物横坐标必须为偶数*/
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			gotoxy(food.FoodX, food.FoodY);
			printf("⊙");
			break;
		}
	}
}

/*移动蛇*/
void MoveSnake(int *x, int *y)
{
	gotoxy(x[0], y[0]);
	printf("  ");
	for (int i = 1; i < snake.length; i++)
	{
		x[i - 1] = x[i];
		y[i - 1] = y[i];
	}
}

/*打印蛇*/
void Print(int *x, int *y)
{
	gotoxy(x[snake.length - 1], y[snake.length - 1]);
	printf("¤");
	for (int i = snake.length - 2; i >= 0; i--)
	{
		gotoxy(x[i], y[i]);
		printf("●");
	}
}