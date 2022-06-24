#include "myhead.h"
vector<BYTE>vKeys;
bool pre[256] = {0};
POINT point, prePoint;
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
    cout << "input a filename to save\n";
    cin >> fileName;
    fileName = LOAD_DIR + fileName + ".txt";
    FILE* fp = fopen(fileName.c_str(), "w");
    if (fp == NULL) {
        cout << fileName << endl;
    }
    cout << "then press F8 to start recording and press F9 to stop\n";
    loadAllKeys();
    while (!pressing(VK_F8)) { // 按F8开始录制
        Sleep(1);
    }
    start = Now();
    prePoint.x = 0x3f3f3f3f;
    mouseMoveEvent(); // 设置鼠标初始位置
}
int main() {
    init();
    while (!pressing(VK_F9)) { // 按F9停止录制
        curTime = Now() - start;
        for (auto v : vKeys) { // 循环监听所有按键
            check(v);
        }
        imitateChange();
        mouseMoveEvent();
        Sleep(1);
    }
    save();
    return 0;
}