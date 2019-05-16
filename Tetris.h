#ifndef TETRIS_H_
#define TETRIS_H_
#include <windows.h>						//void setCurPos(int i, int j);
//长条形
const int A1 = 0;
const int A2 = 7;
//方块
const int B = 1;
//L 形状
const int C11 = 2;
const int C12 = 8;
const int C13 = 9;
const int C14 = 10;
//L 的另一个形状
const int C21 = 3;
const int C22 = 11;
const int C23 = 12;
const int C24 = 13;
//Z 形状
const int D11 = 4;
const int D12 = 14;
//Z 的另一个形状
const int D21 = 5;
const int D22 = 15;

//土字形
const int E31 = 6;
const int E32 = 16;
const int E33 = 17;
const int E34 = 18;

class tetris
{
private:
	int map[12][23];						//背景
	int top;								//当前的最高点
	int score;								//分数
	int level;								//难度等级
	int ID;									//当前的方块的形状
	int hotPoint[2];						//热点(当前活动的点，所有图形基于此点作图)	
public:
	tetris()
	{
		for (int i = 0; i < 12; i++)
		for (int j = 0; j < 23; j++)
			map[i][j] = 0;
		top = 99;
		score = 0;
		ID = 0;
		hotPoint[0] = 5;					//下落点的横坐标
		hotPoint[1] = 0;					//下落点的纵坐标
	}
	void DrawMap();							//绘制地图
	void initInterface();					//初始化界面
	void DrawBox(int x, int y, int id);		//绘制图形
	void DrawBox_nc(int x, int y, int id);	
	void ReBox(int x, int y, int id);		//擦除图形
    void ReBox_nc(int x, int y, int id);
	int  IsJudge(int x, int y, int id);		//是否可以绘制图形
	int  TurnBlock(int id);					//旋转方块
	void UpdateMap(int id);					//更新画面
	void RunGame();							//运行
};

#endif
