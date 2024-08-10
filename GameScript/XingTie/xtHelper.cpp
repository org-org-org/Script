#include "../../common/sync_implement.cpp"
void event1() {
    pressKey(VK_SPACE);
}
void event2() {
    pressDown('W');
}
int main() {
    loadAllKeys();
    while (1) {
        checkPressedKeyUntilNextPressed(192, event1);
        checkPressingKeyOnce(VK_DECIMAL, event2); // 小键盘.
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}