#include "common_implement.cpp"
int syncImitate[N] = {0};
int syncCnt = 0;
int syncFlag = 0;
void syncImitateChange() {
    // PgUp, PgDn模拟滚轮
    if (pressing(VK_PRIOR)) {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, MOUSE_SPEED, 0);
    } else if (pressing(VK_NEXT)) {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -MOUSE_SPEED, 0);
    }
    if (curTime >= syncImitate[syncFlag]) {
        syncFlag++;
        imitateChange();
    }
}
void loadFile(string fileName, string dir) {
    FILE* fp;
    if ((fp = findFile(fileName, dir)) == NULL) {
        cout << "wrong filename\n";
        return;
    }
    cout << "press F6 to start and press F7 to pause or F4 to stop\n";
    fscanf(fp, "%d", &inputNum);
    for (int i = 0; i < inputNum; i++) {
        fscanf(fp, "%d%d%d", &inputTime[i], &inputKey[i], &inputType[i]);
    }
    fscanf(fp, "%d", &syncCnt);
    for (int i = 0; i < syncCnt; i++) {
        fscanf(fp, "%d", &syncImitate[i]);
    }
    fclose(fp);
}
void syncEvent() {
    clearPressingState();
    start = Now();
    syncFlag = 0;
    int i = 0;
    while (i < inputNum) {
        if (pressing(endKey)) { // 按F9中途结束
            clearPressingState();
            return;
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
}