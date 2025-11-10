#pragma once
/*
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
*/

