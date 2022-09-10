#include "../../common/sync_implement.h"
// int state[256] = {0};
// bool doublePress(int vKey) {
//     if (GetAsyncKeyState(vKey)) {
//         if (pre[vKey] == 0) { // 之前没按着现在按着，按下
//             pre[vKey] = 1;
//             state[vKey]++;
//         }
//     } else {
//         if (pre[vKey] == 1) { // 之前按着现在没按着，松开
//             pre[vKey] = 0;
//             state[vKey]++;
//         } else {
//             state[vKey] = 0;
//         }
//     }
//     return state[vKey] == 4;
// }
int pauseEvent() {
    if (pressing(VK_F7) || pressing(VK_MENU) && pressing(VK_TAB)) {
        clearPressingState();
        while (!pressing(VK_F6)) {
            if (pressing(VK_F4)) {
                return 0;
            }
            Sleep(SLEEP_DURATION);
        }
    }
    if (pressing('M') || pressing('B') || pressing('C') || pressing('L') || pressing(VK_RETURN)) {
        clearPressingState();
        while (!pressing(VK_ESCAPE) && !pressing(VK_F6)) {
            if (pressing(VK_F4)) {
                return 0;
            }
            Sleep(SLEEP_DURATION);
        }
    }
    return 1;
}
void selfEvent() {
    if (pressing('H')) {
        start = Now();
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
}
void init() {
    loadAllKeys();
    FILE* fp;
    if ((fp = findFile("event.txt", "D:/0_vscode_cpp/Script/GameScript/YuanShen/input/")) == NULL) {
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
int main() {
    init();
    while (!pressing(VK_F6)) {
        Sleep(SLEEP_DURATION);
        if (pressing(VK_F4)) {
            return 0;
        }
    }
    while (!pressing(VK_F4)) {
        if (pauseEvent() == 0) {
            return 0;
        }
        pressKey('F');
        if (pressing('N')) {
            pressDown('W');
        }
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}