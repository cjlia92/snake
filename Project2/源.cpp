#include<iostream>
#include<windows.h>
#include<vector>
using namespace std;
//在指定位置显示内容 
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
void init(int X1,int Y1,int X2,int Y2)
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
}
struct Snake
{
	int x, y;
};
vector<Snake>snake;

int main()
{
	init(1,1,60,30);//活动范围
	return 0;
} 
