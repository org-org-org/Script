#include "common.h"
int ROUND_DURATION = 0;
int ROUND = 1;
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
int waitToStart(int T) {
    if (ROUND_DURATION && T) {
        Sleep(ROUND_DURATION * 1000);
    } else {
        while (!pressing(beginKey)) { // 按F8开始执行
            if (pressing(endKey)) { // 按F9中途结束
                return 0;
            }
            Sleep(SLEEP_DURATION);
        }
    }
    return 1;
}