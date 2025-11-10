#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <iostream>
#include <tchar.h>
#include "utils.h"

void DrawRectangleWithText(int left, int top, int right, int bottom, const wchar_t* text)
{
    rectangle(left, top, right, bottom);
    outtextxy(left + 40, top + 15, text);
}
