#include "MenuEasyx.h"
#include "GameEasyx.h"
#include "GlobalConfig.h"
#include "utils.h"
#include <graphics.h>
#include <cstdio>
#include <new>

MenuEasyx::MenuEasyx()
{
    //initgraph(WINDOW_WIDTH, WINDOW_HEIGHT + 50, EX_SHOWCONSOLE); // debug
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT + 50); // release
	drawMenu();
    PlaySound(TEXT("res\\OpeingTheme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);  // ��������
}

void MenuEasyx::drawMenu()
{
    printf("�������˵�");
    setbkcolor(WHITE);
    cleardevice();

    // ���Ʋ˵�
    setlinestyle(PS_SOLID, 1); // ��������Ϊʵ�ߣ��߿�1������
    setlinecolor(BLACK);       // �����ߵ���ɫΪ��ɫ

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

    // ˢ����Ļ
    BeginBatchDraw();
    FlushBatchDraw();
}

void MenuEasyx::run() 
{
    printf("����������\n");
    FlushMouseMsgBuffer();

    while (!mStartGame && !mSettings && !mDevelopInfo && !mQuitGame)
    {
        // �������¼�
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                // ����û�����˿�ʼ��Ϸ��ť
                if (msg.x >= 200 && msg.x <= 400 && msg.y >= 200 && msg.y <= 250)
                {
                    mStartGame = true;
                    PlaySound(NULL, NULL, 0);  // ֹͣ���ֲ���
                    GameEasyx* game = new (std::nothrow) GameEasyx;
                    if (game != nullptr)
                    {
                        game->run();
                        delete game;
                    }
                    drawMenu();
                    PlaySound(TEXT("res\\OpeingTheme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);  // ��������
                    mStartGame = false;
                }

                if (msg.x >= 200 && msg.x <= 400 && msg.y >= 300 && msg.y <= 350)
                {
                    mSettings = true;
                    cleardevice();
                    printf("��������ҳ��\n"); // ���ӵ������
                    drawSettings();
                }

                // ����û�����˿�������Ϣ��ť
                if (msg.x >= 200 && msg.x <= 400 && msg.y >= 400 && msg.y <= 450)
                {
                    mDevelopInfo = true;
                    cleardevice();
                    printf("���뿪������Ϣҳ��\n"); // ���ӵ������
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
    // �������¼�����
    FlushMouseMsgBuffer();

    setbkcolor(WHITE);
    cleardevice();

    // ��������ҳ��

    settextstyle(40, 0, 0);
    settextcolor(BLACK);
    TCHAR a[] = _T("����");
    outtextxy(200, 100, a);

    // ����Ĭ�ϰ�ť
    settextstyle(16, 0, 0);
    if (mIsDefaultSelected) 
    {
        setfillcolor(YELLOW); // ���Ĭ�ϰ�ť��ѡ�У�����ɫ
        fillrectangle(220, 260, 280, 290);
    }
    else
    {
        setfillcolor(WHITE); // ��������ɫ
        fillrectangle(220, 260, 280, 290);
    }
    rectangle(220, 260, 280, 290);
    TCHAR defaultTheme[] = _T("Ĭ��");
    outtextxy(230, 265, defaultTheme);

    // ����OTTO��ť
    if (mIsOTTSelected) 
    {
        setfillcolor(YELLOW); // ��� OTTO ��ť��ѡ�У�����ɫ
        fillrectangle(290, 260, 350, 290);
    }
    else 
    {
        setfillcolor(WHITE); // ��������ɫ
        fillrectangle(290, 260, 350, 290);
    }
    rectangle(290, 260, 350, 290);
    TCHAR OTTO[] = _T("OTTO");
    outtextxy(300, 265, OTTO);


    // ����A-Soul��ť
    if (mIsASoulSelected) 
    {
        setfillcolor(YELLOW); // ��� A-Soul ��ť��ѡ�У�����ɫ
        fillrectangle(360, 260, 420, 290);
    }
    else 
    {
        setfillcolor(WHITE); // ��������ɫ
        fillrectangle(360, 260, 420, 290);
    }
    rectangle(360, 260, 420, 290);
    TCHAR AS[] = _T("A-Soul");
    outtextxy(370, 265, AS);

    settextstyle(20, 0, 0);
    rectangle(200, 200, 400, 250);
    TCHAR b[] = _T("���");
    outtextxy(210, 210, b);

    // ����6֡��ť
    if (mIs6Selected)
    {
        setfillcolor(YELLOW);
        fillrectangle(220, 360, 280, 390);
    }
    rectangle(220, 360, 280, 390);
    TCHAR sixFrames[] = _T("6֡");
    outtextxy(230, 365, sixFrames);

    // ����������֡��ť
    if (mIsNoLimitedSelected)
    {
        setfillcolor(YELLOW);
        fillrectangle(290, 360, 350, 390);
    }
    rectangle(290, 360, 350, 390);
    TCHAR noLimitFrame[] = _T("����");
    outtextxy(300, 365, noLimitFrame);

    rectangle(200, 300, 400, 350);
    TCHAR c[] = _T("��������");
    outtextxy(210, 310, c);

    rectangle(220, 460, /*380*/430, 490);
    TCHAR AIGUO[] = _T("���֣���ֻ���й��ģ�");
    outtextxy(230, 465, AIGUO);

    if (mAiGuo)
    {
        IMAGE AIGUO;
        loadimage(&AIGUO, _T("res\\HANJIAN.png"));
        //loadimage(&AIGUO, _T("res\\testForMemory.jpeg")); // ������
        putimage(440, 400, &AIGUO);
    }

    rectangle(200, 400, 400, 450);
    TCHAR d[] = _T("����");
    outtextxy(210, 410, d);

    // ����ȷ����ȡ����ť
    // ��ʵ����һ��
    settextstyle(16, 0, 0);
    rectangle(200, 500, 250, 530);
    TCHAR e[] = _T("ȷ��");
    outtextxy(210, 505, e);

    rectangle(350, 500, 400, 530);
    TCHAR f[] = _T("ȡ��");
    outtextxy(360, 505, f);

    // ˢ����Ļ
    BeginBatchDraw();
    FlushBatchDraw();

    // �ȴ��û�����
    while (mSettings)
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                // ����û������ȷ����ť
                if (msg.x >= 200 && msg.x <= 250 && msg.y >= 500 && msg.y <= 530)
                {
                    // �������˵�����
                    mSettings = false;
                    mAiGuo = false;
                    drawMenu();
                    break;
                }

                // ����û������ȡ����ť
                if (msg.x >= 350 && msg.x <= 400 && msg.y >= 500 && msg.y <= 530)
                {
                    // �������˵�����
                    mAiGuo = false;
                    mSettings = false;
                    drawMenu();
                    return;
                }

                // ����û������Ĭ�ϰ�ť
                if (msg.x >= 220 && msg.x <= 280 && msg.y >= 260 && msg.y <= 290)
                {
                    printf("Ĭ��\n");

                    // ���÷��ΪĬ��
                    Theme = 0;

                    // ����ѡ��״̬
                    mIsDefaultSelected = true;
                    mIsOTTSelected = false;
                    mIsASoulSelected = false;

                    cleardevice();
                    drawSettings();
                }

                // ����û������ OTTO ��ť
                if (msg.x >= 290 && msg.x <= 350 && msg.y >= 260 && msg.y <= 290)
                {
                    printf("OTTO\n");

                    // ���÷��Ϊ OTTO
                    Theme = 1;

                    // ����ѡ��״̬
                    mIsDefaultSelected = false;
                    mIsOTTSelected = true;
                    mIsASoulSelected = false;

                    cleardevice();
                    drawSettings();
                }

                // ����û������ A-Soul ��ť
                if (msg.x >= 360 && msg.x <= 420 && msg.y >= 260 && msg.y <= 290)
                {
                    printf("A-Soul\n");

                    // ���÷��Ϊ A-Soul
                    Theme = 2;

                    // ����ѡ��״̬
                    mIsDefaultSelected = false;
                    mIsOTTSelected = false;
                    mIsASoulSelected = true;

                    cleardevice();
                    drawSettings();
                }

                // ����û������ 6֡ ��ť
                if (msg.x >= 220 && msg.x <= 280 && msg.y >= 360 && msg.y <= 390)
                {
                    printf("6֡\n");

                    // ����֡��Ϊ 6 ֡
                    FPS = 0;

                    // ����ѡ��״̬
                    mIs6Selected = true;
                    mIsNoLimitedSelected = false;

                    cleardevice();
                    drawSettings();
                }

                // ����û������ ������֡ ��ť
                if (msg.x >= 290 && msg.x <= 350 && msg.y >= 360 && msg.y <= 390)
                {
                    printf("����\n");

                    // ����֡��Ϊ������
                    FPS = 1;

                    // ����ѡ��״̬
                    mIs6Selected = false;
                    mIsNoLimitedSelected = true;

                    cleardevice();
                    drawSettings();
                }

                // ����û������ ���� ��ť
                if (msg.x >= 220 && msg.x <= 430 && msg.y >= 460 && msg.y <= 490)
                {
                    //rectangle(220, 460, /*380*/430, 490);
                    printf("����\n");

                    // ����ѡ��״̬
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

    // ���ƿ�������Ϣҳ��
    settextstyle(40, 0, 0);
    settextcolor(BLACK);
    TCHAR a[] = _T("��������Ϣ");
    outtextxy(150, 100, a);

    settextstyle(20, 0, 0);
    TCHAR b[] = _T("�����ߣ�nad_iz");
    outtextxy(220, 200, b);

    TCHAR c[] = _T("�������ڣ�2023��5��");
    outtextxy(220, 250, c);

    TCHAR d[] = _T("��ϵ��ʽ��2211133@mail.nankai.edu.cn");
    outtextxy(220, 300, d);

    // ���ӷ��ذ�ť
    settextstyle(16, 0, 0);
    rectangle(200, 500, 400, 530);
    TCHAR e[] = _T("����");
    outtextxy(280, 505, e);

    // ˢ����Ļ
    BeginBatchDraw();
    FlushBatchDraw();

    // �ȴ��û�����
    while (1)
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                // ����û�����˷��ذ�ť
                if (msg.x >= 200 && msg.x <= 400 && msg.y >= 500 && msg.y <= 530)
                {
                    // �������˵�����
                    mDevelopInfo = false;
                    drawMenu();
                    return;
                }
            }
        }
    }
}