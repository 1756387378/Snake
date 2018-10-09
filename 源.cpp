#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
/*ע�⣡��ҪC99֧��*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

#define FrameX 6                                                              /*��Ϸ�������ϽǺ�����*/
#define FrameY 4                                                              /*��Ϸ�������Ͻ�������*/
#define FrameHigh 25                                                          /*��Ϸ����߶�*/
#define FrameWidth 35                                                         /*��Ϸ������*/

struct Snake                                                                  /*�����߽ṹ��*/
{
	int x[50];                                                                /*�����������*/
	int y[50];                                                                /*������������*/
	int length;                                                               /*�ߵĳ���*/
	int speed;                                                                /*�ߵ�ǰ�ٶ�*/
	int count;                                                                /*�ѳ�ʳ����*/
	int score;                                                                /*��ǰ����*/
	int grade;                                                                /*��ǰ�ȼ�*/
}snake;

struct  Food
{
	int FoodX;
	int FoodY;
}food;

void gotoxy(int x, int y);                                                      /*��ȡ���λ��*/
void MoveSnake(int *x, int *y);                                                /*�ߵ��ƶ�*/
void Print(int *x, int *y);                                                    /*��ӡ��*/
void GameArea();                                                               /*������Ϸ����*/
void InitializeSnake();                                                        /*��ʼ����*/
void MakeFood();                                                               /*����ʳ��*/
void GameInformation();                                                        /*��Ϸ��Ϣ*/
int StartGame();                                                               /*��ʼ��Ϸ*/
int GameOver();                                                                /*������Ϸ*/
void EatFood();                                                                /*��ʳ��*/
bool Dead();                                                                   /*�ж��Ƿ�����*/

int main()
{
	StartGame();
	GameOver();
	system("pause");
	return 0;
}

/*��ʼ��Ϸ*/
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

/*������Ϸ*/
int GameOver()
{
	gotoxy(10, 20);
	printf("��Ϸ������");
	return 0;
}

/*��ʳ��*/
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

/*�ж��Ƿ�����*/
bool Dead()
{
	for (int i = 0; i < snake.length - 1; i++)
		if (snake.x[snake.length - 1] == snake.x[i] && snake.y[snake.length - 1] == snake.y[i])
			return true;
	for (int i = FrameX + 1; i < FrameX + FrameWidth - 1; i++)                                  /*�ϱ߿�*/
		if (snake.x[snake.length - 1] == i && snake.y[snake.length - 1] == FrameY)
			return true;
	for (int i = FrameX + 1; i < FrameX + FrameWidth - 1; i++)                                  /*�±߿�*/
		if (snake.x[snake.length - 1] == i && snake.y[snake.length - 1] == FrameY + FrameHigh)
			return true;
	for (int i = FrameY + 1; i < FrameY + FrameHigh - 1; i++)                                   /*��߿�*/
		if (snake.y[snake.length - 1] == i && snake.x[snake.length - 1] == FrameX)
			return true;
	for (int i = FrameY + 1; i < FrameY + FrameHigh - 1; i++)                                    /*�ұ߿�*/
		if (snake.y[snake.length - 1] == i && snake.x[snake.length - 1] == FrameX + FrameWidth - 1)
			return true;
	return false;
}

/*��ȡ���λ��*/
void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };                             // �����Ϣ
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);        // ���ù������	
}

/*������Ϸ����*/
void GameArea()
{
	for (int i = FrameX; i <= FrameWidth + FrameX; i++)
	{
		for (int j = FrameY; j <= FrameHigh + FrameY; j++)
		{
			if (i == FrameX && j == FrameY)
			{
				gotoxy(i, j);
				printf("��");
			}
			else if (j < FrameHigh + FrameY && j != FrameY)
			{
				if (i == FrameX)
				{
					gotoxy(i, j);
					printf("��");
				}
				if (i == FrameWidth + FrameX - 1)
				{
					gotoxy(i, j);
					printf("��");
				}
			}
			else if (i == FrameX && j == FrameHigh + FrameY)
			{
				gotoxy(i, j);
				printf("��");
			}
			else if (i > FrameX && i < FrameWidth + FrameX - 1)
			{
				if (j == FrameY)
				{
					gotoxy(i, j);
					printf("��");
				}
				if (j == FrameHigh + FrameY)
				{
					gotoxy(i, j);
					printf("��");
				}
			}
			else if (i == FrameWidth + FrameX - 1 && j == FrameY)
			{
				gotoxy(i, j);
				printf("��");
			}
			else if (i == FrameWidth + FrameX - 1 && j == FrameHigh + FrameY)
			{
				gotoxy(i, j);
				printf("��");
			}
			else
				continue;
		}
	}
}

/*��ʼ����*/
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

/*��Ϸ��Ϣ*/
void GameInformation()
{
	gotoxy(FrameX + 15, FrameY - 2);
	printf("̰����");
	gotoxy(FrameX + FrameWidth + 3, FrameY + 1);
	printf("�ߵĳ��ȣ�%d", snake.length);
	gotoxy(FrameX + FrameWidth + 3, FrameY + 5);
	printf("ʳ�������(%2d,%2d)", food.FoodX, food.FoodY);
	gotoxy(FrameX + FrameWidth + 3, FrameY + 9);
	printf("��ͷ������(%2d,%2d)", snake.x[snake.length - 1], snake.y[snake.length - 1]);
	gotoxy(FrameX + FrameWidth + 3, FrameY + 13);
	printf("�ѳ�ʳ��������%d", snake.count);
	gotoxy(FrameX + FrameWidth + 3, FrameY + 17);
	printf("��ǰ������%d", snake.score);
	gotoxy(FrameX + FrameWidth + 3, FrameY + 21);
	printf("��ǰ�ȼ���%d", snake.grade);
	gotoxy(FrameX + FrameWidth + 3, FrameY + 25);
	printf("��ǰ�ٶȣ�%d ms", snake.speed);
}

/*����ʳ��*/
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
			{/*�����ַ�ռλ��ԭ������ʳ����������Ϊż��*/
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			gotoxy(food.FoodX, food.FoodY);
			printf("��");
			break;
		}
	}
}

/*�ƶ���*/
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

/*��ӡ��*/
void Print(int *x, int *y)
{
	gotoxy(x[snake.length - 1], y[snake.length - 1]);
	printf("��");
	for (int i = snake.length - 2; i >= 0; i--)
	{
		gotoxy(x[i], y[i]);
		printf("��");
	}
}