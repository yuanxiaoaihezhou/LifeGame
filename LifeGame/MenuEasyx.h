#pragma once
class MenuEasyx
{
private:
	bool mStartGame = 0;
	bool mConfig = 0;
	bool mDevelopInfo = 0;
	bool mQuitGame = 0;
	void drawMenu();
	void drawSettings();
	void drawDeveloperInfo();
public:
	void run();
	MenuEasyx();
};