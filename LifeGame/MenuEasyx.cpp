#include "MenuEasyx.h"
#include "GameEasyx.h"
#include "GlobalConfig.h"
#include "utils.h"
#include <graphics.h>
#include <cstdio>

MenuEasyx::MenuEasyx()
{
    //initgraph(WINDOW_WIDTH, WINDOW_HEIGHT + 50, EX_SHOWCONSOLE); // debug
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT + 50); // release
	drawMenu();
    PlaySound(TEXT("res\\OpeingTheme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);  // 播放音乐
}

void MenuEasyx::drawButton(int x1, int y1, int x2, int y2, const TCHAR* text, int textX, int textY, bool selected)
{
    if (selected)
    {
        setfillcolor(YELLOW);
        fillrectangle(x1, y1, x2, y2);
    }
    else
    {
        setfillcolor(WHITE);
        fillrectangle(x1, y1, x2, y2);
    }
    rectangle(x1, y1, x2, y2);
    outtextxy(textX, textY, text);
}

void MenuEasyx::drawMenu()
{
    printf("绘制主菜单");
    setbkcolor(WHITE);
    cleardevice();

    // 绘制菜单
    setlinestyle(PS_SOLID, 1); // 设置线型为实线，线宽1个像素
    setlinecolor(BLACK);       // 设置线的颜色为黑色

    settextstyle(40, 0, 0);
    settextcolor(BLACK);
    TCHAR a[] = _T("Life Game");
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
    printf("主界面运行\n");
    FlushMouseMsgBuffer();

    while (!mStartGame && !mSettings && !mDevelopInfo && !mQuitGame)
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
                    PlaySound(NULL, NULL, 0);  // 停止音乐播放
                    {
                        GameEasyx game;
                        game.run();
                    }
                    drawMenu();
                    PlaySound(TEXT("res\\OpeingTheme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);  // 播放音乐
                    mStartGame = false;
                }

                if (msg.x >= 200 && msg.x <= 400 && msg.y >= 300 && msg.y <= 350)
                {
                    mSettings = true;
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
                    closegraph();
                }
            }
        }
    }
}

void MenuEasyx::drawSettings()
{
    // 清空鼠标事件队列
    FlushMouseMsgBuffer();

    setbkcolor(WHITE);
    cleardevice();

    // 绘制设置页面

    settextstyle(40, 0, 0);
    settextcolor(BLACK);
    TCHAR a[] = _T("设置");
    outtextxy(200, 100, a);

    // 绘制主题选择按钮
    settextstyle(16, 0, 0);
    drawButton(220, 260, 280, 290, _T("默认"), 230, 265, mIsDefaultSelected);
    drawButton(290, 260, 350, 290, _T("OTTO"), 300, 265, mIsOTTSelected);
    drawButton(360, 260, 420, 290, _T("A-Soul"), 370, 265, mIsASoulSelected);

    settextstyle(20, 0, 0);
    rectangle(200, 200, 400, 250);
    TCHAR b[] = _T("风格");
    outtextxy(210, 210, b);

    // 绘制帧率选择按钮
    settextstyle(16, 0, 0);
    drawButton(220, 360, 280, 390, _T("6帧"), 230, 365, mIs6Selected);
    drawButton(290, 360, 350, 390, _T("无限"), 300, 365, mIsNoLimitedSelected);

    settextstyle(20, 0, 0);
    rectangle(200, 300, 400, 350);
    TCHAR c[] = _T("画面质量");
    outtextxy(210, 310, c);

    rectangle(220, 460, 430, 490);
    TCHAR AIGUO[] = _T("文字，我只用中国的！");
    outtextxy(230, 465, AIGUO);

    if (mAiGuo)
    {
        IMAGE AIGUO;
        loadimage(&AIGUO, _T("res\\HANJIAN.png"));
        putimage(440, 400, &AIGUO);
    }

    rectangle(200, 400, 400, 450);
    TCHAR d[] = _T("语言");
    outtextxy(210, 410, d);

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
    while (mSettings)
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                // 如果用户点击了确定或取消按钮
                if ((msg.x >= 200 && msg.x <= 250 && msg.y >= 500 && msg.y <= 530) ||
                    (msg.x >= 350 && msg.x <= 400 && msg.y >= 500 && msg.y <= 530))
                {
                    // 返回主菜单界面
                    mSettings = false;
                    mAiGuo = false;
                    drawMenu();
                    break;
                }

                // 如果用户点击了默认按钮
                if (msg.x >= 220 && msg.x <= 280 && msg.y >= 260 && msg.y <= 290)
                {
                    printf("默认\n");
                    Theme = 0;
                    mIsDefaultSelected = true;
                    mIsOTTSelected = false;
                    mIsASoulSelected = false;
                    cleardevice();
                    drawSettings();
                }

                // 如果用户点击了 OTTO 按钮
                else if (msg.x >= 290 && msg.x <= 350 && msg.y >= 260 && msg.y <= 290)
                {
                    printf("OTTO\n");
                    Theme = 1;
                    mIsDefaultSelected = false;
                    mIsOTTSelected = true;
                    mIsASoulSelected = false;
                    cleardevice();
                    drawSettings();
                }

                // 如果用户点击了 A-Soul 按钮
                else if (msg.x >= 360 && msg.x <= 420 && msg.y >= 260 && msg.y <= 290)
                {
                    printf("A-Soul\n");
                    Theme = 2;
                    mIsDefaultSelected = false;
                    mIsOTTSelected = false;
                    mIsASoulSelected = true;
                    cleardevice();
                    drawSettings();
                }

                // 如果用户点击了 6帧 按钮
                else if (msg.x >= 220 && msg.x <= 280 && msg.y >= 360 && msg.y <= 390)
                {
                    printf("6帧\n");
                    FPS = 0;
                    mIs6Selected = true;
                    mIsNoLimitedSelected = false;
                    cleardevice();
                    drawSettings();
                }

                // 如果用户点击了 无限制帧 按钮
                else if (msg.x >= 290 && msg.x <= 350 && msg.y >= 360 && msg.y <= 390)
                {
                    printf("无限\n");
                    FPS = 1;
                    mIs6Selected = false;
                    mIsNoLimitedSelected = true;
                    cleardevice();
                    drawSettings();
                }

                // 如果用户点击了 爱国 按钮
                else if (msg.x >= 220 && msg.x <= 430 && msg.y >= 460 && msg.y <= 490)
                {
                    printf("爱国\n");
                    mAiGuo = true;
                    mciSendString(_T("play res\\HANJIAN.wav"), NULL, 0, NULL);
                    cleardevice();
                    drawSettings();
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