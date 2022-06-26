#include "../../common/common_record.h"
int syncImitate[N] = {0};
int syncCnt = 0;
void init() {
    initRecord();
}
int imitateChange() {
    // PgUp, PgDn模拟滚轮
    if (pressing(VK_PRIOR)) {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, MOUSE_SPEED, 0);
    } else if (pressing(VK_NEXT)) {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -MOUSE_SPEED, 0);
    }
    int flag = 0;
    // 小键盘模拟视角变换
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
void save() {
    FILE* fp = fopen(fileName.c_str(), "w");
    fprintf(fp, "%d\n", inputNum);
    for (int i = 0; i < inputNum; i++) {
        fprintf(fp, "%d %d %d\n", inputTime[i], inputKey[i], inputType[i]);
    }
    syncImitate[syncCnt++] = INF;
    fprintf(fp, "%d", syncCnt);
    for (int i = 0; i < syncCnt; i++) {
        if (i % 10 == 0) {
            fprintf(fp, "\n");
        }
        fprintf(fp, "%d ", syncCnt);
    }
    fclose(fp);
}
int main() {
    init();
    while (!pressing(endKey)) { // 按F9停止录制
        curTime = Now() - start;
        for (auto v : vKeys) { // 循环监听所有按键
            check(v);
        }
        if (imitateChange()) {
            syncImitate[syncCnt++] = curTime;
        }
        mouseMoveEvent();
        Sleep(SLEEP_DURATION);
    }
    save();
    return 0;
}