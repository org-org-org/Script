#include "../../common/sync_implement.cpp"
void event1() {
    pressKey('F');
}
void event2() {
    pressDown('W');
}
int main() {
    loadAllKeys();
    while (1) {
        if (pressing(VK_XBUTTON1)) { // 鼠标侧键（后退）
            mouse_event(MOUSEEVENTF_MOVE, -256, 0, 0, 0);
        }
        checkPressedKeyUntilNextPressed(192, event1);
        checkPressingKeyOnce(VK_DECIMAL, event2); // 小键盘.
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}