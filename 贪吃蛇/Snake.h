#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#ifndef _Snake_H
#define _Snake_H
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <cstdbool>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdbool>
#include <iomanip>
using namespace std;

const int FrameX = 12;                                      /*��Ϸ�������ϽǺ�����*/
const int FrameY = 10;                                      /*��Ϸ�������Ͻ�������*/
const int FrameHigh = 25;                                   /*��Ϸ����߶�*/
const int FrameWidth = 35;                                  /*��Ϸ������*/
const int VERTEX = 100;										
const int WALL = 1;
const int ROUTE = 0;
const int MAXSPEED = 120;									/*������ٶ�*/
class Snake;
class SnakeControl;
class Food;
class Graph;

struct Node
{
	int x, y;
};
class Snake
{
public:
	int x[2500];                                                              /*�����������*/
	int y[2500];                                                              /*������������*/
	int length;                                                               /*�ߵĳ���*/
	int speed;                                                                /*�ߵ�ǰ�ٶ�*/
	int count;                                                                /*�ѳ�ʳ����*/
	int score;                                                                /*��ǰ����*/
	int grade;                                                                /*��ǰ�ȼ�*/

	Snake();																  /*��ʼ����*/
	~Snake() {};
	void MoveSnake(SnakeControl *const control, Graph *const graph, int *const x, int *const y);      /*�ߵ��ƶ�*/
	void EatFood(Food *const food, SnakeControl *const control);              /*��ʳ��*/
	bool Dead() const;															/*�ж��Ƿ�����*/


};

class SnakeControl
{
public:

	void gotoxy(const int x, const int y) const;                                     /*��ȡ���λ��*/
	void Print(Snake *snake, Graph * graph, int *x, int *y) const;                   /*��ӡ��*/
	void GameArea(Graph *graph) const;                                               /*������Ϸ����*/
	void GameInformation(Snake *snake, Food *food) const;                            /*��Ϸ��Ϣ*/
	int StartGame();																 /*��ʼ��Ϸ*/
	int GameOver() const;                                                            /*������Ϸ*/
	void GetPath(Snake *const snake, Graph *const graph, Food *const food, char dataStruct);
	void ReadPath();
	void Speed(Snake *const snake);
};

class Food
{
public:
	int FoodX;																		/*ʳ�������*/
	int FoodY;																		/*ʳ��������*/
	vector<pair<int, int>> virtual_food;											/*��������������ʳ��*/
	vector<pair<int, int>>::iterator it;
	pair<int, int> v_food;
	void MakeFood(Snake *const snake, SnakeControl *const control);					/*����ʳ��*/
	void CreateVirtualFood(Snake *const snake, string block);
};

class Graph
{
public:
	vector<int>path;																/*����·��*/
	vector<int>::iterator it;
	int maze[VERTEX][VERTEX];														/*��ͼ����*/
	int flag[VERTEX][VERTEX];														/*���ʵ�ͼĳ���־λ*/
	bool found = false;																/*�Ƿ��ҵ�ʳ���־*/
	void DFS(Snake *const snake, Food *const food, const int present_x, const int present_y, int next[][2]);
	void BFS(Snake *const snake, Food *const food, const int start_x, const int start_y, int next[][2]);
};
#endif // !_Snake_H