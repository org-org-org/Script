#include "../../common/sync_implement.cpp"
void event1() {
    pressKey(1);
}
void event2() {
    pressDown('W');
}
void eventVK_XBUTTON1() { // 双反，切下一个人
    pressKey(2, 20);
    pressKey(1, 20);
    pressKey(VK_XBUTTON1, 20);  // 鼠标侧键（后退）
    pressKey(1);
}
void eventVK_XBUTTON2() { // 双反，切上一个人
    pressKey(2, 20);
    pressKey(1, 20);
    pressKey(VK_XBUTTON2, 20);  // 鼠标侧键（前进）
    pressKey(1);
}
void pauseEvent() {
    if (pressing(pauseKey)) { // 按F7暂停
        clearPressingState();
        while (!pressing(beginKey)) { // 按F8重新开始
            Sleep(SLEEP_DURATION);
        }
    }
}
int main() {
    loadAllKeys();
    while (1) {
        pauseEvent();
        checkPressedKeyUntilNextPressed(192, event1);
        checkPressingKeyOnce(VK_DECIMAL, event2); // 小键盘.
        checkPressingKeyOnce(VK_SPACE, eventVK_XBUTTON1);
        checkPressingKeyOnce('C', eventVK_XBUTTON2);
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}