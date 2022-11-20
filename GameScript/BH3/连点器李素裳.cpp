#include "../../common/common_implement.h"
void pauseEvent() {
    if (pressing('N') || pressing(VK_MENU) && pressing(VK_TAB)) {
        clearPressingState();
        while (!pressing('M')) {
            Sleep(SLEEP_DURATION);
        }
    }
    if (pressing(VK_ESCAPE)) {
        clearPressingState();
        while (!pressing(192)) { // 按 ` 开始
            Sleep(SLEEP_DURATION);
        }
    }
}
int main() {
    cout << "then press M to start and press N to pause or press F4 to stop\n";
    clearPressingState();
    while (!pressing('M')) {
        Sleep(SLEEP_DURATION);
    }
    while (!pressing(VK_F4)) {
        pauseEvent();
        pressKey('J');
        Sleep(SLEEP_DURATION);
    }
    return 0;
}
