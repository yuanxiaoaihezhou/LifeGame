#include "MenuEasyx.h"
#include "GameEasyx.h"
#include "GlobalConfig.h"
#include <graphics.h>
#include <cstdio>

MenuEasyx::MenuEasyx()
{
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT + 50, EX_SHOWCONSOLE);
	drawMenu();
    PlaySound(TEXT("res\\OpeingTheme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);  // 播放音乐
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
                    PlaySound(NULL, NULL, 0);  // 停止音乐播放
                    GameEasyx* game = new GameEasyx;
                    game->run();
                    delete game;
                    drawMenu();
                    PlaySound(TEXT("res\\OpeingTheme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);  // 播放音乐
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

    // 绘制默认按钮
    settextstyle(16, 0, 0);
    if (mIsDefaultSelected) 
    {
        setfillcolor(YELLOW); // 如果默认按钮被选中，填充黄色
        fillrectangle(220, 260, 280, 290);
    }
    else
    {
        setfillcolor(WHITE); // 否则填充白色
        fillrectangle(220, 260, 280, 290);
    }
    rectangle(220, 260, 280, 290);
    TCHAR defaultTheme[] = _T("默认");
    outtextxy(230, 265, defaultTheme);

    // 绘制OTTO按钮
    if (mIsOTTSelected) 
    {
        setfillcolor(YELLOW); // 如果 OTTO 按钮被选中，填充黄色
        fillrectangle(290, 260, 350, 290);
    }
    else 
    {
        setfillcolor(WHITE); // 否则填充白色
        fillrectangle(290, 260, 350, 290);
    }
    rectangle(290, 260, 350, 290);
    TCHAR OTTO[] = _T("OTTO");
    outtextxy(300, 265, OTTO);

    // 绘制A-Soul按钮
    if (mIsASoulSelected) 
    {
        setfillcolor(YELLOW); // 如果 A-Soul 按钮被选中，填充黄色
        fillrectangle(360, 260, 420, 290);
    }
    else 
    {
        setfillcolor(WHITE); // 否则填充白色
        fillrectangle(360, 260, 420, 290);
    }
    rectangle(360, 260, 420, 290);
    TCHAR AS[] = _T("A-Soul");
    outtextxy(370, 265, AS);

    settextstyle(20, 0, 0);
    rectangle(200, 200, 400, 250);
    TCHAR b[] = _T("风格");
    outtextxy(210, 210, b);

    // 绘制6帧按钮
    if (mIs6Selected)
    {
        setfillcolor(YELLOW);
        fillrectangle(220, 360, 280, 390);
    }
    rectangle(220, 360, 280, 390);
    TCHAR sixFrames[] = _T("6帧");
    outtextxy(230, 365, sixFrames);

    // 绘制无限制帧按钮
    if (mIsNoLimitedSelected)
    {
        setfillcolor(YELLOW);
        fillrectangle(290, 360, 350, 390);
    }
    rectangle(290, 360, 350, 390);
    TCHAR noLimitFrame[] = _T("无限");
    outtextxy(300, 365, noLimitFrame);

    rectangle(200, 300, 400, 350);
    TCHAR c[] = _T("画面质量");
    outtextxy(210, 310, c);

    rectangle(220, 460, /*380*/430, 490);
    TCHAR AIGUO[] = _T("文字，我只用中国的！");
    outtextxy(230, 465, AIGUO);

    rectangle(200, 400, 400, 450);
    TCHAR d[] = _T("语言");
    outtextxy(210, 410, d);

    // 添加确定和取消按钮
    // 其实这俩一样
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
    while (mConfig)
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
                    break;
                }

                // 如果用户点击了取消按钮
                if (msg.x >= 350 && msg.x <= 400 && msg.y >= 500 && msg.y <= 530)
                {
                    // 返回主菜单界面
                    mConfig = false;
                    drawMenu();
                    return;
                }

                // 如果用户点击了默认按钮
                if (msg.x >= 220 && msg.x <= 280 && msg.y >= 260 && msg.y <= 290)
                {
                    printf("默认\n");

                    // 设置风格为默认
                    Theme = 0;

                    // 更新选中状态
                    mIsDefaultSelected = true;
                    mIsOTTSelected = false;
                    mIsASoulSelected = false;

                    cleardevice();
                    drawSettings();
                }

                // 如果用户点击了 OTTO 按钮
                if (msg.x >= 290 && msg.x <= 350 && msg.y >= 260 && msg.y <= 290)
                {
                    printf("OTTO\n");

                    // 设置风格为 OTTO
                    Theme = 1;

                    // 更新选中状态
                    mIsDefaultSelected = false;
                    mIsOTTSelected = true;
                    mIsASoulSelected = false;

                    cleardevice();
                    drawSettings();
                }

                // 如果用户点击了 A-Soul 按钮
                if (msg.x >= 360 && msg.x <= 420 && msg.y >= 260 && msg.y <= 290)
                {
                    printf("A-Soul\n");

                    // 设置风格为 A-Soul
                    Theme = 2;

                    // 更新选中状态
                    mIsDefaultSelected = false;
                    mIsOTTSelected = false;
                    mIsASoulSelected = true;

                    cleardevice();
                    drawSettings();
                }

                // 如果用户点击了 6帧 按钮
                if (msg.x >= 220 && msg.x <= 280 && msg.y >= 360 && msg.y <= 390)
                {
                    printf("6帧\n");

                    // 设置帧率为 6 帧
                    FPS = 0;

                    // 更新选中状态
                    mIs6Selected = true;
                    mIsNoLimitedSelected = false;

                    cleardevice();
                    drawSettings();
                }

                // 如果用户点击了 无限制帧 按钮
                if (msg.x >= 290 && msg.x <= 350 && msg.y >= 360 && msg.y <= 390)
                {
                    printf("无限\n");

                    // 设置帧率为无限制
                    FPS = 1;

                    // 更新选中状态
                    mIs6Selected = false;
                    mIsNoLimitedSelected = true;

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