#include "../../common/sync_implement.cpp"
void event1() {
    pressKey(VK_SPACE);
}
void event2() {
    pressKey(1);
}
int main() {
    loadAllKeys();
    INT8 hitF = 0;
    while (1) {
        if (pressing(VK_DECIMAL)) { // 小键盘.
            pressDown('W');
        }
        checkPressedKey(192, event1);
        checkPressingKey(VK_XBUTTON1, event2); // 鼠标侧键（后退）
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}