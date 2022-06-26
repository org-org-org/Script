#include "./common/common_record.h"
int main() {
    initRecord();
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