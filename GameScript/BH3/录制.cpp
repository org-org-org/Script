#include "../../common/common_record.cpp"
int pressEsc = 0;
void init() {
    cout << "whether to quick hit Esc to pause game at first? [0/1]\n";
    cin >> pressEsc;
    initRecord();
}
void quickHitEsc() {
    if (pressEsc && curTime > 6000) {
        while (curTime < 8000) {
            pressDown(VK_ESCAPE);
            pressDownEvent(VK_ESCAPE);
            Sleep(SLEEP_DURATION);
            pressUp(VK_ESCAPE);
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