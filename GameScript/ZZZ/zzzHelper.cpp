#include "../../common/sync_implement.cpp"
void event1() {
    pressKey(VK_SPACE);
}
void eventVK_XBUTTON1() { // 双反，切上一个人
    pressKey(2);
    pressKey(1);
    pressKey('C');
    pressKey(1);
}
void eventVK_XBUTTON2() { // 双反，切下一个人
    pressKey(2);
    pressKey(1);
    pressKey(VK_SPACE);
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
        checkPressingKeyOnce(VK_XBUTTON1, eventVK_XBUTTON1); // 鼠标侧键（后退）
        checkPressingKeyOnce(VK_XBUTTON2, eventVK_XBUTTON2); // 鼠标侧键（前进）
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}