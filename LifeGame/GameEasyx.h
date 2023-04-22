#pragma once
#include <graphics.h>
#include "GlobalConfig.h"

class GameEasyx 
{
private:
	void initNullGrid();// 初始化0矩阵
	void initRandomGrid();// 初始化随机矩阵
	void drawGrid(int FillTheme);// 更新矩阵数组
	void updateGrid();// 更新画面
	bool handleInput();
	bool isSame() const;// 判断数组前后是否相等 

	bool mStartGame = 0;

	IMAGE imgOTTO;
	IMAGE imgAVA;

	bool mHandleRemenu = 0;
	int mGeneration = 0;
	bool mGrid[COLS][ROWS];
	bool mGridCopy[COLS][ROWS];
	bool mUpdateGrid[COLS][ROWS];
public:
	GameEasyx();
	void run();
};
