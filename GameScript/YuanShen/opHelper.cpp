#include "../../common/sync_implement.cpp"
void event1() {
    pressKey('F');
}
int main() {
    loadAllKeys();
    while (1) {
        if (pressing(VK_XBUTTON1)) { // 鼠标侧键（后退）
            mouse_event(MOUSEEVENTF_MOVE, -256, 0, 0, 0);
        }
        if (pressing(VK_DECIMAL)) { // 小键盘.
            pressDown('W');
        }
        checkPressedKeyUntilNextPressed(192, event1);
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}