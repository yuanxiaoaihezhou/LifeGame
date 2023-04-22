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

    //游戏主循环
    while (true)
    {
        //重置mHandleMenu
        if (mHandleRemenu == 1)
        {
            mHandleRemenu = 0;
            break;
        }

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
        drawGrid(Theme);
        updateGrid();
        if (isSame() == 0)
            mGeneration += 1;
        if (mGeneration >= 999)
            mGeneration = 0;

        if (FPS == 0)
        {
            Sleep(1000 / 6);
        }
    }
}

void GameEasyx::drawGrid(int FillTheme)
{
    // 背景色为白色
    setbkcolor(WHITE);
    cleardevice();

    // 绘制网格
    setlinestyle(PS_SOLID, 1); // 设置线型为实线，线宽1个像素
    setlinecolor(BLACK);       // 设置线的颜色为黑色
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            rectangle(i * CELL_SIZE,  j * CELL_SIZE, (i + 1) * CELL_SIZE, (j + 1) * CELL_SIZE);// 绘制矩形
            if (mGrid[i][j] == 1) 
            {
                if (Theme == 0)
                {
                    setfillcolor(0x700B6E); // 南开紫
                    fillrectangle(i * CELL_SIZE, j * CELL_SIZE, (i + 1) * CELL_SIZE, (j + 1) * CELL_SIZE); // 填充矩形
                }
                if (Theme == 1)
                {
                    // IMAGE imgForMemoryTest; // 测试用
                    //loadimage(&imgForMemoryTest, _T("res\\testForMemory.jpeg")); // 测试用

                    IMAGE img; // 声明一个IMAGE对象用于加载图像
                    loadimage(&img, _T("res\\otto.jpg"));
                    putimage(i * CELL_SIZE, j * CELL_SIZE, &img);
                }
                if (Theme == 2)
                {
                    IMAGE img; // 声明一个IMAGE对象用于加载图像
                    loadimage(&img, _T("res\\DATOU.png")); // 加载一张名为test.jpg的图片
                    putimage(i * CELL_SIZE, j * CELL_SIZE, &img);
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
    // 在这里可能会出现bug，标记一下
    rectangle(350, 600, 420, 650);
    char tempDAI[10] = "代: ";
    sprintf(tempDAI, "代: %d", mGeneration);

    WCHAR wcDAI[20];
    MultiByteToWideChar(CP_ACP, 0, tempDAI, -1, wcDAI, sizeof(wcDAI));

    TCHAR cDAI[20];
    _tcscpy_s(cDAI, wcDAI);

    outtextxy(365, 620, cDAI);

    // 等待绘图完毕刷新，以免屏幕闪烁
    BeginBatchDraw();
    FlushBatchDraw();
}

// 更新每帧，使用updateGrid暂时存储更改，并在遍历完原矩阵后复制回Grid
void GameEasyx::updateGrid()
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            mGridCopy[i][j] = mGrid[i][j];
        }
    }
    // 规则
    // 1.如果一个活着的细胞周围（上下左右和四个对角线）有2个或3个活着的细胞，那么它在下一个时刻仍然是活着的；
    // 2.如果一个活着的细胞周围的活着的细胞少于2个，或者超过3个，那么它在下一个时刻会死亡；
    // 3.如果一个死亡的细胞周围恰好有3个活着的细胞，那么它在下一个时刻会复活成为一个活着的细胞。

    // 进行状态判断
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            int neighbours = 0;

            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    // 避开本身的格子
                    if (x == 0 && y == 0)
                    {
                        continue;
                    }

                    // 处理边界
                    int col = (i + x + COLS) % COLS;
                    int row = (j + y + ROWS) % ROWS;

                    neighbours += mGrid[col][row];
                }
            }

            if (mGrid[i][j] == 1) // 存活
            {
                if (neighbours < 2 || neighbours > 3)
                {
                    mUpdateGrid[i][j] = 0;
                }
                else
                {
                    mUpdateGrid[i][j] = 1;
                }
            }
            else
            {
                if (neighbours == 3)
                {
                    mUpdateGrid[i][j] = 1;
                }
                else
                {
                    mUpdateGrid[i][j] = 0;
                }
            }
        }
    }

    //拷贝mUpdateGrid
    for (int i = 0; i < COLS; i++)
        for (int j = 0; j < ROWS; j++)
            mGrid[i][j] = mUpdateGrid[i][j];
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

bool GameEasyx::isSame()
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
