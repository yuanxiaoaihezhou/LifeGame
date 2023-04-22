#include "GameEasyx.h"
#include "GlobalConfig.h"
#include <graphics.h>
#include <ctime>


GameEasyx::GameEasyx() {
    srand(time(NULL));

    // ³õÊ¼»¯Íø¸ñ
    initGrid();
}

void GameEasyx::initGrid()
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            if (rand() % 114514 == 0)
            {
                mGrid[i][j] == 1;
            }
        }
    }

}