#include<iostream>
#include<windows.h>
#include<vector>
using namespace std;
//��ָ��λ����ʾ���� 
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
	printf("%c",c);//�����ָ�����ַ� 
}  
//��ʼ������ 
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
	snake.clear();//��ʼ�����	
	Snake t{};
	t.x = (X1 + X2) / 2;
	t.y = (Y1 + Y2) / 2;
	snake.push_back(t);
}
//��ʾ�ߵ�����
int XX[4] = { 0,0,-1,1 };
int YY[4] = { -1,1,0,0 };
void Print(int direction)
{
	int n = snake.size() - 1;
	gotoxy(snake[n].x, snake[n].y, ' ');//�������β���µĺۼ� 
	for (int i = n; i >= 1; i--)
		snake[i] = snake[i - 1];//���нڵ����
	snake[0].x += XX[direction];
	snake[0].y += YY[direction];
	for (int i = 1; i <= n; i++)
		gotoxy(snake[i].x, snake[i].y, '*');
	gotoxy(snake[0].x, snake[0].y, '@');//��ͷ��@��ʾ 
}


int main()
{
	init(1,1,60,30);//���Χ
	while (true)
	{
		Print(1);
		Sleep(500);//�ӳ�500ms�����Ƴ�����ʾʱ��	
	}
	return 0;
} 
