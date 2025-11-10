#define _CRT_SECURE_NO_WARNINGS
#include "GameEasyx.h"
#include "GlobalConfig.h"
#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <iostream>

GameEasyx::GameEasyx() {
    srand(time(NULL));

    if (Theme == 0)
    {
        PlaySound(TEXT("res\\DeaufltGame.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
    if (Theme == 1)
    {
        PlaySound(TEXT("res\\GameOtto.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
    if (Theme == 2)
    {
        PlaySound(TEXT("res\\A-soul.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }

    loadimage(&imgOTTO, _T("res\\otto.jpg"));
    loadimage(&imgAVA, _T("res\\DATOU.png"));

    // 初始化网格
    initNullGrid();
}

void GameEasyx::initNullGrid()
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            mGrid[i][j] = 0;
        }
    }
}

void GameEasyx::initRandomGrid()
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            if (rand() % 3 == 0)
            {
                mGrid[i][j] = 1;
            }
            else
            {
                mGrid[i][j] = 0;
            }
        }
    }
}

void GameEasyx::run()
{
flag1:
    while (handleInput() != 1)
    {
        drawGrid(Theme);
    }

    // 游戏主循环
    while (1)
    {
        // 减少 Sleep 的时间
        Sleep(1000 / 60); // 将帧率提高到 60 FPS

        // 重置 mHandleMenu
        if (mHandleRemenu == 1)
        {
            mHandleRemenu = 0;
            break;
        }

        // 更频繁地检查鼠标事件
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                // 如果用户点击了返回按钮
                if (msg.x >= 0 && msg.x <= 70 && msg.y >= 600 && msg.y <= 650)
                {
                    printf("返回按钮点下\n");
                    // 返回主菜单界面
                    break;
                }

                // 如果用户点击了重置按钮
                if (msg.x >= 140 && msg.x <= 210 && msg.y >= 600 && msg.y <= 650)
                {
                    printf("游戏循环重置\n");
                    initNullGrid(); // 或者 initRandomGrid()
                    for (int i = 0; i < COLS; i++)
                        for (int j = 0; j < ROWS; j++)
                            mUpdateGrid[i][j] = 0;
                    mGeneration = 0;
                    goto flag1;
                    // 返回主菜单界面
                }
            }
        }

        // 绘制网格
        drawGrid(Theme);

        // 更新网格
        updateGrid();

        // 更新代数
        if (isSame() == 0)
            mGeneration += 1;
        if (mGeneration >= 999)
            mGeneration = 0;

        // 根据 FPS 设置 Sleep 时间
        if (FPS == 0)
        {
            Sleep(1000 / 6);
        }
    }
}

void GameEasyx::drawGrid(int FillTheme)
{
    BeginBatchDraw();

    // 背景色为白色
    setbkcolor(WHITE);
    cleardevice();

    // 绘制网格
    setlinestyle(PS_SOLID, 1); // 设置线型为实线，线宽1个像素
    setlinecolor(BLACK);       // 设置线的颜色为黑色
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            rectangle(i * CELL_SIZE, j * CELL_SIZE, (i + 1) * CELL_SIZE, (j + 1) * CELL_SIZE);// 绘制矩形
            if (mGrid[i][j] == 1)
            {
                if (Theme == 0)
                {
                    setfillcolor(0x700B6E); // 南开紫
                    fillrectangle(i * CELL_SIZE, j * CELL_SIZE, (i + 1) * CELL_SIZE, (j + 1) * CELL_SIZE); // 填充矩形
                }
                if (Theme == 1)
                {
                    putimage(i * CELL_SIZE, j * CELL_SIZE, &imgOTTO);
                }
                if (Theme == 2)
                {
                    putimage(i * CELL_SIZE, j * CELL_SIZE, &imgAVA);
                }
            }
        }
    }

    setlinestyle(PS_SOLID, 1); // 设置线型为实线，线宽1个像素
    setlinecolor(BLACK);       // 设置线的颜色为黑色
    settextstyle(16, 0, 0);

    // 返回按钮
    rectangle(0, 600, 70, 650);
    TCHAR e[] = _T("返回");
    outtextxy(15, 620, e);

    // 开始按钮
    rectangle(70, 600, 140, 650);
    TCHAR f[] = _T("开始");
    outtextxy(85, 620, f);

    // 重置按钮
    rectangle(140, 600, 210, 650);
    TCHAR g[] = _T("重置");
    outtextxy(155, 620, g);

    // 随机按钮
    rectangle(210, 600, 280, 650);
    TCHAR h[] = _T("随机");
    outtextxy(225, 620, h);

    // 逐步按钮
    rectangle(280, 600, 350, 650);
    TCHAR cZHUBU[] = _T("逐步");
    outtextxy(295, 620, cZHUBU);

    // 代 
    rectangle(350, 600, 420, 650);
    char tempDAI[10] = "代: ";
    sprintf(tempDAI, "代: %d", mGeneration);

    WCHAR wcDAI[200];
    MultiByteToWideChar(CP_ACP, 0, tempDAI, -1, wcDAI, sizeof(wcDAI));

    TCHAR cDAI[20];
    _tcscpy_s(cDAI, wcDAI);

    outtextxy(365, 620, cDAI);

    // 立即刷新屏幕
    FlushBatchDraw();
}

// 更新每帧，使用updateGrid暂时存储更改，并在遍历完原矩阵后复制回Grid
void GameEasyx::updateGrid()
{
    memcpy(mGridCopy, mGrid, sizeof(mGrid)); // 使用memcpy函数代替两层for循环来拷贝mGrid数组

    int col, row;
    for (int i = 0; i < COLS; i++)
    {
        col = (i - 1 + COLS) % COLS;
        int next_col = (i + 1) % COLS;

        for (int j = 0; j < ROWS; j++)
        {
            row = (j - 1 + ROWS) % ROWS;
            int next_row = (j + 1) % ROWS;

            // 计算周围细胞数量
            int neighbours = mGrid[col][row] + mGrid[i][row] + mGrid[next_col][row] +
                mGrid[col][j] + mGrid[next_col][j] +
                mGrid[col][next_row] + mGrid[i][next_row] + mGrid[next_col][next_row];

            // 使用三目运算符简化代码
            mUpdateGrid[i][j] = mGrid[i][j] ? (neighbours < 2 || neighbours > 3 ? 0 : 1) : (neighbours == 3 ? 1 : 0);
        }
    }

    memcpy(mGrid, mUpdateGrid, sizeof(mGrid)); // 使用memcpy函数代替两层for循环来拷贝mUpdateGrid数组
}
bool GameEasyx::handleInput()
{
    // 检测鼠标事件
    if (MouseHit())
    {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN)
        {
            //开始判断
            if (msg.x >= 70 && msg.x <= 140 && msg.y >= 600 && msg.y <= 650)
            {
                printf("游戏循环开始\n");
                // 返回主菜单界面
                mStartGame = 1;
                return 1;
            }

            //随机填充
            if (msg.x >= 210 && msg.x <= 280 && msg.y >= 600 && msg.y <= 650)
            {
                printf("随机\n");
                initRandomGrid();
            }

            //逐步
            if (msg.x >= 280 && msg.x <= 350 && msg.y >= 600 && msg.y <= 650)
            {
                printf("逐步\n");

                if (Theme == 1)
                {
                    mciSendString(_T("play res\\Dududu.wav"), NULL, 0, NULL);
                }
                if (Theme == 2)
                {
                    mciSendString(_T("play res\\AVA.wav"), NULL, 0, NULL);
                }

                updateGrid();
                if(isSame() == 0)
                    mGeneration += 1;
            }

            // 如果用户点击了重置按钮
            if (msg.x >= 140 && msg.x <= 210 && msg.y >= 600 && msg.y <= 650)
            {
                printf("游戏循环重置\n");
                initNullGrid(); // 或者 initRandomGrid()
                for (int i = 0; i < COLS; i++)
                    for (int j = 0; j < ROWS; j++)
                        mUpdateGrid[i][j] = 0;
                mGeneration = 0;
            }

            //如果用户点击了返回按钮
            if (msg.x >= 0 && msg.x <= 70 && msg.y >= 600 && msg.y <= 650)
            {
                printf("游戏循环返回\n");
                mHandleRemenu = 1;
                return 1;
            }

            // 判断鼠标是否点击了游戏区域内的方格
            for (int i = 0; i < COLS; i++)
            {
                for (int j = 0; j < ROWS; j++)
                {
                    if (msg.x >= i * CELL_SIZE && msg.x <= (i + 1) * CELL_SIZE &&
                        msg.y >= j * CELL_SIZE && msg.y <= (j + 1) * CELL_SIZE)
                    {
                        if (Theme == 1)
                        {
                            mciSendString(_T("play res\\Dududu.wav"), NULL, 0, NULL);
                        }
                        if (Theme == 2)
                        {
                            mciSendString(_T("play res\\AVA.wav"), NULL, 0, NULL);
                        }
                        std::cout << "(" << i << "," << j << ")" << " = 1" << std::endl;
                        // 设置对应的mGrid[i][j]值为1
                        mGrid[i][j] = 1;
                    }
                }
            }
        }
        if (msg.uMsg == WM_RBUTTONDOWN)
        {
            // 判断鼠标是否点击了游戏区域内的方格
            for (int i = 0; i < COLS; i++)
            {
                for (int j = 0; j < ROWS; j++)
                {
                    if (msg.x >= i * CELL_SIZE && msg.x <= (i + 1) * CELL_SIZE &&
                        msg.y >= j * CELL_SIZE && msg.y <= (j + 1) * CELL_SIZE)
                    {
                        if (Theme == 1)
                        {
                            Sleep(100); // 解决音频重叠，待测试
                            mciSendString(_T("play res\\Dududu.wav"), NULL, 0, NULL);
                        }
                        if (Theme == 2)
                        {
                            Sleep(100);//解决音频重叠，待测试
                            mciSendString(_T("play res\\AVA.wav"), NULL, 0, NULL);
                        }
                        std::cout << "(" << i << "," << j << ")" << " = 0" << std::endl;
                        // 设置对应的mGrid[i][j]值为0
                        mGrid[i][j] = 0;
                    }
                }
            }
        }
    }
    return 0;
}

bool GameEasyx::isSame() const
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            if (mUpdateGrid[i][j] == mGridCopy[i][j])
                continue;
            else
            {
                return 0;// 不相等
            }
        }
    }
    return 1;
}
