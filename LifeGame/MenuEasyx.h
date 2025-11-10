#pragma once
#include <tchar.h>
class MenuEasyx
{
private:
	bool mStartGame = 0;
	bool mSettings = 0;
	bool mDevelopInfo = 0;
	bool mQuitGame = 0;

	bool mIsDefaultSelected = 1;
	bool mIsOTTSelected = false; // 表示是否选中了 OTTO 按钮
	bool mIsASoulSelected = false; // 表示是否选中了 A-Soul 按钮

	bool mIs6Selected = 0;
	bool mIsNoLimitedSelected = 1;

	bool mAiGuo = 0;

	void drawMenu();
	void drawSettings();
	void drawDeveloperInfo();
	void drawButton(int x1, int y1, int x2, int y2, const TCHAR* text, int textX, int textY, bool selected = false);
public:
	void run();
	MenuEasyx();
};