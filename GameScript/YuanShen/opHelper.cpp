#include "../../common/sync_implement.cpp"
int main() {
    loadAllKeys();
    INT8 hitF = 0;
    while (1) {
        if (pressing(VK_DECIMAL)) { // 小键盘.
            pressDown('W');
        }
        if (pressing(192)) {
            if (pre[192] == 0) { // 之前没按着现在按着，按下
                pre[192] = 1;
            }
        } else {
            if (pre[192] == 1) { // 之前按着现在没按着，松开
                pre[192] = 0;
                hitF = !hitF;
            }
        }
        if (hitF) {
            hitF++;
            if (hitF > 9) {
                pressKey('F');
                hitF = 1;
            }
        }
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}