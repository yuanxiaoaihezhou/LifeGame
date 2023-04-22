#include "GameEasyx.h"
#include "GlobalConfig.h"
#include <graphics.h>
#include <ctime>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


GameEasyx::GameEasyx() {
    srand(time(NULL));

    // 初始化网格
    initNullGrid();
    initRandomGrid();
}

void GameEasyx::initNullGrid()
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
    //开启了控制台
    //initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, EX_SHOWCONSOLE);

    // 测试帧数控制
    //DWORD lastFrameTime = timeGetTime(); // 上一帧开始时间

    // 测试帧数控制
    //DWORD lastFrameTime = timeGetTime(); // 上一帧开始时间

    //游戏主循环
    while (true)// 未来加入返回按钮
    {
        // 计算时间差，以便限制帧率
        //DWORD currentTime = timeGetTime();
        //DWORD deltaTime = currentTime - lastFrameTime;
        //lastFrameTime = currentTime;

        drawGrid();
        updateGrid();

        // 计算需要休眠的时间，以保证每秒钟 60 帧
        //DWORD sleepTime
        Sleep(1000/6);
    }

    //closegraph();
}

void GameEasyx::drawGrid()
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
                setfillcolor(0x700B6E); // 南开紫
                fillrectangle(i * CELL_SIZE,  j * CELL_SIZE, (i + 1) * CELL_SIZE, (j + 1) * CELL_SIZE); // 填充矩形
            }
        }
    }
    // 等待绘图完毕刷新，以免屏幕闪烁
    BeginBatchDraw();
    FlushBatchDraw();
}

// 更新每帧，使用updateGrid暂时存储更改，并在遍历完原矩阵后复制回Grid
void GameEasyx::updateGrid()
{
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