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

const int FrameX = 12;                                      /*游戏区域左上角横坐标*/
const int FrameY = 10;                                      /*游戏区域左上角纵坐标*/
const int FrameHigh = 25;                                   /*游戏区域高度*/
const int FrameWidth = 35;                                  /*游戏区域宽度*/
const int VERTEX = 100;										
const int WALL = 1;
const int ROUTE = 0;
const int MAXSPEED = 120;									/*蛇最大速度*/
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
	int x[2500];                                                              /*蛇身体横坐标*/
	int y[2500];                                                              /*蛇身体纵坐标*/
	int length;                                                               /*蛇的长度*/
	int speed;                                                                /*蛇当前速度*/
	int count;                                                                /*已吃食物数*/
	int score;                                                                /*当前分数*/
	int grade;                                                                /*当前等级*/

	Snake();																  /*初始化蛇*/
	~Snake() {};
	void MoveSnake(SnakeControl *const control, Graph *const graph, int *const x, int *const y);      /*蛇的移动*/
	void EatFood(Food *const food, SnakeControl *const control);              /*吃食物*/
	bool Dead() const;															/*判断是否死亡*/


};

class SnakeControl
{
public:

	void gotoxy(const int x, const int y) const;                                     /*获取光标位置*/
	void Print(Snake *snake, Graph * graph, int *x, int *y) const;                   /*打印蛇*/
	void GameArea(Graph *graph) const;                                               /*绘制游戏区域*/
	void GameInformation(Snake *snake, Food *food) const;                            /*游戏信息*/
	int StartGame();																 /*开始游戏*/
	int GameOver() const;                                                            /*结束游戏*/
	void GetPath(Snake *const snake, Graph *const graph, Food *const food, char dataStruct);
	void ReadPath();
	void Speed(Snake *const snake);
};

class Food
{
public:
	int FoodX;																		/*食物横坐标*/
	int FoodY;																		/*食物纵坐标*/
	vector<pair<int, int>> virtual_food;											/*用于让蛇找虚拟食物*/
	vector<pair<int, int>>::iterator it;
	pair<int, int> v_food;
	void MakeFood(Snake *const snake, SnakeControl *const control);					/*产生食物*/
	void CreateVirtualFood(Snake *const snake, string block);
};

class Graph
{
public:
	vector<int>path;																/*保存路径*/
	vector<int>::iterator it;
	int maze[VERTEX][VERTEX];														/*地图数组*/
	int flag[VERTEX][VERTEX];														/*访问地图某点标志位*/
	bool found = false;																/*是否找到食物标志*/
	void DFS(Snake *const snake, Food *const food, const int present_x, const int present_y, int next[][2]);
	void BFS(Snake *const snake, Food *const food, const int start_x, const int start_y, int next[][2]);
};
#endif // !_Snake_H