#define _CRT_SECURE_NO_WARNINGS
#include "GameEasyx.h"
#include "GlobalConfig.h"
#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <iostream>

GameEasyx::GameEasyx() {
    srand(time(nullptr));

    if (Theme == 0)
    {
        PlaySound(TEXT("res\\DeaufltGame.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
    else if (Theme == 1)
    {
        PlaySound(TEXT("res\\GameOtto.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
    else if (Theme == 2)
    {
        PlaySound(TEXT("res\\A-soul.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }

    loadimage(&imgOTTO, _T("res\\otto.jpg"));
    loadimage(&imgAVA, _T("res\\DATOU.png"));

    // ��ʼ������
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
    bool restartGame = true;
    
    while (restartGame)
    {
        restartGame = false;
        
        while (handleInput() != 1)
        {
            drawGrid(Theme);
        }

        // ��Ϸ��ѭ��
        while (1)
        {
            // ���� Sleep ��ʱ��
            Sleep(1000 / 60); // ��֡����ߵ� 60 FPS

            // ���� mHandleMenu
            if (mHandleRemenu == 1)
            {
                mHandleRemenu = 0;
                break;
            }

            // ��Ƶ���ؼ������¼�
            if (MouseHit())
            {
                MOUSEMSG msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    // ����û�����˷��ذ�ť
                    if (msg.x >= BUTTON_RETURN_X1 && msg.x <= BUTTON_RETURN_X2 && msg.y >= BUTTON_Y && msg.y <= BUTTON_Y + BUTTON_HEIGHT)
                    {
                        printf("���ذ�ť����\n");
                        // �������˵�����
                        break;
                    }

                    // ����û���������ð�ť
                    if (msg.x >= BUTTON_RESET_X1 && msg.x <= BUTTON_RESET_X2 && msg.y >= BUTTON_Y && msg.y <= BUTTON_Y + BUTTON_HEIGHT)
                    {
                        printf("��Ϸѭ������\n");
                        initNullGrid(); // ���� initRandomGrid()
                        for (int i = 0; i < COLS; i++)
                            for (int j = 0; j < ROWS; j++)
                                mUpdateGrid[i][j] = 0;
                        mGeneration = 0;
                        restartGame = true;
                        break;
                    }
                }
            }

            // ��������
            drawGrid(Theme);

            // ��������
            updateGrid();

            // ���´���
            if (isSame() == 0)
                mGeneration += 1;
            if (mGeneration >= 999)
                mGeneration = 0;

            // ���� FPS ���� Sleep ʱ��
            if (FPS == 0)
            {
                Sleep(1000 / 6);
            }
        }
    }
}

void GameEasyx::drawGrid(int FillTheme)
{
    BeginBatchDraw();

    // ����ɫΪ��ɫ
    setbkcolor(WHITE);
    cleardevice();

    // ��������
    setlinestyle(PS_SOLID, 1); // ��������Ϊʵ�ߣ��߿�1������
    setlinecolor(BLACK);       // �����ߵ���ɫΪ��ɫ
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            rectangle(i * CELL_SIZE, j * CELL_SIZE, (i + 1) * CELL_SIZE, (j + 1) * CELL_SIZE);// ���ƾ���
            if (mGrid[i][j] == 1)
            {
                if (Theme == 0)
                {
                    setfillcolor(0x700B6E); // �Ͽ���
                    fillrectangle(i * CELL_SIZE, j * CELL_SIZE, (i + 1) * CELL_SIZE, (j + 1) * CELL_SIZE); // ������
                }
                else if (Theme == 1)
                {
                    putimage(i * CELL_SIZE, j * CELL_SIZE, &imgOTTO);
                }
                else if (Theme == 2)
                {
                    putimage(i * CELL_SIZE, j * CELL_SIZE, &imgAVA);
                }
            }
        }
    }

    setlinestyle(PS_SOLID, 1); // ��������Ϊʵ�ߣ��߿�1������
    setlinecolor(BLACK);       // �����ߵ���ɫΪ��ɫ
    settextstyle(16, 0, 0);

    // ���ذ�ť
    rectangle(BUTTON_RETURN_X1, BUTTON_Y, BUTTON_RETURN_X2, BUTTON_Y + BUTTON_HEIGHT);
    TCHAR e[] = _T("����");
    outtextxy(15, 620, e);

    // ��ʼ��ť
    rectangle(BUTTON_START_X1, BUTTON_Y, BUTTON_START_X2, BUTTON_Y + BUTTON_HEIGHT);
    TCHAR f[] = _T("��ʼ");
    outtextxy(85, 620, f);

    // ���ð�ť
    rectangle(BUTTON_RESET_X1, BUTTON_Y, BUTTON_RESET_X2, BUTTON_Y + BUTTON_HEIGHT);
    TCHAR g[] = _T("����");
    outtextxy(155, 620, g);

    // �����ť
    rectangle(BUTTON_RANDOM_X1, BUTTON_Y, BUTTON_RANDOM_X2, BUTTON_Y + BUTTON_HEIGHT);
    TCHAR h[] = _T("���");
    outtextxy(225, 620, h);

    // �𲽰�ť
    rectangle(BUTTON_STEP_X1, BUTTON_Y, BUTTON_STEP_X2, BUTTON_Y + BUTTON_HEIGHT);
    TCHAR cZHUBU[] = _T("��");
    outtextxy(295, 620, cZHUBU);

    // �� 
    rectangle(BUTTON_GEN_X1, BUTTON_Y, BUTTON_GEN_X2, BUTTON_Y + BUTTON_HEIGHT);
    char tempDAI[10] = "��: ";
    sprintf(tempDAI, "��: %d", mGeneration);

    WCHAR wcDAI[200];
    MultiByteToWideChar(CP_ACP, 0, tempDAI, -1, wcDAI, sizeof(wcDAI));

    TCHAR cDAI[20];
    _tcscpy_s(cDAI, wcDAI);

    outtextxy(365, 620, cDAI);

    // ����ˢ����Ļ
    FlushBatchDraw();
}

// ����ÿ֡��ʹ��updateGrid��ʱ�洢���ģ����ڱ�����ԭ������ƻ�Grid
void GameEasyx::updateGrid()
{
    memcpy(mGridCopy, mGrid, sizeof(mGrid)); // ʹ��memcpy������������forѭ��������mGrid����

    for (int i = 0; i < COLS; i++)
    {
        int col = (i - 1 + COLS) % COLS;
        int next_col = (i + 1) % COLS;

        for (int j = 0; j < ROWS; j++)
        {
            int row = (j - 1 + ROWS) % ROWS;
            int next_row = (j + 1) % ROWS;

            // ������Χϸ������
            int neighbours = mGrid[col][row] + mGrid[i][row] + mGrid[next_col][row] +
                mGrid[col][j] + mGrid[next_col][j] +
                mGrid[col][next_row] + mGrid[i][next_row] + mGrid[next_col][next_row];

            // ʹ����Ŀ������򻯴���
            mUpdateGrid[i][j] = mGrid[i][j] ? (neighbours < 2 || neighbours > 3 ? 0 : 1) : (neighbours == 3 ? 1 : 0);
        }
    }

    memcpy(mGrid, mUpdateGrid, sizeof(mGrid)); // ʹ��memcpy������������forѭ��������mUpdateGrid����
}
bool GameEasyx::handleInput()
{
    // �������¼�
    if (MouseHit())
    {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN)
        {
            //��ʼ�ж�
            if (msg.x >= BUTTON_START_X1 && msg.x <= BUTTON_START_X2 && msg.y >= BUTTON_Y && msg.y <= BUTTON_Y + BUTTON_HEIGHT)
            {
                printf("��Ϸѭ����ʼ\n");
                // �������˵�����
                mStartGame = 1;
                return 1;
            }

            //������
            if (msg.x >= BUTTON_RANDOM_X1 && msg.x <= BUTTON_RANDOM_X2 && msg.y >= BUTTON_Y && msg.y <= BUTTON_Y + BUTTON_HEIGHT)
            {
                printf("���\n");
                initRandomGrid();
            }

            //��
            if (msg.x >= BUTTON_STEP_X1 && msg.x <= BUTTON_STEP_X2 && msg.y >= BUTTON_Y && msg.y <= BUTTON_Y + BUTTON_HEIGHT)
            {
                printf("��\n");

                if (Theme == 1)
                {
                    mciSendString(_T("play res\\Dududu.wav"), NULL, 0, NULL);
                }
                else if (Theme == 2)
                {
                    mciSendString(_T("play res\\AVA.wav"), NULL, 0, NULL);
                }

                updateGrid();
                if(isSame() == 0)
                    mGeneration += 1;
            }

            // ����û���������ð�ť
            if (msg.x >= BUTTON_RESET_X1 && msg.x <= BUTTON_RESET_X2 && msg.y >= BUTTON_Y && msg.y <= BUTTON_Y + BUTTON_HEIGHT)
            {
                printf("��Ϸѭ������\n");
                initNullGrid(); // ���� initRandomGrid()
                for (int i = 0; i < COLS; i++)
                    for (int j = 0; j < ROWS; j++)
                        mUpdateGrid[i][j] = 0;
                mGeneration = 0;
            }

            //����û�����˷��ذ�ť
            if (msg.x >= BUTTON_RETURN_X1 && msg.x <= BUTTON_RETURN_X2 && msg.y >= BUTTON_Y && msg.y <= BUTTON_Y + BUTTON_HEIGHT)
            {
                printf("��Ϸѭ������\n");
                mHandleRemenu = 1;
                return 1;
            }

            // �ж�����Ƿ�������Ϸ�����ڵķ���
            int i = msg.x / CELL_SIZE;
            int j = msg.y / CELL_SIZE;
            if (i >= 0 && i < COLS && j >= 0 && j < ROWS)
            {
                if (Theme == 1)
                {
                    mciSendString(_T("play res\\Dududu.wav"), NULL, 0, NULL);
                }
                else if (Theme == 2)
                {
                    mciSendString(_T("play res\\AVA.wav"), NULL, 0, NULL);
                }
                std::cout << "(" << i << "," << j << ")" << " = 1" << std::endl;
                // ���ö�Ӧ��mGrid[i][j]ֵΪ1
                mGrid[i][j] = 1;
            }
        }
        if (msg.uMsg == WM_RBUTTONDOWN)
        {
            // �ж�����Ƿ�������Ϸ�����ڵķ���
            int i = msg.x / CELL_SIZE;
            int j = msg.y / CELL_SIZE;
            if (i >= 0 && i < COLS && j >= 0 && j < ROWS)
            {
                if (Theme == 1)
                {
                    mciSendString(_T("play res\\Dududu.wav"), NULL, 0, NULL);
                }
                else if (Theme == 2)
                {
                    mciSendString(_T("play res\\AVA.wav"), NULL, 0, NULL);
                }
                std::cout << "(" << i << "," << j << ")" << " = 0" << std::endl;
                // ���ö�Ӧ��mGrid[i][j]ֵΪ0
                mGrid[i][j] = 0;
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
            if (mUpdateGrid[i][j] != mGridCopy[i][j])
            {
                return 0;// �����
            }
        }
    }
    return 1;
}
