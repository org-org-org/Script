#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <time.h>
#include <dirent.h>
#define INF 0x3f3f3f3f
using namespace std;
const int N = 1 << 16;
const int MOUSE_SPEED = 64;
const int SLEEP_DURATION = 10;
const string LOAD_DIR = "./input/";
int inputTime[N] = {0}, inputKey[N] = {0}, inputType[N] = {0};
int inputNum = 0;
time_t start = 0, curTime = 0;
string fileName;
BYTE beginKey = VK_F8, endKey = VK_F9, pauseKey = VK_F7;
vector<BYTE>vKeys;
INT8 hit[256] = {0};
bool pre[256] = {0};
bool pressing(BYTE vKey) {
    return GetAsyncKeyState(vKey) >> 15;
}
time_t Now() { // 获取当前时间戳，毫秒级
    time_t second;
    time(&second);
    SYSTEMTIME ms;
    GetSystemTime(&ms);
    return second * 1000 + ms.wMilliseconds;
}
void loadAllKeys() {
    vKeys = vector<BYTE>{1, 2, 4, 8, 9, 13, 16, 17, 18, 20, 27, 44, 46, 192};
    for (int i = 32; i <= 40; i++) {
        vKeys.push_back(i);
    }
    for (int i = 48; i <= 92; i++) { // 0~9 + A~Z
        vKeys.push_back(i);
    }
    for (int i = 112; i <= 123; i++) { // F1~F12
        vKeys.push_back(i);
    }
    for (int i = 96; i <= 111; i++) { // 小键盘
        vKeys.push_back(i);
    }
}
void pressDown(int key) {
    switch (key) {
    case 1: {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); // 鼠标左键按下
        break;
    }
    case 2: {
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        break;
    }
    case 4: {
        mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
        break;
    }
    case 5: {
        mouse_event(MOUSEEVENTF_XDOWN, 0, 0, XBUTTON1, 0);
        break;
    }
    case 6: {
        mouse_event(MOUSEEVENTF_XDOWN, 0, 0, XBUTTON2, 0);
        break;
    }
    default: {
        keybd_event(key, MapVirtualKey(key, 0), 0, 0);
    }
    }
}
void pressUp(int key) {
    switch (key) {
    case 1: {
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        break;
    }
    case 2: {
        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        break;
    }
    case 4: {
        mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
        break;
    }
    case 5: {
        mouse_event(MOUSEEVENTF_XUP, 0, 0, XBUTTON1, 0);
        break;
    }
    case 6: {
        mouse_event(MOUSEEVENTF_XUP, 0, 0, XBUTTON2, 0);
        break;
    }
    default: {
        keybd_event(key, MapVirtualKey(key, 0), 2, 0);
    }
    }
}
void clearPressingState() {
    for (int i = 3; i < vKeys.size(); i++) {
        pressUp(vKeys[i]);
    }
}
int imitateChange() {
    int flag = 0;
    // 方向键模拟视角变换
    if (pressing(VK_LEFT)) {
        flag = 1;
        mouse_event(MOUSEEVENTF_MOVE, -MOUSE_SPEED, 0, 0, 0);
    } else if (pressing(VK_RIGHT)) {
        flag = 1;
        mouse_event(MOUSEEVENTF_MOVE, MOUSE_SPEED, 0, 0, 0);
    } else if (pressing(VK_UP)) {
        flag = 1;
        mouse_event(MOUSEEVENTF_MOVE, 0, -MOUSE_SPEED, 0, 0);
    } else if (pressing(VK_DOWN)) {
        flag = 1;
        mouse_event(MOUSEEVENTF_MOVE, 0, MOUSE_SPEED, 0, 0);
    }
    return flag;
}
