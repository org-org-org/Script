#include "common_record.h"
void init() {
    loadAllKeys();
    cout << "input a filename to save\n";
    cin >> fileName;
    fileName = LOAD_DIR + fileName + ".txt";
    FILE* fp = fopen(fileName.c_str(), "w");
    if (fp == NULL) {
        cout << fileName << endl;
    }
    cout << "then press F8 to start recording and press F9 to stop\n";
    while (!pressing(beginKey)) { // 按F8开始录制
        Sleep(SLEEP_DURATION);
    }
    printf("\a");
    start = Now();
    prePoint.x = 0x3f3f3f3f;
    mouseMoveEvent(); // 设置鼠标初始位置
}
int main() {
    init();
    while (!pressing(endKey)) { // 按F9停止录制
        curTime = Now() - start;
        for (auto v : vKeys) { // 循环监听所有按键
            check(v);
        }
        mouseMoveEvent();
        Sleep(SLEEP_DURATION);
    }
    saveRecord();
    return 0;
}