#include "../../common/common_record.h"
int pressEsc = 0;
void init() {
    cout << "whether to quick hit Esc to pause game at first? [0/1]\n";
    cin >> pressEsc;
    initRecord();
}
void quickHitEsc() {
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
        pauseEvent();
        curTime = Now() - start;
        quickHitEsc();
        for (int i = 0; i < vKeys.size(); i++) { // 循环监听所有按键
            check(vKeys[i]);
        }
        mouseMoveEvent();
        Sleep(SLEEP_DURATION);
    }
    saveRecord();
    return 0;
}