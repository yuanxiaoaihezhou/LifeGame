#include <graphics.h>
#include <iostream>
#include <mmsystem.h>
#include "MenuEasyx.h"
#include "GameEasyx.h"
#pragma comment(lib, "winmm.lib")  // Á´½Ó winmm ¿â

int main()
{
	MenuEasyx menu;
	menu.run();

	return 0;
}