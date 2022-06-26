#include "myhead.h"
bool pre[256] = {0};
POINT point, prePoint;
int pressEsc = 0, imitateViewChange = 0;
// 在curTime时imitateViewChange执行
void pressDownEvent(int vKey) {
    pre[vKey] = 1;
    inputTime[inputNum] = curTime;
    inputKey[inputNum] = vKey;
    inputType[inputNum] = 0;
    inputNum++;
}
void pressUpEvent(int vKey) {
    pre[vKey] = 0;
    inputTime[inputNum] = curTime;
    inputKey[inputNum] = vKey;
    inputType[inputNum] = 2;
    inputNum++;
}
void mouseMoveEvent() {
    GetCursorPos(&point); // 获取鼠标指针位置(屏幕坐标)
    if (abs(point.x - prePoint.x) > 1 || abs(point.y - prePoint.y) > 1) {
        inputTime[inputNum] = curTime;
        inputKey[inputNum] = -point.x; // 用负数记录
        inputType[inputNum] = -point.y;
        prePoint = point;
        inputNum++;
    }
}
void check(int vKey) {
    if (vKey == beginKey || vKey == endKey) {
        return;
    }
    if (pressing(vKey)) {
        if (pre[vKey] == 0) { // 之前没按着现在按着，按下
            pressDownEvent(vKey);
        }
    } else {
        if (pre[vKey] == 1) { // 之前按着现在没按着，松开
            pressUpEvent(vKey);
        }
    }
}
void save() {
    FILE* fp = fopen(fileName.c_str(), "w");
    for (int i = 0; i < inputNum; i++) {
        fprintf(fp, "%d %d %d\n", inputTime[i], inputKey[i], inputType[i]);
    }
    fclose(fp);
}
void init() {
    loadAllKeys();
    cout << "input a filename to save\n";
    cin >> fileName;
    fileName = LOAD_DIR + fileName + ".txt";
    FILE* fp = fopen(fileName.c_str(), "w");
    if (fp == NULL) {
        cout << fileName << endl;
    }
    cout << "whether to quick click Esc to pause game at first? [0/1]\n";
    cin >> pressEsc;
    cout << "whether to use ↑↓←→ to imitate view change? [0/1]\n";
    cin >> imitateViewChange;
    cout << "then press F8 to start recording and press F9 to stop\n";
    while (!pressing(beginKey)) { // 按F8开始录制
        Sleep(SLEEP_DURATION);
    }
    printf("\a");
    start = Now();
    prePoint.x = 0x3f3f3f3f;
    mouseMoveEvent(); // 设置鼠标初始位置
}
void quickClickEsc() {
    if (pressEsc && curTime > 3200) {
        while (curTime < 5400) {
            keybd_event(VK_ESCAPE, 0, 0, 0);
            pressDownEvent(VK_ESCAPE);
            Sleep(SLEEP_DURATION);
            curTime = Now() - start;
            keybd_event(VK_ESCAPE, 0, 2, 0);
            pressUpEvent(VK_ESCAPE);
            Sleep(SLEEP_DURATION);
            curTime = Now() - start;
        }
        printf("\a");
        pressEsc = 0;
    }
}
int main() {
    init();
    while (!pressing(endKey)) { // 按F9停止录制
        curTime = Now() - start;
        quickClickEsc();
        for (auto v : vKeys) { // 循环监听所有按键
            check(v);
        }
        if (imitateViewChange) {
            imitateChange();
        }
        mouseMoveEvent();
        Sleep(SLEEP_DURATION);
    }
    save();
    return 0;
}