/*注意！需要C99支持*/
#include "Snake.h"

int main()
{
	srand((unsigned)time(NULL));
	SnakeControl *const control = new SnakeControl();
	control->StartGame();
	control->GameOver();
	delete control;
	system("pause");
	return 0;
}
