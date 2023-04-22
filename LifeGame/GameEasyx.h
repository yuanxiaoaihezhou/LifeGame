#pragma once
#include "GlobalConfig.h"

class GameEasyx 
{
private:
	void initGrid();//初始化矩阵
	void drawGrid();//更新矩阵数组
	void updateGrid();//更新画面

	int mGrid[COLS][ROWS];
	int mUpdateGrid[COLS][ROWS];
public:
	GameEasyx();
	void run();
};
