#include <graphics.h>
#include <iostream>
#include <mmsystem.h>
#include "MenuEasyx.h"
#include "GameEasyx.h"
#pragma comment(lib, "winmm.lib")  // 链接 winmm 库

int main()
{
	MenuEasyx menu;
	menu.run();

	return 0;
}