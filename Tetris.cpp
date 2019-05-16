#include <iostream>
#include <conio.h>							//getch()
#include <time.h>
#include "Tetris.h"
using std::cout;
using std::endl;

int sharp[19][9] =												//每个一维数组内有8个点，没两个点是一个 形状的一个小方格，在4*4的表格中
{
	{ 0, 0, 0, 1, 0, 2, 0, 3, FOREGROUND_RED | FOREGROUND_INTENSITY }, 						//长条形
	{ 0, 0, 1, 0, 0, 1, 1, 1, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY },	//方形
	{ 0, 0, 0, 1, 1, 1, 2, 1, FOREGROUND_GREEN | FOREGROUND_RED },							//L形
	{ 0, 1, 1, 1, 2, 1, 2, 0, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY },	//反L形
	{ 0, 0, 1, 0, 1, 1, 2, 1, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY },	//Z形
	{ 1, 0, 2, 0, 0, 1, 1, 1, FOREGROUND_GREEN | FOREGROUND_INTENSITY },					//反Z形
	{ 0, 0, 0, 1, 0, 2, 1, 1, FOREGROUND_BLUE | FOREGROUND_INTENSITY },						//土形
	//上面形状的变换
	{ 0, 0, 1, 0, 2, 0, 3, 0, FOREGROUND_RED | FOREGROUND_INTENSITY },						
	{ 1, 0, 1, 1, 1, 2, 0, 2, FOREGROUND_GREEN | FOREGROUND_RED },
	{ 0, 0, 1, 0, 2, 0, 2, 1, FOREGROUND_GREEN | FOREGROUND_RED },
	{ 0, 0, 1, 0, 0, 1, 0, 2, FOREGROUND_GREEN | FOREGROUND_RED },
	{ 0, 0, 1, 0, 1, 1, 1, 2, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY },
	{ 0, 0, 1, 0, 2, 0, 0, 1, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY },
	{ 0, 0, 0, 1, 0, 2, 1, 2, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY },
	{ 1, 0, 0, 1, 1, 1, 0, 2, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY },
	{ 0, 0, 0, 1, 1, 1, 1, 2, FOREGROUND_GREEN | FOREGROUND_INTENSITY },
	{ 0, 0, 1, 0, 2, 0, 1, 1, FOREGROUND_BLUE | FOREGROUND_INTENSITY },
	{ 0, 1, 1, 0, 1, 1, 1, 2, FOREGROUND_BLUE | FOREGROUND_INTENSITY },
	{ 1, 0, 0, 1, 1, 1, 2, 1, FOREGROUND_BLUE | FOREGROUND_INTENSITY }
};

int high[19] = { 4, 2, 2, 2, 2, 2, 3, 1, 3, 2, 3, 3, 2, 3, 3, 3, 2, 3, 2 };					//数组是用来保存上面每个一维数组的各个形状高度的

void setCurPos(int i, int j, int color = 003)				//设定光标的位置
{															
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);				//获得标准输出句柄
	SetConsoleTextAttribute(out, color);
	COORD pos = { i * 2, j };
	SetConsoleCursorPosition(out, pos);
}


void tetris::DrawMap()
{
	//地图框架

	for (int b = 0; b < 25; b++)			// 0 - 24
	{
		setCurPos(0, b);
		cout << "■";
		setCurPos(13, b);
		cout << "■";
	}
	for (int c = 0; c < 14; c++)
	{
		setCurPos(c, 24);
		cout << "■";
	}
	//information框架
	for (int d = 15; d <= 21; d++)
	{
		setCurPos(d, 0);
		cout << "■";
		setCurPos(d, 8);
		cout << "■";
	}
		for (int e = 22; e <= 28; e++)
	{
		setCurPos(e, 0);
		cout << "■";
		setCurPos(e, 8);
		cout << "■";
	}
	for (int i = 0; i <= 8; i++)
	{
		setCurPos(15, i);
		cout << "■";
		setCurPos(21, i);
		cout << "■";
		setCurPos(28, i);
		cout << "■";
	}
	setCurPos(16, 12);
	cout << "俄罗斯方块";
	setCurPos(16, 15);
	cout << " 分数： " << score;
}

void tetris::initInterface()
{
	char x;
	while (1)
	{
		system("cls");
		cout << endl;
		cout << endl;
		cout << "             俄罗斯方块               " << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "       A,D左右移动  S向下加速         " << endl;
		cout << "        W  转动方块  p暂停        " << endl;
		cout << "         上下左右也可以使用         " << endl;
		cout << "			 空格直接落下         " << endl;
		cout << endl;
		cout << endl;
		cout << endl;	
		cout << "             按任意键开始               " << endl;
		cout << endl;
		cout << endl;
		setCurPos(8, 10);
		x = _getch();
		break;
		
	}
}

void tetris::DrawBox(int x, int y, int id)
{
	int nx = 0, ny = 0;
	int color = sharp[id][8];
	for (int i = 0; i < 4; i++)
	{
		nx = x + sharp[id][i * 2];
		ny = y + sharp[id][i * 2 + 1];
		setCurPos(nx + 1, ny + 1, color);
		cout << "■";
	}
}

void tetris::DrawBox_nc(int x, int y, int id)
{
	int nx = 0, ny = 0;
	int color = sharp[id][8];
	for (int i = 0; i < 4; i++)
	{
		nx = x + sharp[id][i * 2];
		ny = y + sharp[id][i * 2 + 1];
		setCurPos(nx + 1, ny + 1, 8);
		cout << "■";
	}
}


void tetris::ReBox(int x, int y, int id)
{
	int nx = 0, ny = 0;
	for (int i = 0; i < 4; i++)
	{
		nx = x + sharp[id][i * 2];
		ny = y + sharp[id][i * 2 + 1];
		setCurPos(nx + 1, ny + 1);
		cout << " ";
	}
}
void tetris::ReBox_nc(int x, int y, int id)
{
	int nx = 0, ny = 0;
	for (int i = 0; i < 4; i++)
	{
		nx = x + sharp[id][i * 2];
		ny = y + sharp[id][i * 2 + 1];
		setCurPos(nx + 1, ny + 1);
		cout << "  ";
	}
}



int tetris::IsJudge(int x, int y, int id)
{
	int nx = 0, ny = 0;
	for (int i = 0; i < 4; i++)
	{
		nx = x + sharp[id][i * 2];
		ny = y + sharp[id][i * 2 + 1];
		if (nx < 0 || nx >= 12 || ny < 0 || ny >= 23 || map[nx][ny] != 0)	//不能放了，返回0
			return 0;
	}
	return 1;
}

int tetris::TurnBlock(int id)
{
	switch (id)
	{
	case A1: id = A2;  break;
	case A2: id = A1;  break;

	case B:  id = B;   break;

	case C11:id = C12; break;
	case C12:id = C13; break;
	case C13:id = C14; break;
	case C14:id = C11; break;

	case C21:id = C22; break;
	case C22:id = C23; break;
	case C23:id = C24; break;
	case C24:id = C21; break;

	case D11:id = D12; break;
	case D12:id = D11; break;

	case D21:id = D22; break;
	case D22:id = D21; break;

	case E31:id = E32; break;
	case E32:id = E33; break;
	case E33:id = E34; break;
	case E34:id = E31; break;
	}
	return id;
}

void tetris::UpdateMap(int id)
{
	int nx = 0, ny = 0;
	int flag;
	int clear = 0;							//清除了多少个格子
	for (int i = 0; i < 4; i++)
	{
		nx = hotPoint[0] + sharp[id][i * 2];
		ny = hotPoint[1] + sharp[id][i * 2 + 1];
		map[nx][ny] = sharp[id][8];							//加上颜色值
	}
	if (hotPoint[1] < top)				//因为地图的最上面是0，最下面是22，所以如果有了更高的方块，就是比top小，所以更新一下top，方便下面下移 行使用
		top = hotPoint[1];
	for (int j = hotPoint[1]; j < hotPoint[1] + high[id]; j++)	//从上向下可以，从下向上容易出问题
	{
		flag = 0;
		for (int i = 0; i < 12; i++)
		{
			if (map[i][j] == 0)						//没有可以消除的
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)								//可以消除当前行
		{
			for (int k = j; k >= top; k--)
			{
				if (k == 0)							//消除 到了最顶行
				{
					for (int i = 0; i < 12; i++)
					{
						map[i][k] = 0;
						setCurPos(i + 1, k + 1);
						cout << " ";
					}
				}
				else
				{
					for (int i = 0; i < 12; i++)
					{
						map[i][k] = map[i][k - 1];
						setCurPos(i + 1, k + 1);	//因为有两条图形框边， 游戏运行过程中的坐标系相对于 真正的坐标系是 x、y 都加 1 的
						if (map[i][k] == 0)			//被删除行的 上一行是空的，所以这一行也是空的
							cout << " ";
						else                        //上一行不是空的
						{
							int tempColor = map[i][k];
							setCurPos(i + 1, k + 1, tempColor);
							cout << "■";
						}
					}
				}
			}
			top++;									//消除成功，最高点下降一个
			clear++;
			score += clear * 100;
		}
	}
	setCurPos(16, 15);
	cout << " 分数： " << score;
}

void tetris::RunGame()
{
	initInterface();
	system("cls");
	DrawMap();

	int x = ' ';										//读取键盘信息										
	int nextId = 0;
	int nextnextId=0;
	int curId = 0;
	int flag=0;
	srand((unsigned)time(0));
	curId = rand() % 7;
	nextId = rand() % 7;
	nextnextId=rand()%7;
	DrawBox(hotPoint[0], hotPoint[1], curId);			//画当前图形
	DrawBox(17, 3, nextId);								//画下一个图形
	DrawBox_nc(22,3,nextId);
	clock_t clockLast, clockNow;
	clockNow=clockLast=clock();
	while (1)
	{
		clockNow=clock();
		if (clockNow-clockLast>=(10-score/1000)*100||flag==1)								//可以自动下移
		{
			clockLast=clock();
			if (IsJudge(hotPoint[0], hotPoint[1] + 1, curId) == 0)	//下个位置无效，到底了
			{
				UpdateMap(curId);						//更新一下画面
				ReBox(17, 3, nextId);					//清除原来的下一个图形   
				ReBox_nc(22,3,nextnextId);
				flag= 0;
				curId = nextId;
				nextId=nextnextId;
				nextnextId = rand() % 7;
				hotPoint[0] = 5;						//更新热点
				hotPoint[1] = 0;
				DrawBox(hotPoint[0], hotPoint[1], curId);
				DrawBox(17, 3, nextId);					//画上现在的下一个图形
				DrawBox_nc(22, 3, nextnextId);
				if (IsJudge(hotPoint[0], hotPoint[1], curId) == 0)		//无法绘制当前图形
				{
					system("cls");
					cout << "游戏结束，得分为：" << score << endl;
					system("pause");
					exit(0);
				}
			}
			else
			{
				ReBox(hotPoint[0], hotPoint[1], curId);
				hotPoint[1]++;
				DrawBox(hotPoint[0], hotPoint[1], curId);
			}
		}
		if (_kbhit())										//读取键盘信息
		{
			x = _getch();
			if(x==224)
			{
				int y=_getch();
				switch (y)
				{
				case 72:
					x='W';
					break;
				case 75:
					x='A';
					break;
				case 77:
					x='D';
					break;
				case 80:
					x='S';
					break;
				}
			}
			if ((x == 'a' || x == 'A')&&flag==0)						//左移
			{
				if (IsJudge(hotPoint[0] - 1, hotPoint[1], curId))
				{
					ReBox(hotPoint[0], hotPoint[1], curId);
					hotPoint[0]--;
					DrawBox(hotPoint[0], hotPoint[1], curId);
				}
			}
			else if ((x == 'd' || x == 'D')&&flag==0)				//右移
			{
				if (IsJudge(hotPoint[0]+1, hotPoint[1], curId))
				{
					ReBox(hotPoint[0], hotPoint[1], curId);
					hotPoint[0]++;
					DrawBox(hotPoint[0], hotPoint[1], curId);
				}
			}
			else if (x == 's' || x == 'S')				//向下加速
			{
				if (IsJudge(hotPoint[0], hotPoint[1] + 1, curId))
				{
					ReBox(hotPoint[0], hotPoint[1], curId);
					hotPoint[1]++;
					DrawBox(hotPoint[0], hotPoint[1], curId);
				}
			}
			else if ((x == 'w' || x == 'W')&&flag==0)
			{
				int temp = curId;
				curId = TurnBlock(curId);
				if (IsJudge(hotPoint[0], hotPoint[1], curId))
				{
					ReBox(hotPoint[0], hotPoint[1], temp);
					DrawBox(hotPoint[0], hotPoint[1], curId);
				}
				else
					curId = temp;
			}
			else if (x == ' ')								//直接落地
			{
				while (IsJudge(hotPoint[0], hotPoint[1] + 1, curId))
				{
					ReBox(hotPoint[0], hotPoint[1], curId);
					hotPoint[1]++;
					DrawBox(hotPoint[0], hotPoint[1], curId);
				}
				flag=1;
			}
			else if (x == 'P'|| x=='p')                     //暂停
			{
				getch();
			}
			while (_kbhit())								//读取掉剩下的键盘信息s
				_getch();
		}
	

	}
}
