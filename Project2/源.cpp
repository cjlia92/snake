#include<iostream>
#include<windows.h>
#include<vector>
#include<conio.h>
using namespace std;
//在指定位置显示内容 
struct Snake
{
	int x, y;
};
vector<Snake>snake;
void gotoxy(int x,int y,char c)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; //variablendklaration
	HANDLE hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
	csbiInfo.dwCursorPosition.X = x; //cursorposition X koordinate festlegen
	csbiInfo.dwCursorPosition.Y = y; //cursorposition Y koordinate festlegen
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition); //den cursor an die festgelegte koordinate setzen
	printf("%c",c);//输出你指定的字符 
}  
//初始化函数 

int X1 = 1, Y1 = 1;
int X2 = 60, Y2 = 30;
void init()
{
	for (int i = X1; i <= X2; i++)
	{
		gotoxy(i, Y1, '#');
		gotoxy(i, Y2, '#');
	}
	for (int j = Y1; j <= Y2; j++)
	{
		gotoxy(X1, j, '#');
		gotoxy(X2, j, '#');
	}
	snake.clear();//初始化清空	
	Snake t{};
	t.x = (X1 + X2) / 2;
	t.y = (Y1 + Y2) / 2;
	snake.push_back(t);
}
//显示蛇的内容
int XX[4] = { 0,0,-1,1 };
int YY[4] = { -1,1,0,0 };
void Print(int direction)
{
	int n = snake.size() - 1;
	gotoxy(snake[n].x, snake[n].y, ' ');//先清除蛇尾留下的痕迹 
	for (int i = n; i >= 1; i--)
		snake[i] = snake[i - 1];//进行节点更新
	snake[0].x += XX[direction];
	snake[0].y += YY[direction];
	for (int i = 1; i <= n; i++)
		gotoxy(snake[i].x, snake[i].y, '*');
	gotoxy(snake[0].x, snake[0].y, '@');//蛇头用@表示 
}


int main()
{
	init();//活动范围
	int direction = 1;
	while (true)
	{
		Print(direction);
		if (_kbhit())//判断有键盘指令输入 
		{
			char c = _getch();
			if (c == 'W')//往上 
				direction = 0;
			else if (c == 'S')//往下 
				direction = 1;
			else if (c == 'A')//往左 
				direction = 2;
			else if (c == 'D')//往右 
				direction = 3;
		}
		gotoxy(X2 + 1, Y2 + 1, ' ');
		Sleep(300);//延迟300ms，控制程序显示时间	
	}
	return 0;
} 
