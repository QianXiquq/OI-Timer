#include <iostream>
#include <graphics.h>
#include <easyx.h>
#include "resource.h"
#include <cstring>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <sys/stat.h>
#pragma warning(disable : 4996)

// #include "_InputBox.h"
// #define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
wchar_t User[40];
wchar_t Welc[13] = {'W', 'e', 'l', 'c', 'o', 'm', 'e', ' ', 'b', 'a', 'c', 'k', ','};
char chour[3];
char cmin[3];
char csec[3];
wchar_t hour[3];
wchar_t minn[3];
wchar_t sec[3];
int IAccuTime;
char CAccuTime[300];

wchar_t AccuTime[300];

long long AcSec = 0;

double AccuHour = 0.0;

long long SingleSec = 0.0;

double SingleHour = 0.0;

char CSingleHour[300];

wchar_t WSingleHour[300];

bool isFileExists_stat(string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void CZero(char text[])
{
    memset(text, 0, sizeof(text));
}

void WZero(wchar_t text[])
{
    memset(text, 0, sizeof(text));
}

void CW(wchar_t tar[], char fro[], int l)
{ // 目标，来源，长度
    int j = l - 1;
    for (int i = 0; i <= j; i++)
        tar[i] = fro[i];
}

void ftoa(char text[], double from)
{ // 目标char数组，来源double数字
    sprintf(text, "%.2lf", from);
}

void Say(wchar_t text[], int x, int y)
{
    setbkmode(TRANSPARENT);
    settextcolor(LIGHTGRAY);
    LOGFONT f;
    gettextstyle(&f); // 获取当前字体设置
    f.lfHeight = 25;  // 设置字体高度为 25
    _tcscpy_s(f.lfFaceName, _T("Consolas"));
    f.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&f);
    outtextxy(x, y, text);
}

void SayTime(wchar_t text[], int x, int y)
{
    setbkmode(TRANSPARENT);
    settextcolor(LIGHTGRAY);
    LOGFONT f;
    gettextstyle(&f); // 获取当前字体设置
    f.lfHeight = 30;  // 设置字体高度为 30
    _tcscpy_s(f.lfFaceName, _T("Consolas"));
    f.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&f);
    outtextxy(x, y, text);
}

void SaySingleTime(wchar_t text[], int x, int y)
{
    setbkmode(TRANSPARENT);
    settextcolor(LIGHTGRAY);
    LOGFONT f;
    gettextstyle(&f); // 获取当前字体设置
    f.lfHeight = 50;  // 设置字体高度为 50
    _tcscpy_s(f.lfFaceName, _T("Consolas"));
    f.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&f);
    outtextxy(x, y, text);
}

void GetName()
{

    // ExMessage m;
    // m = getmessage(EX_KEY);
    // TCHAR show[] = _T("qweqwe");
    // outtextxy(10, 10, show);

    InputBox(User, 35, L"Please input your name:", L"Log in", NULL, 230, 0, TRUE);
    for (int i = 0; i <= 39; i++)
    {
        if (User[i])
            continue;
        else
        {
            User[i] = '.';
            break;
        }
    }

    // outtextxy(10, 10, User);
    // Widget widget(800, 600);
    // widget.init();
    // widget.run();
    // widget.close();
}

void SayName()
{
    Say(Welc, 20, 15);
    Say(User, 20, 35);
    outtextxy(356, 12, L"qwq");
}

void Getnowtime()
{
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    // 输出结构中的内容

    int ihour = ltm->tm_hour;
    int imin = ltm->tm_min;
    int isec = ltm->tm_sec;

    // 转换为char
    if (ihour <= 9)
    {
        chour[0] = '0';
        chour[1] = char(ihour + '0');
    }
    else
        itoa(ihour, chour, 10);
    if (imin <= 9)
    {
        cmin[0] = '0';
        cmin[1] = char(imin + '0');
    }
    else
        itoa(imin, cmin, 10);
    if (isec <= 9)
    {
        csec[0] = '0';
        csec[1] = char(isec + '0');
    }
    else
        itoa(isec, csec, 10);

    // 转换为wchar_t

    CW(hour, chour, 2);
    CW(minn, cmin, 2);
    CW(sec, csec, 2);

    // 显示

    SayTime(hour, 273, 250);
    SayTime(minn, 315, 250);
    SayTime(sec, 359, 250);
    outtextxy(300, 250, ':');
    outtextxy(344, 250, ':');
}

void Paint()
{
    IMAGE img;
    loadimage(&img, L"PNG", MAKEINTRESOURCE(IDB_PNG2));
    //    RECT r = { 0, 0, 639, 479 };

    // loadimage(&img, L"./res/bkimg.png");
    putimage(0, 0, &img);
}

void RecordTime()
{
    string s = "time.dll";
    //if (!isFileExists_stat(s))
    //{
        //system("type nul>time.dll");
    //}
    freopen("time.dll", "r", stdin);
    cin >> IAccuTime;
    fclose(stdin);

    system("rm time.dll");
    freopen("time.dll", "w", stdout);

    IAccuTime += AcSec;
    // AcSec的清零会在SingleRecord()中被执行，不能重复执行
    cout << IAccuTime;
    AccuHour = (double)IAccuTime / 3600.0;
    ftoa(CAccuTime, AccuHour);
    CW(AccuTime, CAccuTime, 300);
    SayTime(AccuTime, 20, 250);

    setbkmode(TRANSPARENT);
    settextcolor(LIGHTGRAY);
    LOGFONT f;
    gettextstyle(&f); // 获取当前字体设置
    f.lfHeight = 20;  // 设置字体高度为 20
    _tcscpy_s(f.lfFaceName, _T("Consolas"));
    f.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&f);
    outtextxy(20, 235, L"Total Time:");
    outtextxy(98, 257, L"hr(s)");
}

void SingleRecord()
{
    SingleSec += AcSec;
    AcSec = 0;
    SingleHour = (double)SingleSec / 3600.0;
    ftoa(CSingleHour, SingleHour);
    CW(WSingleHour, CSingleHour, 300);
    SaySingleTime(WSingleHour, 158, 170);
    setbkmode(TRANSPARENT);
    settextcolor(LIGHTGRAY);
    LOGFONT f;
    gettextstyle(&f); // 获取当前字体设置
    f.lfHeight = 20;  // 设置字体高度为 20
    _tcscpy_s(f.lfFaceName, _T("Consolas"));
    f.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&f);
    outtextxy(129, 212, L"Single Time (hrs)");
}

DWORD GetCurrentActiveWindowsProcessId()
{
    HWND hWnd = GetActiveWindow();
    DWORD processId = 0;
    GetWindowThreadProcessId(hWnd, &processId);
    return processId;
}

BOOL HasFocus()
{
    DWORD active_process = GetCurrentActiveWindowsProcessId();
    DWORD current_process = ::GetCurrentProcessId();
    return current_process == active_process;
}
int main()
{
    //initgraph(400, 300);
    //SetWindowText(GetHWnd(), L"ANNOUNCEMENT");
    //LOGFONT f;
    //gettextstyle(&f); // 获取当前字体设置
    //f.lfHeight = 35;  // 设置字体高度为 25
    //_tcscpy_s(f.lfFaceName, _T("Consolas"));
    //f.lfQuality = ANTIALIASED_QUALITY;
    //settextstyle(&f);
    //outtextxy(100, 50, L"ANNOUNCEMENT");
    //f.lfHeight = 20;
    //_tcscpy_s(f.lfFaceName, _T("微软雅黑"));
    //settextstyle(&f);
    //outtextxy(8, 130, L"本程序将在exe文件的同级目录新建\"time.dll\"文件以记录时间。");
    //outtextxy(107, 170, L"Made By QianXiquq.");
    //Sleep(5000);
    //closegraph();

    initgraph(400, 300);
    // 获得窗口句柄
    HWND hWnd = GetHWnd();
    // 使用 Windows API 修改窗口名称
    SetWindowText(hWnd, L"OI上机计时器");

    Paint();
    // cleardevice();
    GetName();
    Getnowtime();

    for (;;)
    {
        Paint();
        RecordTime();
        SingleRecord();
        SayName();
        Getnowtime();
        AcSec++;
        Sleep(1000);
    }

    closegraph();
    return 0;
}
