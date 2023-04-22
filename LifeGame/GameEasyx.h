#pragma once
#include "GlobalConfig.h"

class GameEasyx 
{
private:
	void initNullGrid();// 初始化0矩阵
	void initRandomGrid();// 初始化随机矩阵
	void drawGrid(int FillTheme);// 更新矩阵数组
	void updateGrid();// 更新画面
	bool handleInput();
	bool isSame();// 判断数组前后是否相等 

	bool mStartGame = 0;

	bool mHandleRemenu = 0;
	int mGeneration = 0;
	int mGrid[COLS][ROWS];
	int mGridCopy[COLS][ROWS];
	int mUpdateGrid[COLS][ROWS];
public:
	GameEasyx();
	void run();
};
