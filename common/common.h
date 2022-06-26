#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <time.h>
#include <dirent.h>
using namespace std;
const int N = 1 << 18;
const int MOUSE_SPEED = 32;
const int SLEEP_DURATION = 10;
const string LOAD_DIR = "./input/";
int inputTime[N] = {0}, inputKey[N] = {0}, inputType[N] = {0};
int inputNum = 0;
time_t start = 0, curTime = 0;
string fileName;
BYTE beginKey = VK_F8, endKey = VK_F9;
vector<BYTE>vKeys;
bool pre[256] = {0};
void press(BYTE vKey) {
    keybd_event(vKey, 0, 0, 0);
    keybd_event(vKey, 0, 2, 0);
}
bool pressing(int vKey) {
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
    // for (int i = 96; i <= 111; i++) { // 小键盘
    //     vKeys.push_back(i);
    // }
}
void clearPressingState() {
    for (auto v : vKeys) {
        keybd_event(v, 0, 2, 0);
    }
}