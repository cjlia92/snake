#include<iostream>
#include<windows.h>
#include<vector>
#include<conio.h>
#define random(a,b) (rand()%(b-a+1)+a)
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
//ʳ������
int food_x, food_y;
bool search(int L, int R)
{
	if (L > R)return false;
	int MID = random(L, R);
	int d = X2 - X1 - 1;//���ܰ���Χǽ����Ҫ��Χǽ�Ŀ�ȼ�ȥ 
	int y = (MID + d) / d + X1;
	int t = MID % d;
	int x = Y1;
	if (t == 0)
		x += d;
	else x += t;
	bool flag = false;
	for (int i = 0; i < snake.size(); i++)
	{
		if (snake[i].x == x && snake[i].y == y)
		{
			flag = true;
			break;
		}
	}
	if (flag)
	{
		bool res = search(L, MID - 1);
		if (res)return true;
		res = search(MID + 1, R);
		if (res)return true;
		return false;
	}
	else
	{
		food_x = x;
		food_y = y;
		return true;
	}
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
	gotoxy(food_x, food_y, 'O');
}


int main()
{
	init();//���Χ
	int direction = 1;
	bool is_food = false;//�Ƿ���ʳ���ж�
	while (true)
	{
		if (is_food == false)
		{
			search((X1 + 2) * (Y1 + 2), (X2 - 2) * (Y2 - 2));
			is_food = true;
		}
		Print(direction);

		if (snake[0].x == food_x && snake[0].y == food_y)
		{
			Snake t;
			t.x = food_x, t.y = food_y;
			is_food = false;
			snake.insert(snake.begin(), t);
		}

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
		gotoxy(X2 + 1, Y2 + 1, ' ');//Ϊ�˲�����Ϸ��������ʾ��ɫ���Ӱ�����Ч�� 
		Sleep(150);//�ӳ�150ms�����Ƴ�����ʾʱ��	
	}
	return 0;
} 
