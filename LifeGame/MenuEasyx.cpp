#include "MenuEasyx.h"
#include "GameEasyx.h"
#include "GlobalConfig.h"
#include <graphics.h>
#include <cstdio>

MenuEasyx::MenuEasyx()
{
	drawMenu();
}

void MenuEasyx::drawMenu()
{
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT + 50, EX_SHOWCONSOLE);
    setbkcolor(WHITE);
    cleardevice();

    // 绘制菜单

    setlinestyle(PS_SOLID, 1); // 设置线型为实线，线宽1个像素
    setlinecolor(BLACK);       // 设置线的颜色为黑色

    settextstyle(40, 0, 0);
    settextcolor(BLACK);
    TCHAR a[] = _T("Game Title");
    outtextxy(200, 100, a);

    settextstyle(20, 0, 0);
    rectangle(200, 200, 400, 250);
    TCHAR b[] = _T("Start Game");
    outtextxy(240, 215, b);

    rectangle(200, 300, 400, 350);
    TCHAR c[] = _T("Settings");
    outtextxy(240, 315, c);

    rectangle(200, 400, 400, 450);
    TCHAR d[] = _T("Developer Info");
    outtextxy(240, 415, d);

    rectangle(200, 500, 400, 550);
    TCHAR e[] = _T("Quit Game");
    outtextxy(240, 515, e);

    // 刷新屏幕
    BeginBatchDraw();
    FlushBatchDraw();
}

void MenuEasyx::run() 
{
    while (!mStartGame && !mConfig && !mDevelopInfo && !mQuitGame)
    {
        // 检测鼠标事件
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                // 如果用户点击了开始游戏按钮
                if (msg.x >= 200 && msg.x <= 400 && msg.y >= 200 && msg.y <= 250)
                {
                    mStartGame = true;
                    GameEasyx* game = new GameEasyx;
                    game->run();
                    delete game;
                    drawMenu();
                    mStartGame = false;
                }

                if (msg.x >= 200 && msg.x <= 400 && msg.y >= 300 && msg.y <= 350)
                {
                    mConfig = true;
                    cleardevice();
                    printf("进入设置页面\n"); // 添加调试输出
                    drawSettings();
                }

                // 如果用户点击了开发者信息按钮
                if (msg.x >= 200 && msg.x <= 400 && msg.y >= 400 && msg.y <= 450)
                {
                    mDevelopInfo = true;
                    cleardevice();
                    printf("进入开发者信息页面\n"); // 添加调试输出
                    drawDeveloperInfo();
                }

                if (msg.x >= 200 && msg.x <= 400 && msg.y >= 500 && msg.y <= 550)
                {
                    mQuitGame = true;
                }
            }
        }

        /*if (mStartGame == true)
        {
            GameEasyx* game = new GameEasyx;
            game->run();
            delete game;
            drawMenu();
        }*/

        if (mQuitGame == true)
        {
            closegraph();
        }
    }
}

void MenuEasyx::drawSettings()
{
    setbkcolor(WHITE);
    cleardevice();

    // 绘制设置页面

    settextstyle(40, 0, 0);
    settextcolor(BLACK);
    TCHAR a[] = _T("设置");
    outtextxy(200, 100, a);

    settextstyle(20, 0, 0);
    rectangle(200, 200, 400, 250);
    TCHAR b[] = _T("音量");
    outtextxy(210, 210, b);

    rectangle(200, 300, 400, 350);
    TCHAR c[] = _T("画面质量");
    outtextxy(210, 310, c);

    rectangle(200, 400, 400, 450);
    TCHAR d[] = _T("语言");
    outtextxy(210, 410, d);

    // 添加其他设置选项的绘制代码

    // 添加确定和取消按钮
    settextstyle(16, 0, 0);
    rectangle(200, 500, 250, 530);
    TCHAR e[] = _T("确定");
    outtextxy(210, 505, e);

    rectangle(350, 500, 400, 530);
    TCHAR f[] = _T("取消");
    outtextxy(360, 505, f);

    // 刷新屏幕
    BeginBatchDraw();
    FlushBatchDraw();

    // 等待用户交互
    while (1)
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                // 如果用户点击了确定按钮
                if (msg.x >= 200 && msg.x <= 250 && msg.y >= 500 && msg.y <= 530)
                {
                    // 返回主菜单界面
                    mConfig = false;
                    drawMenu();
                    return;
                }

                // 如果用户点击了取消按钮
                if (msg.x >= 350 && msg.x <= 400 && msg.y >= 500 && msg.y <= 530)
                {
                    // 返回主菜单界面
                    mConfig = false;
                    drawMenu();
                    return;
                }
            }
        }
    }
}

void MenuEasyx::drawDeveloperInfo()
{
    setbkcolor(WHITE);
    cleardevice();

    // 绘制开发者信息页面
    settextstyle(40, 0, 0);
    settextcolor(BLACK);
    TCHAR a[] = _T("开发者信息");
    outtextxy(150, 100, a);

    settextstyle(20, 0, 0);
    TCHAR b[] = _T("开发者：nad_iz");
    outtextxy(220, 200, b);

    TCHAR c[] = _T("发布日期：2023年5月");
    outtextxy(220, 250, c);

    TCHAR d[] = _T("联系方式：2211133@mail.nankai.edu.cn");
    outtextxy(220, 300, d);

    // 添加返回按钮
    settextstyle(16, 0, 0);
    rectangle(200, 500, 400, 530);
    TCHAR e[] = _T("返回");
    outtextxy(280, 505, e);

    // 刷新屏幕
    BeginBatchDraw();
    FlushBatchDraw();

    // 等待用户交互
    while (1)
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                // 如果用户点击了返回按钮
                if (msg.x >= 200 && msg.x <= 400 && msg.y >= 500 && msg.y <= 530)
                {
                    // 返回主菜单界面
                    mDevelopInfo = false;
                    drawMenu();
                    return;
                }
            }
        }
    }
}