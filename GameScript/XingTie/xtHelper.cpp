#include "../../common/sync_implement.cpp"
void event1() {
    pressKey(VK_SPACE);
}
int main() {
    loadAllKeys();
    while (1) {
        if (pressing(VK_DECIMAL)) { // 小键盘.
            pressDown('W');
        }
        checkPressedKeyUntilNextPressed(192, event1);
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}