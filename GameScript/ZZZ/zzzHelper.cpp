#include "../../common/sync_implement.cpp"
const int duration = 10;
void event1() {
    pressKey(1);
}
void event2() {
    pressDown('W');
}
void eventSpace() { // 双反，切下一个人
    pressKey(VK_LSHIFT, duration);
    pressKey('J', duration);
    pressKey('2');
}
void eventC() { // 双反，切上一个人
    pressKey(VK_LSHIFT, duration);
    pressKey('J', duration);
    pressKey('1');
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
        checkPressingKeyOnce(VK_SPACE, eventSpace);
        checkPressingKeyOnce('C', eventC);
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}