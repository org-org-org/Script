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
void press(BYTE vKey) {
    keybd_event(vKey, 0, 0, 0);
    keybd_event(vKey, 0, 2, 0);
}
bool pressing(int vKey) {
    return GetAsyncKeyState(vKey) >> 15;
}
void imitateChange() {
    // 小键盘模拟视角变换
    if (pressing(VK_LEFT)) {
        mouse_event(MOUSEEVENTF_MOVE, -MOUSE_SPEED, 0, 0, 0);
    } else if (pressing(VK_RIGHT)) {
        mouse_event(MOUSEEVENTF_MOVE, MOUSE_SPEED, 0, 0, 0);
    } else if (pressing(VK_UP)) {
        mouse_event(MOUSEEVENTF_MOVE, 0, -MOUSE_SPEED, 0, 0);
    } else if (pressing(VK_DOWN)) {
        mouse_event(MOUSEEVENTF_MOVE, 0, MOUSE_SPEED, 0, 0);
    }
    // PgUp, PgDn模拟滚轮
    if (pressing(VK_PRIOR)) {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, MOUSE_SPEED, 0);
    } else if (pressing(VK_NEXT)) {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -MOUSE_SPEED, 0);
    }
}
time_t Now() { // 获取当前时间戳，毫秒级
    time_t second;
    time(&second);
    SYSTEMTIME ms;
    GetSystemTime(&ms);
    return second * 1000 + ms.wMilliseconds;
}
FILE* findFile(string fileName, string prefix = LOAD_DIR) {
    if (fileName.find(".txt") == fileName.npos) {
        fileName += ".txt";
    }
    FILE* fp = fopen((prefix + fileName).c_str(), "r");
    if (fp != NULL) {
        return fp;
    }
    DIR* dir = opendir(prefix.c_str());
    struct dirent* entry;
    while (entry = readdir(dir)) {
        string curName = entry->d_name;
        if (curName.find('.') == curName.npos) { // 是文件夹
            fp = findFile(fileName, prefix + curName + '/');
            if (fp != NULL) {
                closedir(dir);
                return fp;
            }
        }
    }
    closedir(dir);
    return NULL;
}
void pressDown(int key) {
    if (key == 1) {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); // 鼠标左键按下 
    } else if (key == 2) {
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    } else if (key == 4) {
        mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
    } else {
        keybd_event(key, 0, 0, 0);
    }
}
void pressUp(int key) {
    if (key == 1) {
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    } else if (key == 2) {
        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
    } else if (key == 4) {
        mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
    } else {
        keybd_event(key, 0, 2, 0);
    }
}
void mouseMove(int i) {
    SetCursorPos(-inputKey[i], -inputType[i]);
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