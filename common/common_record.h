#include "common.h"
POINT point, prePoint;
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
void saveRecord() {
    FILE* fp = fopen(fileName.c_str(), "w");
    for (int i = 0; i < inputNum; i++) {
        fprintf(fp, "%d %d %d\n", inputTime[i], inputKey[i], inputType[i]);
    }
    fclose(fp);
}
void initRecord() {
    loadAllKeys();
    cout << "input a filename to save\n";
    cin >> fileName;
    fileName = LOAD_DIR + fileName + ".txt";
    cout << "then press F8 to start recording and press F9 to stop\n";
    while (!pressing(beginKey)) { // 按F8开始录制
        Sleep(SLEEP_DURATION);
    }
    printf("\a");
    start = Now();
    prePoint.x = INF;
    mouseMoveEvent(); // 设置鼠标初始位置
}