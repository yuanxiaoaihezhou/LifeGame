#pragma once
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

	void drawMenu();
	void drawSettings();
	void drawDeveloperInfo();
public:
	void run();
	MenuEasyx();
};