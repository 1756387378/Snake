#include "Snake.h"

//��ʼ����Ϸ
Snake::Snake()
{
	this->x[0] = 16;
	this->y[0] = 15;
	this->length = 3;
	this->speed = MAXSPEED;
	this->count = 0;
	this->grade = 1;
	this->score = 0;
	for (int i = 1; i < this->length; i++)
	{
		this->x[i] = this->x[i - 1] + 2;
		this->y[i] = this->y[i - 1];
	}
}

/*��ʼ��Ϸ*/
int SnakeControl::StartGame()
{
	Snake *const snake = new Snake();
	Graph *const graph = new Graph();
	Food *const food = new Food();
	int x, y;
	int temp_x, temp_y;
	char dataStruct = 'D';			//D������DFS��B������BFS
	string block = "ul";			//��ul���������ϡ���ur���������ϡ���ll���������¡���lr����������
	int iblock = 0;
	food->MakeFood(snake, this);
	GameArea(graph);
	while (1)
	{
		GetPath(snake, graph, food, 'B');		//�ȳ��Թ����������
		if (!graph->path.empty())
		{
			for (graph->it = graph->path.begin(); graph->it != graph->path.end(); graph->it++)
			{
				x = *(graph->it);
				(graph->it)++;
				y = *(graph->it);
				snake->MoveSnake(this, graph, snake->x, snake->y);
				snake->x[snake->length - 1] = x;
				snake->y[snake->length - 1] = y;
				Print(snake, graph, snake->x, snake->y);
				Speed(snake);
				GameInformation(snake, food);
			}
			snake->EatFood(food, this);
		}
		else//��������ʳ��λ�ã��������Ƚ����滻
		{
			food->CreateVirtualFood(snake, block);
			//cout << dataStruct << endl;
			/*for (food->it = food->virtual_food.begin(); food->it != food->virtual_food.end(); food->it++)
			{
				food->FoodX = (*food->it).first;
				food->FoodY = (*food->it).second;
				cout << "x:" << food->FoodX << "	y:" << food->FoodY << endl;
			}*/
			temp_x = food->FoodX;						//����ԭʳ������
			temp_y = food->FoodY;
			for (food->it = food->virtual_food.begin(); food->it != food->virtual_food.end(); food->it++)
			{
				food->FoodX = (*food->it).first;
				food->FoodY = (*food->it).second;
				GetPath(snake, graph, food, dataStruct);
				if (!graph->path.empty())
				{
					for (graph->it = graph->path.begin(); graph->it != graph->path.end(); graph->it++)
					{
						x = *(graph->it);
						(graph->it)++;
						y = *(graph->it);
						snake->MoveSnake(this, graph, snake->x, snake->y);
						snake->x[snake->length - 1] = x;
						snake->y[snake->length - 1] = y;
						/*cout << endl;
						for (int i = 0; i < snake->length; i++)
							cout << "snake_x:" << snake->x[i] << "		snake_y:" << snake->y[i] << endl;*/
						Print(snake, graph, snake->x, snake->y);
						Speed(snake);
						GameInformation(snake, food);
					}
					break;
				}
			}
			if (food->it == food->virtual_food.end())		//��·���ߣ���ת��ͷ
			{
				int temp;
				for (int i = 0; i < snake->length / 2; i++)
				{
					temp = snake->x[snake->length - i - 1];
					snake->x[snake->length - i - 1] = snake->x[i];
					snake->x[i] = temp;

					temp = snake->y[snake->length - i - 1];
					snake->y[snake->length - i - 1] = snake->y[i];
					snake->y[i] = temp;
				}
			}
			food->FoodX = temp_x;
			food->FoodY = temp_y;
		}
		if (dataStruct == 'D')
			dataStruct = 'B';
		else
			dataStruct = 'D';
		iblock = rand() % 4;
		switch (iblock)
		{
		case 0:
			block = "ul";
			break;
		case 1:
			block = "ur";
			break;
		case 2:
			block = "ll";
			break;
		case 3:
			block = "lr";
			break;
		default:
			break;
		}
		if (snake->Dead())
		{
			/*for (int i = 0; i < snake->length; i++)
				cout << "snake_x:" << snake->x[i] << "		snake_y:" << snake->y[i] << endl;*/
			return 0;
		}
	}
	delete snake;
	delete graph;
	delete food;
}

/*��ʳ��,������Ϸ��Ϣ*/
void Snake::EatFood(Food *const food, SnakeControl *const control)
{
	if (this->x[this->length - 1] == food->FoodX && this->y[this->length - 1] == food->FoodY)
	{
		this->length++;
		this->count++;
		if (this->count % 5 == 0)
		{
			this->grade++;
			this->score += 20;
		}
		else
			this->score += 10;
		food->MakeFood(this, control);
		for (int i = this->length - 1; i >= 1; i--)
		{
			this->x[i] = this->x[i - 1];
			this->y[i] = this->y[i - 1];
		}
	}
}

/*�ж��Ƿ�����*/
bool Snake::Dead() const
{
	for (int i = 0; i < this->length - 1; i++)
		if (this->x[this->length - 1] == this->x[i] && this->y[this->length - 1] == this->y[i])
			return true;
	for (int i = FrameX + 1; i < FrameX + FrameWidth - 1; i++)                                  /*�ϱ߿�*/
		if (this->x[this->length - 1] == i && this->y[this->length - 1] == FrameY)
			return true;
	for (int i = FrameX + 1; i < FrameX + FrameWidth - 1; i++)                                  /*�±߿�*/
		if (this->x[this->length - 1] == i && this->y[this->length - 1] == FrameY + FrameHigh)
			return true;
	for (int i = FrameY + 1; i <= FrameY + FrameHigh - 1; i++)                                  /*��߿�*/
		if (this->y[this->length - 1] == i && this->x[this->length - 1] == FrameX)
			return true;
	for (int i = FrameY + 1; i <= FrameY + FrameHigh - 1; i++)                                  /*�ұ߿�*/
		if (this->y[this->length - 1] == i && this->x[this->length - 1] == FrameX + FrameWidth - 1)
			return true;
	return false;
}

/*�ƶ���*/
void Snake::MoveSnake(SnakeControl *const control, Graph *const graph, int *const x, int *const y)
{
	control->gotoxy(x[0], y[0]);
	cout << "  ";
	for (int i = 1; i < this->length; i++)
	{
		x[i - 1] = x[i];
		y[i - 1] = y[i];
	}
}

//�ٶȿ���
void SnakeControl::Speed(Snake *const snake)
{
	char ch = 0;
	if (kbhit())
		ch = getch();
	switch (ch)
	{
	case 72:
		if (snake->speed > 20)
			snake->speed -= 20;
		else
			snake->speed -= 5;
		if (snake->speed < 0)
			snake->speed = 0;
		break;
	case 80:
		if (snake->speed < 20)
			snake->speed += 5;
		else
			snake->speed += 20;
		if (snake->speed > MAXSPEED)
			snake->speed = MAXSPEED;
		break;
	}
	Sleep(snake->speed);
}

/*������Ϸ*/
int SnakeControl::GameOver() const
{
	gotoxy(15, 20);
	cout << "��Ϸ������";
	return 0;
}

/*��ȡ���λ��*/
void SnakeControl::gotoxy(const int x, const int y) const
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };                             // �����Ϣ
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);        // ���ù������	
}

/*������Ϸ����*/
void SnakeControl::GameArea(Graph *graph) const
{
	for (int i = FrameX; i <= FrameWidth + FrameX; i++)
	{
		for (int j = FrameY; j <= FrameHigh + FrameY; j++)
		{
			if (i == FrameX && j == FrameY)
			{
				gotoxy(i, j);
				graph->maze[i][j] = WALL;
				cout << "��";
			}
			else if (j < FrameHigh + FrameY && j != FrameY)
			{
				if (i == FrameX)
				{
					gotoxy(i, j);
					graph->maze[i][j] = WALL;
					cout << "��";
				}
				if (i == FrameWidth + FrameX - 1)
				{
					gotoxy(i, j);
					graph->maze[i][j] = WALL;
					cout << "��";
				}
			}
			else if (i == FrameX && j == FrameHigh + FrameY)
			{
				gotoxy(i, j);
				graph->maze[i][j] = WALL;
				cout << "��";
			}
			else if (i > FrameX && i < FrameWidth + FrameX - 1)
			{
				if (j == FrameY)
				{
					gotoxy(i, j);
					graph->maze[i][j] = WALL;
					cout << "��";
				}
				if (j == FrameHigh + FrameY)
				{
					gotoxy(i, j);
					graph->maze[i][j] = WALL;
					cout << "��";
				}
			}
			else if (i == FrameWidth + FrameX - 1 && j == FrameY)
			{
				gotoxy(i, j);
				graph->maze[i][j] = WALL;
				cout << "��";
			}
			else if (i == FrameWidth + FrameX - 1 && j == FrameHigh + FrameY)
			{
				gotoxy(i, j);
				graph->maze[i][j] = WALL;
				cout << "��";
			}
			else
				continue;
		}
	}
}

/*��Ϸ��Ϣ*/
void SnakeControl::GameInformation(Snake *snake, Food *food) const
{
	gotoxy(FrameX + FrameWidth / 2, FrameY - 2);
	cout << "̰����";
	gotoxy(FrameX + FrameWidth + 3, FrameY);
	cout << "�ߵĳ��ȣ�" << snake->length;
	gotoxy(FrameX + FrameWidth + 3, FrameY + FrameHigh / 6);
	cout << "ʳ�������(" << food->FoodX << "," << food->FoodY << ")";
	gotoxy(FrameX + FrameWidth + 3, FrameY + FrameHigh * 2 / 6);
	cout << "��ͷ������(" << snake->x[snake->length - 1] << "," << snake->y[snake->length - 1] << ")";
	gotoxy(FrameX + FrameWidth + 3, FrameY + FrameHigh * 3 / 6);
	cout << "�ѳ�ʳ��������" << snake->count;
	gotoxy(FrameX + FrameWidth + 3, FrameY + FrameHigh * 4 / 6);
	cout << "��ǰ������" << snake->score;
	gotoxy(FrameX + FrameWidth + 3, FrameY + FrameHigh * 5 / 6);
	cout << "��ǰ�ȼ���" << snake->grade;
	gotoxy(FrameX + FrameWidth + 3, FrameY + FrameHigh);
	cout << "��ǰ�ٶȣ�" << setw(3) << MAXSPEED - snake->speed << setw(3) << "ms" << "�������������ٶȣ�" << endl;
}

/*����ʳ��*/
void Food::MakeFood(Snake *const snake,SnakeControl *const control)
{
	int flag;
	while (1)
	{
		flag = 0;
		this->FoodX = rand() % (FrameWidth - 3) + FrameX + 2;
		this->FoodY = rand() % (FrameHigh - 1) + FrameY + 1;
		for (int i = 0; i < snake->length; i++)
		{
			if ((this->FoodX == snake->x[i] && this->FoodY == snake->y[i]) || this->FoodX % 2 != 0)
			{/*�����ַ�ռλ��ԭ������ʳ����������Ϊż��*/
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			control->gotoxy(this->FoodX, this->FoodY);
			cout << "��";
			break;
		}
	}
}

/*��ӡ��*/
void SnakeControl::Print(Snake *snake, Graph * graph, int *x, int *y) const
{
	gotoxy(x[snake->length - 1], y[snake->length - 1]);
	cout << "��";
	for (int i = snake->length - 2; i >= 0; i--)
	{
		gotoxy(x[i], y[i]);
		cout << "��";
	}
}

//����·��
void SnakeControl::GetPath(Snake *const snake, Graph *const graph, Food *const food, char dataStruct)
{
	int r;
	int path_x, path_y;
	path_x = snake->x[snake->length - 1];				//����ͷλ����Ϊ���
	path_y = snake->y[snake->length - 1];
	int  next[4][2] = {
		{ 0, 1 }, //��
		{ 2, 0 }, //��
		{ 0, -1}, //��
		{ -2, 0}  //��
	};
	for (int i = 0; i < 4; i++) {
		r = rand() % 4;	
		int temp = next[0][0];
		next[0][0] = next[r][0];
		next[r][0] = temp;
		temp = next[0][1];
		next[0][1] = next[r][1];
		next[r][1] = temp;
	}
	graph->path.clear();
	for (int i = FrameX; i <= FrameWidth + FrameX; i++)  //���õ�ͼ
	{
		for (int j = FrameY; j <= FrameHigh + FrameY; j++)
		{
			if (graph->maze[i][j] == WALL)
				continue;
			else
				graph->maze[i][j] = ROUTE;
		}
	}
	if (dataStruct == 'B')
		graph->BFS(snake, food, path_x, path_y, next);
	else
		graph->DFS(snake, food, path_x, path_y, next);
	
	for (int i = 0; i < VERTEX; i++)					//���÷��ʵ�ͼĳ���־λ
	{
		for (int j = 0; j < VERTEX; j++)
		{
			graph->flag[i][j] = ROUTE;
		}
	}

	graph->found = false;
}

//�����������
void Graph::DFS(Snake *const snake, Food *const food, const int present_x, const int present_y, int next[][2])
{
	int tx, ty;
	//int  next[4][2] = {
	//	{ 0, 1 }, //��
	//	{ 2, 0 }, //��
	//	{ 0, -1}, //��
	//	{ -2, 0}  //��
	//};
	if (food->FoodX == present_x && food->FoodY == present_y)		//�ҵ�ʳ��λ��
	{
		found = true;
		return;
	}
	int i = 0;
	for (i = 0; i < 4; i++)
	{
		if (found)
			break;
		tx = present_x + next[i][0];
		ty = present_y + next[i][1];
		
		bool f = false;
		for (int j = 0; j < snake->length; j++)
			if ((tx == snake->x[j] && ty == snake->y[j]))			//�жϸõ��Ƿ�Ϊ����
			{
				f = true;
				break;
			}
		if (maze[tx][ty] || f == true)								//�����ǽ�����������򻻷���
			continue;
		if (flag[tx][ty] == ROUTE)
		{
			flag[tx][ty] = WALL;
			path.push_back(tx);
			path.push_back(ty);
			DFS(snake, food, tx, ty, next);
		}
		
	}
	if (i == 4 && found == false && !path.empty())			/*����������ȥ��*/
	{
		path.pop_back();
		path.pop_back();
	}
	return;
}

//�����������
void Graph::BFS(Snake *const snake, Food *const food, const int start_x, const int start_y, int next[][2])
{
	//int  next[4][2] = {
	//	{ 0, 1 }, //��
	//	{ 2, 0 }, //��
	//	{ 0, -1}, //��
	//	{ -2, 0}  //��
	//};
	queue<Node>q;
	Node start;
	Node father[VERTEX][VERTEX];
	start.x = start_x;
	start.y = start_y;
	q.push(start);
	flag[start_x][start_y] = WALL;
	found = false;
	while (!q.empty())
	{
		Node present = q.front();
		q.pop();
		int tx, ty;
		for (int i = 0; i < 4; i++)
		{
			tx = present.x + next[i][0];
			ty = present.y + next[i][1];
			bool f = false;
			for (int i = 0; i < snake->length; i++)
				if ((tx == snake->x[i] && ty == snake->y[i]))
				{
					f = true;
					break;
				}
			if (maze[tx][ty] || f == true)								//�����ǽ�����������򷵻�
				continue;
			if (flag[tx][ty] == ROUTE)
			{
				flag[tx][ty] = WALL;
				Node child;
				child.x = tx;
				child.y = ty;
				q.push(child);
				father[tx][ty] = present;
			}
			if (food->FoodX == tx && food->FoodY == ty)		//�ҵ�ʳ��λ��
			{
				found = true;
				break;
			}
		}
		if (found)
			break;
	}
	if (q.empty())			//û�ҵ�·��ֱ�ӷ���
		return;
	Node temp = father[food->FoodX][food->FoodY];
	while (!(temp.x == start_x && temp.y == start_y))
	{
		path.insert(path.begin(), temp.y);
		path.insert(path.begin(), temp.x);
		temp = father[temp.x][temp.y];
	}
	path.push_back(food->FoodX);
	path.push_back(food->FoodY);
}

//��ȡ·��
void SnakeControl::ReadPath()
{

}

//����ʳ��
void Food::CreateVirtualFood(Snake *const snake, string block)
{
	int flag;
	int row;
	int column;
	int k;
	virtual_food.clear();
	if (block == "ul")	//��������ʼ��������ʳ��
	{
		column = FrameX + FrameWidth;
		row = FrameY + 1;
		while (true)
		{
			for (int i = FrameX + 2; i < column; i += 2)
			{
				v_food.first = i;
				v_food.second = row;
				flag = 0;
				for (int j = 0; j < snake->length; j++)
					if ((v_food.first == snake->x[j] && v_food.second == snake->y[j]) || v_food.first % 2 != 0)
					{
						flag = 1;
						break;
					}
				if (flag == 0)
					virtual_food.push_back(v_food);

			}
			if (v_food.second >= FrameY + FrameHigh - 1)
				break;
			row++;
			for (int i = column - 1; i > FrameX; i -= 2)
			{
				v_food.first = i;
				v_food.second = row;
				flag = 0;
				for (int j = 0; j < snake->length; j++)
					if ((v_food.first == snake->x[j] && v_food.second == snake->y[j]) || v_food.first % 2 != 0)
					{
						flag = 1;
						break;
					}
				if (flag == 0)
					virtual_food.push_back(v_food);
			}
			if (v_food.second >= FrameY + FrameHigh - 1)
				break;
			row++;
		}
	}
	else if (block == "ll")//��������ʼ��������ʳ��
	{
		column = FrameX + FrameWidth;
		row = FrameY + FrameHigh - 1;
		k = 0;
		while (true)
		{
			for (int i = FrameX + 2; i < column; i += 2)
			{
				v_food.first = i;
				v_food.second = row - k;
				flag = 0;
				for (int j = 0; j < snake->length; j++)
					if ((v_food.first == snake->x[j] && v_food.second == snake->y[j]) || v_food.first % 2 != 0)
					{
						flag = 1;
						break;
					}
				if (flag == 0)
					virtual_food.push_back(v_food);

			}
			if (v_food.second <= FrameY + 1)
				break;
			k++;
			for (int i = column - 1; i > FrameX; i -= 2)
			{
				v_food.first = i;
				v_food.second = row - k;
				flag = 0;
				for (int j = 0; j < snake->length; j++)
					if ((v_food.first == snake->x[j] && v_food.second == snake->y[j]) || v_food.first % 2 != 0)
					{
						flag = 1;
						break;
					}
				if (flag == 0)
					virtual_food.push_back(v_food);
			}
			if (v_food.second <= FrameY + 1)
				break;
			k++;
		}
	}
	else if (block == "ur") //��������ʼ��������ʳ��
	{
		column = FrameX + FrameWidth;
		row = FrameY + 1;
		while (true)
		{
			for (int i = column - 1; i > FrameX; i -= 2)
			{
				v_food.first = i;
				v_food.second = row;
				flag = 0;
				for (int j = 0; j < snake->length; j++)
					if ((v_food.first == snake->x[j] && v_food.second == snake->y[j]) || v_food.first % 2 != 0)
					{
						flag = 1;
						break;
					}
				if (flag == 0)
					virtual_food.push_back(v_food);
			}
			if (v_food.second >= FrameY + FrameHigh - 1)
				break;
			row++;
			for (int i = FrameX + 2; i < column; i += 2)
			{
				v_food.first = i;
				v_food.second = row;
				flag = 0;
				for (int j = 0; j < snake->length; j++)
					if ((v_food.first == snake->x[j] && v_food.second == snake->y[j]) || v_food.first % 2 != 0)
					{
						flag = 1;
						break;
					}
				if (flag == 0)
					virtual_food.push_back(v_food);

			}
			if (v_food.second >= FrameY + FrameHigh - 1)
				break;
			row++;
		}

	}
	else
	{
		k = 0;
		column = FrameX + FrameWidth;
		row = FrameY + FrameHigh - 1;
		while (true)
		{
			for (int i = column - 1; i > FrameX; i -= 2)
			{
				v_food.first = i;
				v_food.second = row - k;
				flag = 0;
				for (int j = 0; j < snake->length; j++)
					if ((v_food.first == snake->x[j] && v_food.second == snake->y[j]) || v_food.first % 2 != 0)
					{
						flag = 1;
						break;
					}
				if (flag == 0)
					virtual_food.push_back(v_food);
			}
			if (v_food.second <= FrameY + 1)
				break;
			k++;

			for (int i = FrameX + 2; i < column; i += 2)
			{
				v_food.first = i;
				v_food.second = row - k;
				flag = 0;
				for (int j = 0; j < snake->length; j++)
					if ((v_food.first == snake->x[j] && v_food.second == snake->y[j]) || v_food.first % 2 != 0)
					{
						flag = 1;
						break;
					}
				if (flag == 0)
					virtual_food.push_back(v_food);

			}
			if (v_food.second <= FrameY + 1)
				break;
			k++;
		}
	}
}
