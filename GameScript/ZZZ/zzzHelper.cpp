#include "../../common/sync_implement.cpp"
void event1() {
    pressKey(VK_SPACE);
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
int main() {
    loadAllKeys();
    INT8 hitF = 0;
    while (1) {
        if (pressing(VK_DECIMAL)) { // 小键盘.
            pressDown('W');
        }
        checkPressedKeyUntilNextPressed(192, event1);
        checkPressingKeyOnce(VK_SPACE, eventVK_XBUTTON1);
        checkPressingKeyOnce('C', eventVK_XBUTTON2);
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}