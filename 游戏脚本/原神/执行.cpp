#include "../../common/common_implement.h"
int syncImitate[N] = {0};
int syncCnt = 0;
int syncFlag = 0;
void init() {
    loadAllKeys();
    cout << "input a filename to read\n";
    cin >> fileName;
    FILE* fp;
    while ((fp = findFile(fileName)) == NULL) {
        cout << "wrong filename, please input again\n";
        cin >> fileName;
    }
    cout << "then press F8 to implement and press F9 to stop\n";
    fscanf(fp, "%d", &inputNum);
    for (int i = 0; i < inputNum; i++) {
        fscanf(fp, "%d%d%d", &inputTime[i], &inputKey[i], &inputType[i]);
    }
    fscanf(fp, "%d", &syncCnt);
    for (int i = 0; i < syncCnt; i++) {
        fscanf(fp, "%d", &syncImitate[i]);
    }
    fclose(fp);
    while (!pressing(beginKey)) { // 按F8开始执行
        Sleep(SLEEP_DURATION);
    }
    start = Now();
}
void syncImitateChange() {
    // PgUp, PgDn模拟滚轮
    if (pressing(VK_PRIOR)) {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, MOUSE_SPEED, 0);
    } else if (pressing(VK_NEXT)) {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -MOUSE_SPEED, 0);
    }
    if (curTime >= syncImitate[syncFlag]) {
        syncFlag++;
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
    }
}
int main() {
    init();
    int i = 0;
    while (i < inputNum) {
        if (pressing(endKey)) { // 按F9中途结束
            clearPressingState();
            return 0;
        }
        curTime = Now() - start;
        while (i < inputNum && curTime >= inputTime[i]) {
            if (inputKey[i] <= 0) { // 鼠标移动
                mouseMove(i);
            } else if (inputType[i] == 0) {
                pressDown(inputKey[i]);
            } else if (inputType[i] == 2) {
                pressUp(inputKey[i]);
            }
            i++;
        }
        syncImitateChange();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}