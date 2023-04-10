#include<iostream>
#include<windows.h>
#include<vector>
#include<conio.h>
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
	init();//���Χ
	int direction = 1;
	while (true)
	{
		Print(direction);
		if (_kbhit())//�ж��м���ָ������ 
		{
			char c = _getch();
			if (c == 'W')//���� 
				direction = 0;
			else if (c == 'S')//���� 
				direction = 1;
			else if (c == 'A')//���� 
				direction = 2;
			else if (c == 'D')//���� 
				direction = 3;
		}
		gotoxy(X2 + 1, Y2 + 1, ' ');
		Sleep(300);//�ӳ�300ms�����Ƴ�����ʾʱ��	
	}
	return 0;
} 
